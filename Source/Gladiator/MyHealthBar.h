// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
		// Attribute
public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	// Methode
public:
	void Init(APawn* owingPawn);

	UFUNCTION()
	void OnCurrentLifeChanged(const int currentLife, const int maxLife);
};
