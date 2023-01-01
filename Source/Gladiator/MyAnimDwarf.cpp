// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimDwarf.h"

void UMyAnimDwarf::NativeInitializeAnimation()
{
    //Very Important Line
    Super::NativeInitializeAnimation();

    //Cache the owning pawn for use in Tick
    OwningPawn = TryGetPawnOwner();

    entity = Cast<AEntityCharacter>(GetOwningActor());
}

void UMyAnimDwarf::NativeUpdateAnimation(float DeltaTimeX)
{
    //Very Important Line
    Super::NativeUpdateAnimation(DeltaTimeX);

    //Always Check Pointers
    if (!OwningPawn)
    {
        return;
    }

    //Set whether moving or not
    speed = OwningPawn->GetVelocity().SizeSquared();

    speedX = OwningPawn->GetVelocity().X;
    speedY = OwningPawn->GetVelocity().Y;
    
    if (entity->state == State::Death)
        isDead = true;
    else
        isDead = false;
}