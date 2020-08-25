// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
//FIRST include
#include "AimingComponent.h"
#include "Tank.h"
#include "TankTrack.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //get possessed tank
    tank_controlled = _get_controlled_tank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //--------------------------
    _aiming_by_viewport();
    _draw_projectile_path();
}

//-----------------------------Tick----------------------------------------------
//-----------------------------------Aiming by normal
void ATankPlayerController::_aiming_by_viewport()
{
    if (tank_controlled != nullptr)
    {
        FVector camera_location{0};
        FVector2D viewport_size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
        DeprojectScreenPositionToWorld(
            viewport_size.X * crosshair_x,
            viewport_size.Y * crosshair_y,
            camera_location,
            aiming_normal);
        tank_controlled->aiming_component->_aiming_by_viewport(aiming_normal);
    }
};

//return a Tank pointer
ATank *ATankPlayerController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

//-----------------------------PLAY------------------------------------------
//Draw Projectile Path
void ATankPlayerController::_draw_projectile_path()
{
    tank_controlled->aiming_component->_draw_projectile_path();
}

//SET weapon number : Change Weapon , projectile number
void ATankPlayerController::_set_projectile_number(int projectile_number)
{
    tank_controlled->_set_projectile_number(projectile_number);
};

//SET exchange weapon
void ATankPlayerController::_exchange_projectile()
{
    tank_controlled->_exchange_projectile();
};

//Fire()
void ATankPlayerController::_fire() //---------	TODO ------------Refact : using Template to Fire with differen projectile number
{
    tank_controlled->_fire();
};

//Reload
void ATankPlayerController::_reload()
{
    tank_controlled->_reload();
};

//Move
void ATankPlayerController::_set_left_throttle(float throttle)
{
    tank_controlled->left_track->_set_throttle(throttle);
};
void ATankPlayerController::_set_right_throttle(float throttle)
{
    tank_controlled->right_track->_set_throttle(throttle);
};
