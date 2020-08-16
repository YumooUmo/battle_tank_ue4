// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

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
    _draw_projectile_path();
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
        FVector aiming_location{0.f, 0.f, 0.f};
        _get_screen_aiming_location(aiming_location);
        tank_controlled->_aiming_at(aiming_location);
        return;
    }
    else
    {
        return;
    }
};

bool ATankPlayerController::_get_screen_aiming_location(FVector &aiming_location) const
{
    //-----
    FVector2D viewport_size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
    FVector camera_location;
    FVector aiming_direction;
    FHitResult hit_result;

    DeprojectScreenPositionToWorld(
        viewport_size.X * 0.5,
        viewport_size.Y * 0.35,
        camera_location,
        aiming_direction);
    aiming_direction = aiming_direction * aiming_range;

    // //----------------------------------------------------------Debug
    // UE_LOG(LogTemp, Warning, TEXT("Camera Location is : %s"), *(camera_location.ToString()));
    // UE_LOG(LogTemp, Warning, TEXT("Out Location is : %s"), *(out_location.ToString()));
    // //----------------------------------------------------------------

    //Get Hit Point : Line trace single by channel, in hit_result.
    if (GetWorld()->LineTraceSingleByChannel(
            hit_result,
            camera_location,
            aiming_direction + camera_location,
            ECollisionChannel::ECC_Visibility))
    {

        aiming_location = hit_result.Location; // should be barrel launch piont-----Not here

        // //---------------------------------------------Debug
        // UE_LOG(LogTemp, Error, TEXT("Tank Location is : %s"), *(tank_controlled->GetActorLocation().ToString()));
        // DrawDebugLine(
        //     GetWorld(),
        //     tank_controlled->GetActorLocation(), // should be barrel launch piont-----Not here
        //     aiming_location,
        //     FColor::Blue,
        //     false,
        //     0.0f,
        //     0.0f,
        //     20.0f);
        // //----------------------------------------------------

        return true;
    }
    else
    {
        aiming_location = aiming_direction + camera_location;
        return false;
    }
}

void ATankPlayerController::_draw_projectile_path()
{
    tank_controlled->_draw_projectile_path();
}