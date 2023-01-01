// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityCharacter.h"

AEntityCharacter::AEntityCharacter()
	: state(State::None)
	, damage(1)
{
	PrimaryActorTick.bCanEverTick = true;

	myHealthComponent = CreateDefaultSubobject<UMyHealthComponent>(TEXT("MyHealthComponent"));
	myHealthComponent->state = &state;
	myHealthComponent->capsuleComponent = GetCapsuleComponent();
}

void AEntityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	materialMeshDwarf0 = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	GetMesh()->SetMaterial(0, materialMeshDwarf0);
	materialMeshDwarf1 = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), this);
	GetMesh()->SetMaterial(1, materialMeshDwarf1);

	state = State::None;
}

void AEntityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateStateTintMaterial();
}

void AEntityCharacter::UpdateStateTintMaterial()
{
	FLinearColor color = FLinearColor(1, 1, 1, 1);
	switch (state)
	{
	case State::None:
		color = FLinearColor(1, 1, 1, 1);
		break;

	case State::Shield:
		color = FLinearColor(0.5, 1, 1, 1);
		break;

	case State::Wounded:
		color = FLinearColor(1, 0, 0, .5);
		break;

	default:
		break;
	}

	materialMeshDwarf0->SetVectorParameterValue("Tint", color);
	materialMeshDwarf1->SetVectorParameterValue("Tint", color);
}

void AEntityCharacter::Attack()
{
	if (MeleeAttackMontage && !GetMesh()->AnimScriptInstance->Montage_IsPlaying(MeleeAttackMontage))
	{
		float duration = GetMesh()->AnimScriptInstance->Montage_Play(MeleeAttackMontage);

		state = State::Attacked;

		FTimerHandle _;
		GetWorldTimerManager().SetTimer(_, this, &AEntityCharacter::AttackEnd, duration, false);
	}
}

void AEntityCharacter::AttackEnd()
{
	state = State::None;
}

void AEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

