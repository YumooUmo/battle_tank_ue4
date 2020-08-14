// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{

    Super::BeginPlay();

    //get_controlled_tank must return a Tank pointer.
    ATank *controlled_tank = get_controlled_tank();
    if (controlled_tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing a Tank : %s"), *(controlled_tank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possess any Tank."));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("Ticking"));
}

//return a Tank pointer
ATank *ATankPlayerController::get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::_aimming_at()
{
    if (get_controlled_tank())
    {
        //Get where we aimming at

    }
    else
    {
        return;
    }
};