// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{

    Super::BeginPlay();

    //get_controlled_tank must return a Tank pointer.
    ATank *controlled_tank = get_controlled_tank();
    if (controlled_tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController is possessing a Tank : %s"), *(controlled_tank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not possess any Tank"));
    }

    ATank *player_tank = get_player_tank();
    if (player_tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController finds a player's Tank : %s"), *(player_tank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController finds no Tank"));
    }


}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    // UE_LOG(LogTemp, Warning, TEXT("Ticking"));
}


//return a Tank pointer
ATank *ATankAIController::get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::get_player_tank() const
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