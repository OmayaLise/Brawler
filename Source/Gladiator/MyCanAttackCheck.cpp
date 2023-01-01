// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCanAttackCheck.h"
#include <Runtime/AIModule/Classes/AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include <AIController.h>
#include "MyBasicEnemy.h"


EBTNodeResult::Type UMyCanAttackCheck::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    MyController = OwnerComp.GetAIOwner();
    AMyBasicEnemy * MyEnemy = Cast<AMyBasicEnemy>(MyController->GetPawn());

    FVector CirclePosition = MyEnemy->GetActorLocation();
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PlayerCircle"), CirclePosition);


    if(AMyBasicEnemy::CanAttackPlayer)
    {
        AMyBasicEnemy::CanAttackPlayer = false;
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("CanAttack"), true);
        MyEnemy->isAttacking = true;
    }

    return EBTNodeResult::Succeeded;

}