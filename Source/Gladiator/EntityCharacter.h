// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "MyHealthComponent.h"
#include "GameFramework/Character.h"
#include "EntityCharacter.generated.h"

UCLASS()
class GLADIATOR_API AEntityCharacter : public ACharacter
{
	GENERATED_BODY()

		// Attribute
public:
	State state;
	int damage;


protected:
	UMaterialInstanceDynamic* materialMeshDwarf0;
	UMaterialInstanceDynamic* materialMeshDwarf1;

	class UMyHealthComponent* myHealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* MeleeAttackMontage;

	// Methode
public:	
	AEntityCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();
	void AttackEnd();

protected:
	virtual void BeginPlay() override;

private:
	void UpdateStateTintMaterial();
};
