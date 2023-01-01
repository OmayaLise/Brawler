// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDayNightCycle.h"

// Sets default values
AMyDayNightCycle::AMyDayNightCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyDayNightCycle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyDayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (lightSource)
	{
		float angleControl =+ (DeltaTime * turnRate);
		lightSource->AddActorLocalRotation(FRotator(angleControl, 0,0));
		if (angleControl <170 )
		{
			angleControl = 10;
		}

	}
	if (sun)
	{
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
}

