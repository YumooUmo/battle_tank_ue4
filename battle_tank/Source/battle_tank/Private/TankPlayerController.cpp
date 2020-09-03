// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//FIRST include
#include "MenuHUD.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //get possessed tank
    tank_controlled = _get_controlled_tank();
}

void ATankPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("OpenMenu", IE_Pressed, this, &ATankPlayerController::_open_menu);
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //--------------------------
    if (tank_controlled != nullptr)
    {
        _get_aiming_normal();
        tank_controlled->_controller_do(aiming_normal);
    }
}

//-----------------------------Tick----------------------------------------------
//-----------------------------------Aiming by normal
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

//return a Tank pointer
ATank *ATankPlayerController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

//-----------------------------Menu------------------------------------------
void ATankPlayerController::_open_menu()
{
    if (AMenuHUD *menu_HUD = Cast<AMenuHUD>(GetHUD()))
    {
        menu_HUD->_show_menu();
    }
};


