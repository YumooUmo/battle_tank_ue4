// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//FIRST include

FVector UTankBarrel::_get_launch_location() const
{
    return GetSocketLocation(FName(TEXT("launch_socket")));
};

FVector UTankBarrel::_get_launch_normal() const
{
    return GetForwardVector();
};

// bool _set_aiming_normal(){}

void UTankBarrel::_elevate_barrel(float delta_pitch)
{
    if (FMath::Abs(GetOwner()->GetActorRotation().Roll) > 90.f)
    {
        delta_pitch = -delta_pitch;
    }
    /*  #### BUG fixed : When tank rolling-over, barrel turing to reverse direction. 
        *Becuase we Add world rotation pitch to relative rotation pitch.
        *Method is : When tank rolling-over, pass in parameter -dest_pitch.
        */

    if (FMath::Abs(delta_pitch) > 0.05f)
    {
        //Clamp to 1 °/s                               #### TODO : adjustable Curve
        delta_pitch = FMath::Clamp<float>(delta_pitch * 10.f,
                                          -_max_elevate_speed,
                                          _max_elevate_speed) *
                      GetWorld()->DeltaTimeSeconds;
        //Angle that changed
    }
    //Add Relative rotation.
    float relative_angle = GetRelativeRotation().Pitch + delta_pitch;

    //Clamp
    relative_angle = FMath::Clamp<float>(relative_angle, _min_relative_angle, _max_relative_angle);

    //set
    SetRelativeRotation(FRotator(relative_angle, 0, 0));
};