// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankHUD.h"
//FIRST include
#include "AimingComponent.h"
#include "Tank.h"
// #include "TankWidget.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FString name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ BeginPlay "), *name);

    //get controlled pawn
    tank_controlled = Cast<ATank>(GetPawn());
}

void ATankPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("OpenMenu", IE_Pressed, this, &ATankPlayerController::_open_pause_menu);
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //--------------------------
    // if (!ensure(tank_HUD))
    // {
    //     tank_HUD = Cast<ATankHUD>(GetHUD());
    // }
    if (tank_controlled && aiming_component)
    {
        _get_aiming_normal();
        aiming_component->_turning_to(aiming_normal);
    }
}

// - aiming -
void ATankPlayerController::_get_aiming_normal()
{
    FVector2D viewport_size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
    FVector temp{};
    DeprojectScreenPositionToWorld(
        viewport_size.X * crosshair_x,
        viewport_size.Y * crosshair_y,
        temp,
        aiming_normal);
};

// - Paus Menu -
void ATankPlayerController::_open_pause_menu()
{
    ATankHUD *hud = Cast<ATankHUD>(GetHUD());
    if (hud)
    {
        hud->_show_pause_menu();
    }
};

void ATankPlayerController::SetPawn(APawn *InPawn)
{
    Super::SetPawn(InPawn);
    ATank *PossessedTank = Cast<ATank>(InPawn);
    if (PossessedTank)
    {
        // TODO : EVENT
        tank_controlled = PossessedTank;
        
        aiming_component =
            Cast<UAimingComponent>(
                tank_controlled->GetComponentByClass(
                    UAimingComponent::StaticClass()));

        PossessedTank->OnDeath.BindUObject(
            this,
            &ATankPlayerController::PossessBack);
    }
};

void ATankPlayerController::PossessBack(){
    // Possess();
    UE_LOG(LogTemp, Error, TEXT("DONKEY : I know My Tank is Dead."))};
