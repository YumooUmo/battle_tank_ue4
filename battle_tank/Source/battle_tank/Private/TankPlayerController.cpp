// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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
    _aiming();
}

//return a Tank pointer
ATank *ATankPlayerController::_get_controlled_tank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::_aiming() const
{
    if (tank_controlled != nullptr)
    {
        //Get where we aimming at
        FVector aiming_vector{0.f, 0.f, 0.f};
        _get_screen_aiming_vector(aiming_vector);
        tank_controlled->_aiming_at(aiming_vector);
        return;
    }
    else
    {
        return;
    }
};

bool ATankPlayerController::_get_screen_aiming_vector(FVector &vector_screen_aiming) const
{
    //-----
    int32 viewport_size_x = 0.f;
    int32 viewport_size_y = 0.f;
    FVector camera_location = PlayerCameraManager->GetCameraLocation();
    FVector direction_screen_aiming{0.f, 0.f, 0.f};
    // FVector vector_screen_aiming = (0.f, 0.f, 0.f);
    FHitResult hit_result;

    ATankPlayerController::GetViewportSize(viewport_size_x, viewport_size_y);

    //Transform screen crosshair to UWorld Direction Vector
    APlayerController::DeprojectScreenPositionToWorld(
        viewport_size_x * 0.5,
        viewport_size_y * 0.35,
        camera_location,
        direction_screen_aiming);
    //Multi by range
    direction_screen_aiming *= aiming_range;
    //Line trace single hit point
    if (GetWorld()->LineTraceSingleByChannel(
            hit_result,
            camera_location,
            direction_screen_aiming,
            ECollisionChannel::ECC_Visibility))
    {
        vector_screen_aiming = hit_result.Location;
        return true;
    }
    else
    {
        vector_screen_aiming = direction_screen_aiming;
        return false;
    }
}