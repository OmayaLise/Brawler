// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCheckDistanceToPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include <AIController.h>

EBTNodeResult::Type UMyCheckDistanceToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	controller = OwnerComp.GetAIOwner();
	APawn* Pawn = controller->GetPawn();
	FVector MyCharacter = Pawn->ActorToWorld().GetLocation();
	APawn* MyPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	float distancePlayerEnemy = MyPlayer->GetDistanceTo(Pawn);

	if (distancePlayerEnemy > 300)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("PlayerMoved"), true);
		return EBTNodeResult::Failed;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("PlayerMoved"), false);
	}

	return EBTNodeResult::Succeeded;
}