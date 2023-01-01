// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityCharacter.h"
#include "Animation/AnimInstance.h"
#include "MyAnimDwarf.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class GLADIATOR_API UMyAnimDwarf : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float speedX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float speedY;

public:

	APawn* OwningPawn;
	AEntityCharacter* entity;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};
