// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyCanAttackUncheck.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyCanAttackUncheck : public UBTTaskNode
{
	GENERATED_BODY()
public:
    class AAIController* MyController;

    class  APawn* Pawn;

    virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
