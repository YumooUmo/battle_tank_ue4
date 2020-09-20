// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankHUD.h"
//FIRST include
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
    if (tank_controlled != nullptr)
    {
        _get_aiming_normal();
        tank_controlled->_turning_to(aiming_normal);
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
