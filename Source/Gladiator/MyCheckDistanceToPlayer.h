// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyCheckDistanceToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyCheckDistanceToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	class UNavigationSystemV1* NavArea;

	class AAIController* controller;

	FVector RandomLocation;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
