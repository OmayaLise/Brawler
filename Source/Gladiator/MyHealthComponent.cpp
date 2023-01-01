#include "MyHealthComponent.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "MyBasicEnemy.h"

UMyHealthComponent::UMyHealthComponent()
	: maxLife(5)
	, currentLife(maxLife)
	, state(nullptr)
	, timeWounded(1.f)
	, timerWounded(0)
	, AIController(nullptr)
	, healthBarComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMyHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMyHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!lifeBar && HealthBar)
		lifeBar = Cast<UMyHealthBar>(HealthBar);

	if (state && *state == State::Wounded)
	{
		timerWounded += DeltaTime;
		if (timerWounded >= timeWounded)
		{
			*state = previousState;
			timerWounded = 0.f;
		}
	}
}

void UMyHealthComponent::TakeDamage(const int damage, const FVector positionAttack)
{
	FVector NormalizeVector = positionAttack - GetOwner()->GetActorLocation();
	NormalizeVector.Normalize();
	float temp = FVector::DotProduct(GetOwner()->GetActorForwardVector(), NormalizeVector);

	if (*state == State::Shield && (temp > 0.f))
		return;

	if (*state == State::Wounded)
		return;

	currentLife -= damage;

	if (currentLife <= 0)
	{
		*state = State::Death;
		capsuleComponent->SetCollisionProfileName("NoCollision");
		
		if (AIController)
			AIController->StopBehaviorTree();
		
		if(healthBarComponent)
			healthBarComponent->DestroyComponent();

		if (isAttacking && *isAttacking)
			AMyBasicEnemy::CanAttackPlayer = true;
	}
	else
	{
		previousState = *state;
		*state = State::Wounded;
	}

	OnCurrentLifeChangedDelegate.Broadcast(currentLife, maxLife);
}

void UMyHealthComponent::SetMaxLife(const int p_maxLife)
{
	maxLife = p_maxLife;
	currentLife = p_maxLife;
}