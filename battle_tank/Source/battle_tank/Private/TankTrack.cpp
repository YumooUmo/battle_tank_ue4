// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::_set_throttle(float throttle)
{
    throttle = FMath::Clamp<float>(throttle, -1, 1);

    Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())
        ->AddForceAtLocation(
            throttle * _max_force * GetForwardVector(),
            GetComponentLocation());
};