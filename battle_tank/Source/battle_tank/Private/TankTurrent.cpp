// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"
//FIRST include

void UTankTurrent::_rotate_turrent(float delta_yaw)
{

        if (delta_yaw > 180.f)
        {
                delta_yaw = delta_yaw - 360.f;
        }
        if (delta_yaw < -180.f)
        {
                delta_yaw = delta_yaw + 360.f;
        }
        /* BUG fixed :Format Yaw change direction 
        *  When turning from -170 -> 170, 
        *  angle addition is +340, but ACTUALLY should be -20.
        */

        if (FMath::Abs(GetOwner()->GetActorRotation().Roll) > 90.f)
        {
                delta_yaw = -delta_yaw;
        }
        /*  #### BUG fixed : When tank rolling-over, barrel turing to reverse direction. 
        *Becuase we Add world rotation pitch to relative rotation pitch.
        *Method is : When tank rolling-over, pass in parameter -dest_pitch.
        */

        delta_yaw = FMath::Clamp<float>(delta_yaw*5.f, -_max_rotate_speed, _max_rotate_speed);
        //Angle that changed
        float rotate_angle = delta_yaw * GetWorld()->DeltaTimeSeconds;
        //Add Relative rotation : RelativeRotation.Pitch --------------------------- get rotation right now and add new to it.
        rotate_angle = GetRelativeRotation().Yaw + rotate_angle;
        //set
        SetRelativeRotation(FRotator(0, rotate_angle, 0));
};
