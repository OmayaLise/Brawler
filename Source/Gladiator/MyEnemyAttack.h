// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyEnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyEnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	class AAIController* controller;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
