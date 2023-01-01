// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFakeActor.h"

// Sets default values
AMyFakeActor::AMyFakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	this->SphereMesh->AttachTo(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	this->SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	SphereMesh->SetCollisionProfileName("OverlapAll");
	SphereMesh->SetVisibility(false);
	SphereMesh->SetWorldScale3D(FVector(2, 2, 2));
	SphereMesh->SetRelativeScale3D(FVector(2, 2, 2));

}

// Called when the game starts or when spawned
void AMyFakeActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyFakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyFakeActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMyFakeActor>(OtherActor))
	{
		EscapeDirection = this->GetActorLocation() - OtherActor->GetActorLocation();
		hasCollided = true;
		SetActorLocation((GetActorLocation() - OtherActor->GetActorLocation()) + GetActorLocation());
	}
	else
	{
		hasCollided = false;
	}
}

void AMyFakeActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMyFakeActor>(OtherActor))
	{
		hasCollided = false;
	}
}
