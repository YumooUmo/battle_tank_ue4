// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//FIRST include
#include "Tank.h"

void ATankAIController::BeginPlay()
{

    Super::BeginPlay();

    //GET TANK
    tank_controlled = _get_controlled_tank();
    player_pawn = _get_player_tank();

    FString name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : AIController %s C++ BeginPlay "), *name);
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("Ticking"));

    if (tank_controlled && player_pawn)
    {
        //Tick pass : pass in for aiming ; and self action
        tank_controlled->_ai_turning(player_pawn->GetActorLocation());
        //weapon
        if (tank_controlled->_is_aiming_on())
            tank_controlled->_fire();
        tank_controlled->_reload();
        //move
        MoveToActor(player_pawn, AcceptanceRadius);
    }
}

//return a Tank pointer
ATank *ATankAIController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

APawn *ATankAIController::_get_player_tank() const
{
    return GetWorld()->GetFirstPlayerController()->GetPawn();
}
