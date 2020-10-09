// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
//FIRST include
#include "AimingComponent.h"
#include "StraightWeaponComponent.h"
#include "Tank.h"
#include "TrackForceAdapterComponent.h"

void ATankAIController::BeginPlay()
{

    Super::BeginPlay();

    //GET TANK
    player_pawn = _get_player_pawn();

    FString name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : AIController %s C++ BeginPlay "), *name);
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("Ticking"));

    if (tank_controlled && player_pawn && weapon_comonent)
    {
        //Tick pass : pass in for aiming ; and self action
        weapon_comonent->_ai_turning(player_pawn->GetActorLocation());
        //weapon
        if (weapon_comonent->_is_aiming_on())
            weapon_comonent->_fire();
        weapon_comonent->_reload();
        //move
        MoveToActor(player_pawn, AcceptanceRadius);
    }
}

APawn *ATankAIController::_get_player_pawn() const
{
    return GetWorld()->GetFirstPlayerController()->GetPawn();
}

// - SetPawn Override -
void ATankAIController::SetPawn(APawn *InPawn)
{
    Super::SetPawn(InPawn);
    ATank *PossessedTank = Cast<ATank>(InPawn);
    if (PossessedTank)
    {
        // TODO : EVENT
        tank_controlled = PossessedTank;
        weapon_comonent = tank_controlled->FindComponentByClass<UStraightWeaponComponent>();
        PossessedTank->OnDeath.BindUObject(
            this,
            &ATankAIController::PossessBack);
    }
};

void ATankAIController::PossessBack()
{
    // Possess();
    UE_LOG(LogTemp, Error, TEXT("DONKEY : I know My Tank is Dead."));
};
