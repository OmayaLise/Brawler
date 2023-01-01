// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	static bool canAttack;

	AMyAIController();

    void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnSeePawn(APawn* PlayerPawn);

	UFUNCTION()
	void SetCanSeePlayer(bool SeePlayer, class UObject* Player, APawn* PlayerPawn);

	FTimerHandle RetriggerableTimerHandle;
	FTimerDelegate FunctionDelegate;
	void RunRetriggerableTimer();

	void SetCanAttackPlayer();

	void StopBehaviorTree();

	FVector testPos;

};
