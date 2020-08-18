// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//FIRST include

FVector UTankBarrel::_get_launch_location() const
{
    return GetSocketLocation(FName(TEXT("launch_socket")));
};

FVector UTankBarrel::_get_launch_normal() const
{
    return (GetSocketLocation(FName(TEXT("launch_socket"))) - GetSocketLocation(FName(TEXT("launch_base_socket")))).GetSafeNormal();
};

// bool _set_aiming_normal(){}

void UTankBarrel::_elevate_barrel(float relative_speed)
{
    relative_speed = FMath::Clamp<float>(relative_speed, -1, 1);
    float time = GetWorld()->GetTimeSeconds();
    //--------------------------------------------------------------------------------Debug
    // UE_LOG(LogTemp, Warning, TEXT("At %f elevation speed is %f"), time, relative_speed);

    //Angle that changed
    float elevate_angle = relative_speed * _max_elevate_speed * GetWorld()->DeltaTimeSeconds;
    //Add Relative rotation : RelativeRotation.Pitch --------------------------- get rotation right now and add new to it.
    elevate_angle = GetRelativeRotation().Pitch + elevate_angle;
    //Clamp
    elevate_angle = FMath::Clamp<float>(elevate_angle, _min_elevate_angle, _max_elevate_angle);
    //set
    SetRelativeRotation(FRotator(elevate_angle, 0, 0));

};