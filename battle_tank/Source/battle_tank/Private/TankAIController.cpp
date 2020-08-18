// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//FIRST include
#include "Tank.h"
#include "AimingComponent.h"

void ATankAIController::BeginPlay()
{

    Super::BeginPlay();

    //GET TANK
    tank_controlled = _get_controlled_tank();
    tank_of_player = _get_player_tank();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("Ticking"));
    _aiming();
}

//return a Tank pointer
ATank *ATankAIController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::_get_player_tank() const
{

    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    //--------------
    // Not necessary
    //--------------
    // auto *player_pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    // if (player_pawn)
    // {
    //     return Cast<ATank>(player_pawn);
    // }
    // else
    // {
    //     return nullptr;
    // }
}

void ATankAIController::_aiming() const
{
    if (tank_controlled != nullptr && tank_of_player != nullptr)
    {
        //aiming at player's tank
        tank_controlled->aiming_component->_aiming_at(tank_of_player->GetActorLocation());
        return;
    }
    else
    {
        return;
    }
}