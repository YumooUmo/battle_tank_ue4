// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    
    Super::BeginPlay();
}

ATank *ATankPlayerController::get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}