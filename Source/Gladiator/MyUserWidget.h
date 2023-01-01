// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

		// Methode
public:
	UFUNCTION(BlueprintCallable)
		void Retry();

	UFUNCTION(BlueprintCallable)
		void Quit();
};
