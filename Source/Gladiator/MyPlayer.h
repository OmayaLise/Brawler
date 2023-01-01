// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EntityCharacter.h"
#include "Animation/AnimMontage.h"
#include "MyPlayer.generated.h"


UCLASS(config = Game, BlueprintType)
class GLADIATOR_API AMyPlayer : public AEntityCharacter
{
	GENERATED_BODY()

		// Attribute
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UMyHealthBar> healthBarPlayer;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	class UUserWidget* healthBar;

	UPROPERTY(EditAnywhere)
	class USphereComponent* DamageCollision;

	USkeletalMeshComponent* shieldMesh;
	UMaterialInstanceDynamic* materialMeshShield;

		// Methode
public:
	AMyPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetState(const State p_state) { state = p_state; };

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void ColliderHammerHit(AActor* actorHit);

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);

private:
	void Attack() override;
	void Shield();
	void StopShield();
};