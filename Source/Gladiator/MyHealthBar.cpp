// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHealthBar.h"
#include "MyHealthComponent.h"

void UMyHealthBar::Init(APawn* owingPawn)
{
	UActorComponent* healthActorComp = owingPawn->GetComponentByClass(UMyHealthComponent::StaticClass());
	UMyHealthComponent* healthComp = Cast<UMyHealthComponent>(healthActorComp);
	healthComp->OnCurrentLifeChangedDelegate.AddUniqueDynamic(this, &UMyHealthBar::OnCurrentLifeChanged);
}

void UMyHealthBar::OnCurrentLifeChanged(const int currentLife, const int maxLife)
{
	HealthBar->SetPercent(currentLife * 1.0f / maxLife * 1.0f);
}