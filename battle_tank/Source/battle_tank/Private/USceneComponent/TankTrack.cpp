// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
//include first

UTankTrack::UTankTrack()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    // ...
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : Track C++ Construct "));
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    // ...
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : Track C++ BeginPlay "));
    // OnComponentHit.AddDynamic(this, &UTankTrack::_grounded);
}
