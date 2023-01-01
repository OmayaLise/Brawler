// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyUserWidget::Retry()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FString nameCurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
	UGameplayStatics::OpenLevel(GetWorld(), FName(nameCurrentLevel));
}

void UMyUserWidget::Quit()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), playerController, EQuitPreference::Quit, true);
}