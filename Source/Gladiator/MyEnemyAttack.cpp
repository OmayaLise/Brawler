// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAttack.h"
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include <AIController.h>
#include <Gladiator/MyBasicEnemy.h>
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	controller = OwnerComp.GetAIOwner();
	APawn* Pawn = controller->GetPawn();

	AMyBasicEnemy* enemy = nullptr;
	enemy = Cast<AMyBasicEnemy>(Pawn);

	if (enemy)
		enemy->Attack();
	else
		return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}