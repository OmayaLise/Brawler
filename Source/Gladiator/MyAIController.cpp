// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"


AMyAIController::AMyAIController()
{
    PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
}

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();
    PawnSensing->OnSeePawn.AddDynamic(this, &AMyAIController::OnSeePawn);
    RunBehaviorTree(BehaviorTree);
}

void AMyAIController::OnSeePawn(APawn* PlayerPawn)
{
    UObject* Player = Cast<UObject>(PlayerPawn);

    if (Player)
    {
        SetCanSeePlayer(true, Player, PlayerPawn);
        //RunRetriggerableTimer();
    }
}

void AMyAIController::SetCanSeePlayer(bool SeePlayer, UObject* Player, APawn* PlayerPawn)
{
    ACharacter* EnemyChar = Cast<ACharacter>(GetPawn());

    
    if (SeePlayer)
    {
        GetBlackboardComponent()->SetValueAsBool(FName("CanSeePlayer"), SeePlayer);
        GetBlackboardComponent()->SetValueAsObject(FName("PlayerTarget"), Player);

    }
    else
    {
        GetBlackboardComponent()->SetValueAsBool(FName("CanSeePlayer"), SeePlayer);

        EnemyChar->GetMesh()->GetAnimInstance()->StopAllMontages(0);
    }

}

void AMyAIController::RunRetriggerableTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);

    FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"),
        false, GetPawn());
   
    GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle,
        FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}

void AMyAIController::SetCanAttackPlayer()
{
    GetBlackboardComponent()->SetValueAsBool(FName("CanAttack"), true);
}

void AMyAIController::StopBehaviorTree()
{
    BrainComponent->StopLogic("");
}


