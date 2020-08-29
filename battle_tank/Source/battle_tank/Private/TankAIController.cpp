// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//FIRST include
#include "Tank.h"

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

    //Tick pass : pass in for aiming ; and self action
    tank_controlled->_controller_do((tank_of_player->GetActorLocation() - tank_controlled->_get_launch_location()).GetSafeNormal());
    //weapon
    tank_controlled->_fire();
    tank_controlled->_reload();
    //move
    MoveToActor(tank_of_player, AcceptanceRadius);
}

//return a Tank pointer
ATank *ATankAIController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::_get_player_tank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
