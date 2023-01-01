// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicEnemy.h"

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

#include "MyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "MyPlayer.h"
#include <Runtime/AIModule/Classes/BrainComponent.h>
#include "MyFakeActor.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>


bool AMyBasicEnemy::CanAttackPlayer = true;


// Sets default values
AMyBasicEnemy::AMyBasicEnemy()
    : AEntityCharacter()
    , isAttacking(false)
{
    AMyBasicEnemy::CanAttackPlayer = true;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthBar->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    myHealthComponent->isAttacking = &isAttacking;
}

// Called when the game starts or when spawned
void AMyBasicEnemy::BeginPlay()
{
	Super::BeginPlay();

    myHealthComponent->SetMaxLife(3);
    myHealthComponent->HealthBar = HealthBar->GetUserWidgetObject();
    myHealthComponent->healthBarComponent = HealthBar;
    Cast<UMyHealthBar>(HealthBar->GetUserWidgetObject())->Init(this);
	
	EnemyAIController = Cast<AMyAIController>(GetController());
    myHealthComponent->SetAIController(EnemyAIController);

    fake = GetWorld()->SpawnActor<AMyFakeActor>(AMyFakeActor::StaticClass());
}

// Called every frame
void AMyBasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (state == State::Death)
    {

        return;
    }

    DistanceCheck();
    APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn();
    SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation()));
}

// Called to bind functionality to input
void AMyBasicEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyBasicEnemy::ColliderHammerHit(AActor* actorHit)
{
    if (state == State::Attacked)
    {
        AMyPlayer* enemyHit = nullptr;
        enemyHit = Cast<AMyPlayer>(actorHit);
        if (enemyHit)
        {
            UMyHealthComponent* enemyHealthComponent = enemyHit->FindComponentByClass<UMyHealthComponent>();
            if (enemyHealthComponent)
            {
                enemyHealthComponent->TakeDamage(damage, GetActorLocation());
            }
        }
    }
}

void AMyBasicEnemy::DistanceCheck()
{
    APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn();
    FVector positionBack = GetActorLocation() - player->GetActorLocation();
    positionBack.Normalize();
    positionBack *= 350;
    positionBack += player->GetActorLocation();
    fake->SetActorLocation(positionBack);

}