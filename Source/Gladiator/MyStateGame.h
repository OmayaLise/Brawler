// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "MyPlayer.h"
#include "MyBasicEnemy.h"
#include "MyUserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStateGame.generated.h"

UCLASS()
class GLADIATOR_API AMyStateGame : public AActor
{
	GENERATED_BODY()
	
		// Attribute
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UMyUserWidget> loseMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UMyUserWidget> winMenu;

private:
	std::vector<AEntityCharacter*> enemys;
	AEntityCharacter* player;

	APlayerController* playerController;

	UUserWidget* loseWidget;
	UUserWidget* winWidget;

	bool gameIsFinish;

		// Methode
public:	
	AMyStateGame();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	const bool CheckEnemyDeath() const;
	const bool CheckPlayerDeath() const;

	void StartLoseMenu();
	void StartWinMenu();

	void ShowMouseCursor(const bool p_visibility);

	void GetEntity();
};
