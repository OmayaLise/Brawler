// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityCharacter.h"
#include "Components/WidgetComponent.h"
#include "MyHealthBar.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "MyFakeActor.h"


#include "MyBasicEnemy.generated.h"

UCLASS()
class GLADIATOR_API AMyBasicEnemy : public AEntityCharacter
{
	GENERATED_BODY()
		// Attribute
public:
	bool PlayerDetected;

	static bool CanAttackPlayer;
	bool isAttacking;

	UPROPERTY(BlueprintReadWrite)
		bool CanDealDamage;

	class AMyAIController* EnemyAIController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UWidgetComponent* HealthBar;

	AMyFakeActor* fake;

		// Methode
public:
	AMyBasicEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void ColliderHammerHit(AActor* actorHit);

	void DistanceCheck();

protected:
	virtual void BeginPlay() override;
};
