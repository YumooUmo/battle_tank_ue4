// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"
//FIRST include

void UTankTurrent::_rotate_turrent(float relative_speed)
{
        relative_speed = FMath::Clamp<float>(relative_speed, -1, 1);
        //Angle that changed
        float rotate_angle = relative_speed * _max_rotate_speed * GetWorld()->DeltaTimeSeconds;
        //Add Relative rotation : RelativeRotation.Pitch --------------------------- get rotation right now and add new to it.
        rotate_angle = GetRelativeRotation().Yaw + rotate_angle;
        //set
        SetRelativeRotation(FRotator(0, rotate_angle, 0));

};
