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
    FString name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : %s C++ BeginPlay "), *name);
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
    // if (!ensure(tank_HUD))
    // {
    //     tank_HUD = Cast<ATankHUD>(GetHUD());
    // }
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

void ATankPlayerController::_setup_tank_widget()
{
    // tank_HUD = Cast<ATankHUD>(GetHUD());
    if (tank_HUD)
    {
        tank_HUD->_setup_tank_widget();
    }
};

void ATankPlayerController::_unset_tank_widget()
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_remove_tank_widget();
};

/* - Tank UI - 
 * - tank_widget & tank_HUD
 */
// - Turning -
//Tank : Change Aiming Box
void ATankPlayerController::_change_crosshair_color(bool flag)
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_change_crosshair_color(flag);
}

// - Weapon - (Projectile)
// - HUD : change projectile image
void ATankPlayerController::_setup_projectile()
{
    if (!ensure(tank_HUD && tank_controlled))
    {
        return;
    }
    tank_HUD->_setup_projectile(tank_controlled->_get_projectile_image());
};
//Tank : Reload Image
void ATankPlayerController::_reload_projectile()
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_reload_projectile();
};
//Tank : Ready - Claer timer
void ATankPlayerController::_reload_ready()
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_reload_ready();
}
//Tank : Hide Image
void ATankPlayerController::_hide_projectile_image()
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_hide_projectile_image();
}

// - LOCK - (Aiming)
//Tank : update
void ATankPlayerController::_update_lock_buffer(float lock_buffer_percent, AimingState aiming_state_toset)
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_update_lock_buffer(lock_buffer_percent, aiming_state_toset);
};
//Tank : _Lock draw
void ATankPlayerController::_do_lock_buffer()
{
    if (!ensure(tank_HUD))
    {
        return;
    }
    tank_HUD->_do_lock_buffer();
};
