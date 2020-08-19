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
    _aiming_by_normal();
    _draw_projectile_path();
}

//-----------------------------Tick----------------------------------------------
//-----------------------------------Aiming by normal
void ATankPlayerController::_aiming_by_normal()
{
    if (tank_controlled != nullptr)
    {
        FVector2D viewport_size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
        DeprojectScreenPositionToWorld(
            viewport_size.X * 0.5,
            viewport_size.Y * 0.35,
            camera_location,
            aiming_normal);
        tank_controlled->aiming_component->_aiming_by_normal(aiming_normal, camera_location);
    }
};

//Aiming by Location---------------------------------
// void ATankPlayerController::_aiming() const
// {
//     if (tank_controlled != nullptr)
//     {
//         //Get where we aimming at
//         FVector aiming_location{0.f, 0.f, 0.f};
//         _get_screen_aiming_location(aiming_location);
//         tank_controlled->aiming_component->_aiming_at(aiming_location);
//     }
// };

//-----------------------------GET------------------------------------------------

// //Aiming by Location--------------------------------
// bool ATankPlayerController::_get_screen_aiming_location(FVector &aiming_location) const
// {
//     //-----
//     FVector2D viewport_size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
//     FVector camera_location;
//     FVector aiming_direction;
//     FHitResult hit_result;
//     DeprojectScreenPositionToWorld(
//         viewport_size.X * 0.5,
//         viewport_size.Y * 0.35,
//         camera_location,
//         aiming_direction);
//     aiming_direction = aiming_direction * aiming_range;
//     if (GetWorld()->LineTraceSingleByChannel(
//             hit_result,
//             camera_location,
//             aiming_direction + camera_location,
//             ECollisionChannel::ECC_Visibility))
//     {
//         aiming_location = hit_result.Location;
//         return true;
//     }
//     else
//     {
//         aiming_location = aiming_direction + camera_location;
//         return false;
//     }
// }

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
