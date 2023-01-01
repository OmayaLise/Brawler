// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCanAttackUncheck.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include <AIController.h>
#include "MyBasicEnemy.h"

EBTNodeResult::Type UMyCanAttackUncheck::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    MyController = OwnerComp.GetAIOwner();
    AMyBasicEnemy* MyEnemy = Cast<AMyBasicEnemy>(MyController->GetPawn());

    if (AMyBasicEnemy::CanAttackPlayer == false)
    {
        AMyBasicEnemy::CanAttackPlayer = true;
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("CanAttack"), false);
    
    }
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("PlayerMoved"), false);

    return EBTNodeResult::Succeeded;

}