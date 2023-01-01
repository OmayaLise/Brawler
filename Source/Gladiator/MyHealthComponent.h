// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Components/WidgetComponent.h"
#include "MyHealthBar.h"
#include "MyAIController.h"
#include "State.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActorComponent.h"
#include "MyHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentLifeChangedSignature, int, currentLife, int, maxLife);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLADIATOR_API UMyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	int maxLife;

	UPROPERTY(EditAnywhere)
	int currentLife;

	UPROPERTY(EditAnywhere)
		float timeWounded;

	float timerWounded;

	UMyHealthBar* lifeBar;
	AMyAIController* AIController;
	
	State previousState;

public:	
	State* state;
	UCapsuleComponent* capsuleComponent;
	UUserWidget* HealthBar;
	UWidgetComponent* healthBarComponent;
	bool* isAttacking;

	// Sets default values for this component's properties
	UMyHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(const int damage, const FVector positionAttack = FVector(0,0,0));

	const int GetCurrentLife() const { return currentLife; };
	void SetMaxLife(const int p_maxLife);
	void SetAIController(AMyAIController* p_AIController) { AIController = p_AIController; };

	UPROPERTY(BlueprintAssignable)
		FOnCurrentLifeChangedSignature OnCurrentLifeChangedDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
