// Fill out your copyright notice in the Description page of Project Settings.

#include "ForceNavMovementComponent.h"
//FIRST include

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

//		---		PRIVATE : self action
//Throttle

//		---		PUBLIC : Move
bool UForceNavMovementComponent::_should_move()
{
    if (left_throttle == 0.f && right_throttle == 0.f && l_dest == 0.f && r_dest == 0.f)
    {
        return false;
    }
    else
    {
        _do_move();
        return true;
    }
};

void UForceNavMovementComponent::_do_move()
{
    float l_clamp = FMath::Clamp<float>(l_dest, -1.f, 1.f);
    float r_clamp = FMath::Clamp<float>(r_dest, -1.f, 1.f);

    if (left_throttle < l_clamp)
    {
        left_throttle += GetWorld()->DeltaTimeSeconds * throttle_rate;
        if (left_throttle > l_clamp)
        {
            left_throttle = l_clamp;
        }
    }
    if (left_throttle > l_clamp)
    {
        left_throttle -= GetWorld()->DeltaTimeSeconds * throttle_rate;
        if (left_throttle < l_clamp)
        {
            left_throttle = l_clamp;
        }
    }
    if (right_throttle < r_clamp)
    {
        right_throttle += GetWorld()->DeltaTimeSeconds * throttle_rate;
        if (right_throttle > r_clamp)
        {
            right_throttle = r_clamp;
        }
    }
    if (right_throttle > r_clamp)
    {
        right_throttle -= GetWorld()->DeltaTimeSeconds * throttle_rate;
        if (right_throttle < r_clamp)
        {
            right_throttle = r_clamp;
        }
    }
}

//Output Throttle
float UForceNavMovementComponent::_get_left_throttle()
{
    if (burst)
    {
        UE_LOG(LogTemp, Error, TEXT(" Left is %f ~!"), left_throttle * burst_rate);
        UE_LOG(LogTemp, Error, TEXT(" Left Dest is %f ~!"), l_dest * burst_rate);
        return left_throttle * burst_rate;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT(" Left is %f ~!"), left_throttle);
        UE_LOG(LogTemp, Error, TEXT(" Left Dest is %f ~!"), l_dest);
        return left_throttle;
    }
};
float UForceNavMovementComponent::_get_right_throttle()
{
    if (burst)
    {
        UE_LOG(LogTemp, Error, TEXT(" Right is %f ~!"), right_throttle * burst_rate);
        UE_LOG(LogTemp, Error, TEXT(" Right Dest is %f ~!"), r_dest * burst_rate);
        return right_throttle * burst_rate;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT(" Right is %f ~!"), right_throttle);
        UE_LOG(LogTemp, Error, TEXT(" Right Dest is %f ~!"), r_dest);
        return right_throttle;
    }
};

//Format Input
void UForceNavMovementComponent::_move_forward(bool if_move)
{
    if (if_move)
    {
        l_dest += 1.f;
        r_dest += 1.f;
    }
    else
    {
        l_dest -= 1.f;
        r_dest -= 1.f;
    }
};
void UForceNavMovementComponent::_move_backward(bool if_move)
{
    if (if_move)
    {
        l_dest -= 1.f;
        r_dest -= 1.f;
    }
    else
    {
        l_dest += 1.f;
        r_dest += 1.f;
    }
};
void UForceNavMovementComponent::_move_left(bool if_move)
{
    if (if_move)
    {
        l_dest -= 1.f;
        r_dest += 1.f;
    }
    else
    {
        l_dest += 1.f;
        r_dest -= 1.f;
    }
};
void UForceNavMovementComponent::_move_right(bool if_move)
{
    if (if_move)
    {
        l_dest += 1.f;
        r_dest -= 1.f;
    }
    else
    {
        l_dest -= 1.f;
        r_dest += 1.f;
    }
};
void UForceNavMovementComponent::_burst(bool if_burst)
{
    burst = if_burst;
};

// void _intend	----------------------------------------------	TODO

void UForceNavMovementComponent::_ai_direct(FVector intend_normal)
{
    // GetOwner()
    FVector forward = GetOwner()->GetActorForwardVector();
    float dot = FVector::DotProduct(intend_normal, forward);
    float cross = FVector::CrossProduct(intend_normal, forward).Z;
    //when intend on right of forward, cross is +, we should turn right, so left_throttle work, left + cross
    l_dest = FMath::Clamp<float>(dot + cross, -1.f, 1.f);
    r_dest = FMath::Clamp<float>(dot - cross, -1.f, 1.f);
}
void UForceNavMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    _ai_direct(MoveVelocity.GetSafeNormal());
};
