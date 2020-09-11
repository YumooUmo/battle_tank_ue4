// Fill out your copyright notice in the Description page of Project Settings.

#include "ForceNavMovementComponent.h"
//FIRST include
#include "Config.h"
#include "TankTrack.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UForceNavMovementComponent::UForceNavMovementComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Called when the game starts
void UForceNavMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...
}

// Called every frame
void UForceNavMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

// - Set Up -
void UForceNavMovementComponent::_setup(UTankTrack *left_track_toset, UTankTrack *right_track_toset)
{
    left_track = left_track_toset;
    right_track = right_track_toset;
};

// - MOVE -
//keyboard
void UForceNavMovementComponent::_move_keyboard()
{
    if (left_throttle == 0.f && right_throttle == 0.f && l_dest == 0.f && r_dest == 0.f)
    {
        if (move_timer.IsValid())
            GetWorld()->GetTimerManager().ClearTimer(move_timer);
        return;
    }

    float l_clamp = FMath::Clamp(l_dest, -1.42f, 1.42f);
    float r_clamp = FMath::Clamp(r_dest, -1.42f, 1.42f);

    if (left_throttle < l_clamp)
    {
        left_throttle += pace * throttle_rate;
        if (left_throttle > l_clamp)
        {
            left_throttle = l_clamp;
        }
    }
    if (left_throttle > l_clamp)
    {
        left_throttle -= pace * throttle_rate;
        if (left_throttle < l_clamp)
        {
            left_throttle = l_clamp;
        }
    }
    if (right_throttle < r_clamp)
    {
        right_throttle += pace * throttle_rate;
        if (right_throttle > r_clamp)
        {
            right_throttle = r_clamp;
        }
    }
    if (right_throttle > r_clamp)
    {
        right_throttle -= pace * throttle_rate;
        if (right_throttle < r_clamp)
        {
            right_throttle = r_clamp;
        }
    }
    _apply_force();
}
//stick
void UForceNavMovementComponent::_input_stick(float lt_x, float lt_y)
{
    if (move_timer.IsValid())
    {
        return;
    }
    FMath::Clamp<float>(lt_y, -1.f, 1.f);
    FMath::Clamp<float>(lt_x, -1.f, 1.f);
    left_throttle = lt_y - lt_x;
    right_throttle = lt_y + lt_x;
    _apply_force();
};
//set burst
void UForceNavMovementComponent::_burst(bool if_burst)
{
    burst = if_burst;
};
//apply force
void UForceNavMovementComponent::_apply_force()
{
    if (left_track)
    {
        left_track->_apply_force(_get_left_throttle());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Left track is nullptr ~!"));
    }
    if (left_track)
    {
        right_track->_apply_force(_get_right_throttle());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Right track is nullptr ~!"));
    }
}

// - Get Throttle -
float UForceNavMovementComponent::_get_left_throttle()
{
    if (burst)
    {
        return left_throttle * burst_rate;
    }
    else
    {
        return left_throttle;
    }
};
float UForceNavMovementComponent::_get_right_throttle()
{
    if (burst)
    {
        return right_throttle * burst_rate;
    }
    else
    {
        return right_throttle;
    }
};

// - Format Input -
//keyboard
void UForceNavMovementComponent::_move_forward(bool if_pressed)
{
    if (if_pressed)
    {
        l_dest += 1.f;
        r_dest += 1.f;
    }
    else
    {
        l_dest -= 1.f;
        r_dest -= 1.f;
    }
    if (!move_timer.IsValid())
        GetWorld()->GetTimerManager().SetTimer(move_timer, this,
                                               &UForceNavMovementComponent::_move_keyboard,
                                               pace, true);
};
void UForceNavMovementComponent::_move_backward(bool if_pressed)
{
    if (if_pressed)
    {
        l_dest -= 1.f;
        r_dest -= 1.f;
    }
    else
    {
        l_dest += 1.f;
        r_dest += 1.f;
    }
    if (!move_timer.IsValid())
        GetWorld()->GetTimerManager().SetTimer(move_timer, this,
                                               &UForceNavMovementComponent::_move_keyboard,
                                               pace, true);
};
void UForceNavMovementComponent::_move_left(bool if_pressed)
{
    if (if_pressed)
    {
        l_dest -= 1.f;
        r_dest += 1.f;
    }
    else
    {
        l_dest += 1.f;
        r_dest -= 1.f;
    }
    if (!move_timer.IsValid())
        GetWorld()->GetTimerManager().SetTimer(move_timer, this,
                                               &UForceNavMovementComponent::_move_keyboard,
                                               pace, true);
};
void UForceNavMovementComponent::_move_right(bool if_pressed)
{
    if (if_pressed)
    {
        l_dest += 1.f;
        r_dest -= 1.f;
    }
    else
    {
        l_dest -= 1.f;
        r_dest += 1.f;
    }
    if (!move_timer.IsValid())
        GetWorld()->GetTimerManager().SetTimer(move_timer, this,
                                               &UForceNavMovementComponent::_move_keyboard,
                                               pace, true);
};

//stick
// void _intend	----------------------------------------------	TODO
void UForceNavMovementComponent::_ai_direct(FVector intend_normal)
{
    // GetOwner()
    FVector forward = GetOwner()->GetActorForwardVector();

    float dot = FVector::DotProduct(intend_normal, forward);
    float cross = FVector::CrossProduct(intend_normal, forward).Z;
    left_throttle = FMath::Clamp<float>(dot - cross, -1.f, 1.f);
    right_throttle = FMath::Clamp<float>(dot + cross, -1.f, 1.f);
    _burst(dot > 0.8 ? true : false);
    //when intend on right of forward, cross is +, we should turn right, so left_throttle work, left + cross
    _apply_force();
}
void UForceNavMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    _ai_direct(MoveVelocity.GetSafeNormal());
};
