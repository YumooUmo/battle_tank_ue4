// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//FIRST include
#include "Tank.h"
#include "TankHUD.h"
// #include "TankWidget.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //get possessed tank
    tank_controlled = Cast<ATank>(GetPawn());
    tank_HUD = Cast<ATankHUD>(GetHUD());
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

    if (tank_controlled != nullptr)
    {
        _get_aiming_normal();
        tank_controlled->_set_aiming_normal(aiming_normal);
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

//-----------------------------Menu------------------------------------------
void ATankPlayerController::_open_pause_menu()
{
    if (tank_HUD)
    {
        tank_HUD->_show_pause_menu();
    }
};

void ATankPlayerController::_set_current_widget(UTankWidget *widget_toset)
{
    if (!tank_HUD)
    {
        return;
    }
    tank_HUD->_set_current_widget(widget_toset);
};
