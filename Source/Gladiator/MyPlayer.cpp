// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyBasicEnemy.h"
#include "MyHealthBar.h"

#include "MyHealthComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
    : AEntityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...    
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
    CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
    CameraArm->SetupAttachment(RootComponent);
    CameraArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character    
    CameraArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

    if (healthBarPlayer)
    {
        healthBar = CreateWidget(GetWorld()->GetFirstPlayerController(), healthBarPlayer);
        myHealthComponent->HealthBar = healthBar;
        healthBar->AddToViewport();
        Cast<UMyHealthBar>(healthBar)->Init(this);
    }
    
    USceneComponent* shieldComponent = GetMesh()->GetChildComponent(1);
    shieldMesh = Cast<USkeletalMeshComponent>(shieldComponent);
    materialMeshShield = UMaterialInstanceDynamic::Create(shieldMesh->GetMaterial(0), this);
    shieldMesh->SetMaterial(0, materialMeshShield);
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AEntityCharacter::Attack);
    PlayerInputComponent->BindAction("Shield", IE_Pressed, this, &AMyPlayer::Shield);
    PlayerInputComponent->BindAction("Shield", IE_Released, this, &AMyPlayer::StopShield);

    PlayerInputComponent->BindAxis("Forward", this, &AMyPlayer::MoveForward);
    PlayerInputComponent->BindAxis("Right", this, &AMyPlayer::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void AMyPlayer::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (state != State::Shield && state != State::Attacked))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AMyPlayer::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f) && (state != State::Shield && state != State::Attacked))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

void AMyPlayer::Attack()
{
    if (MeleeAttackMontage && !GetMesh()->AnimScriptInstance->Montage_IsPlaying(MeleeAttackMontage))
    {
        float duration = GetMesh()->AnimScriptInstance->Montage_Play(MeleeAttackMontage);

        state = State::Attacked;
        if (state == State::Shield)
            StopShield();

        FTimerHandle _;
        GetWorldTimerManager().SetTimer(_, this, &AEntityCharacter::AttackEnd, duration, false);
    }
}

void AMyPlayer::Shield()
{
    if (state == State::None)
    {
        state = State::Shield;
        shieldMesh->SetWorldScale3D(FVector(1.75f, 1.75f, 1.75f));
    }
}

void AMyPlayer::StopShield()
{
    state = State::None;
    shieldMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
}

void AMyPlayer::ColliderHammerHit(AActor* actorHit)
{
    if (state == State::Attacked)
    {
        AMyBasicEnemy* enemyHit = nullptr;
        enemyHit = Cast<AMyBasicEnemy>(actorHit);
        if (enemyHit)
        {
            UMyHealthComponent* enemyHealthComponent = enemyHit->FindComponentByClass<UMyHealthComponent>();
            if (enemyHealthComponent)
            {
                enemyHealthComponent->TakeDamage(damage);
            }
        }
    }
}