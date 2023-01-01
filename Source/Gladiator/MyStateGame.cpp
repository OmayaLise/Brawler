// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStateGame.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
AMyStateGame::AMyStateGame()
	: gameIsFinish(false)
	, loseMenu(nullptr)
	, loseWidget(nullptr)
	, winMenu(nullptr)
	, winWidget(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyStateGame::BeginPlay()
{
	Super::BeginPlay();

	GetEntity();

	playerController = Cast<APlayerController>(player->GetController());
}

// Called every frame
void AMyStateGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gameIsFinish)
		return;

	if (CheckEnemyDeath())
	{
		StartWinMenu();
		gameIsFinish = true;
	}

	if (CheckPlayerDeath())
	{
		StartLoseMenu();
		gameIsFinish = true;
	}
}

const bool AMyStateGame::CheckEnemyDeath() const
{
	for (AEntityCharacter* enemy : enemys)
	{
		if (enemy->state != State::Death)
			return false;
	}
	return true;
}

const bool AMyStateGame::CheckPlayerDeath() const
{
	if (player->state != State::Death)
		return false;
	return true;
}

void AMyStateGame::StartLoseMenu()
{
	if (!loseMenu)
		return;

	loseWidget = CreateWidget(playerController, loseMenu);

	ShowMouseCursor(true);
	loseWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnly(playerController, loseWidget);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMyStateGame::StartWinMenu()
{
	if (!winMenu)
		return;

	winWidget = CreateWidget(playerController, winMenu);

	ShowMouseCursor(true);
	winWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnly(playerController, winWidget);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMyStateGame::ShowMouseCursor(const bool p_visibility)
{
	playerController->bShowMouseCursor = p_visibility;
	playerController->bEnableClickEvents = p_visibility;
	playerController->bEnableMouseOverEvents = p_visibility;
}

void AMyStateGame::GetEntity()
{
	TArray<AActor*> actors;
	TSubclassOf<AEntityCharacter> classToFind = AEntityCharacter::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actors);

	for (AActor* actor : actors)
	{
		AEntityCharacter* actorEntity = Cast<AEntityCharacter>(actor);
		if (!actorEntity)
			continue;

		if (Cast<AMyBasicEnemy>(actor))
		{
			enemys.push_back(actorEntity);
			continue;
		}

		if (Cast<AMyPlayer>(actor))
		{
			player = actorEntity;
			continue;
		}
	}
}