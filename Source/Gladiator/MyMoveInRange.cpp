// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMoveInRange.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "MyBasicEnemy.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

EBTNodeResult::Type UMyMoveInRange::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    MyController = OwnerComp.GetAIOwner();
    Pawn = MyController->GetPawn();

    OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("ActorPositionBack"), Cast<UObject>(Cast<AMyBasicEnemy>(Pawn)->fake));

    Pawn->bUseControllerRotationPitch = !Pawn->bUseControllerRotationPitch;
    Pawn->bUseControllerRotationYaw = !Pawn->bUseControllerRotationYaw;
    Pawn->bUseControllerRotationRoll = !Pawn->bUseControllerRotationRoll;


    return EBTNodeResult::Succeeded;

}
