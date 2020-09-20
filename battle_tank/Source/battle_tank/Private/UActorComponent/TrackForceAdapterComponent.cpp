// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackForceAdapterComponent.h"
//FIRST include
#include "Config.h"
#include "DrawDebugHelpers.h"
#include "DriveSide.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UTrackForceAdapterComponent::UTrackForceAdapterComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    // ...
    UE_LOG(LogTemp, Warning, TEXT("DONKEY : Move C++ Construct "));
}

// Called when the game starts
void UTrackForceAdapterComponent::BeginPlay()
{
    Super::BeginPlay();
    // ...
}

// Called every frame
void UTrackForceAdapterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

/*  - Set Up -  */
//Attach
bool UTrackForceAdapterComponent::_setup_left(UChildActorComponent *left_child_component_toset)
{
    if (!left_child_component_toset && !left_child_component)
        return false;
    if (left_child_component_toset)
        left_child_component = left_child_component_toset;

    //Exists Already?
    if (left_driveside)
        return false;
    //Is ChildActor a DriveSide ?
    ADriveSide *child_actor = Cast<ADriveSide>(left_child_component->GetChildActor());
    if (!child_actor)
        return false;

    //Assign
    left_driveside = child_actor;

    //Bind to Root
    // left_driveside->_bind_constraint(Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()));
    return true;
};
bool UTrackForceAdapterComponent::_setup_right(UChildActorComponent *right_child_component_toset)
{
    if (!right_child_component_toset && !right_child_component)
        return false;
    if (right_child_component_toset)
        right_child_component = right_child_component_toset;

    //Exists Already?
    if (right_driveside)
        return false;
    //Is ChildActor a DriveSide ?
    ADriveSide *child_actor = Cast<ADriveSide>(right_child_component->GetChildActor());
    if (!child_actor)
        return false;

    //Assign
    right_driveside = child_actor;

    //Bind to Root
    // right_driveside->_bind_constraint(Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()));
    return true;
};

//Attach
bool UTrackForceAdapterComponent::_attach_left(AActor *child_actor)
{
    // //Already Bind ?
    // if (left_driveside)
    //     return false;
    //Child Component Exist ?
    if (!left_child_component)
        return false;

    //Is ChildActor a DriveSide ?
    if (!Cast<ADriveSide>(child_actor))
        return false;

    //                    #### TODO : Apply Instance Data
    left_child_component->SetChildActorClass(child_actor->GetClass(), child_actor);
    TArray<AActor *> children;
    child_actor->GetAllChildActors(children);
    for (AActor *child : children)
    {
        child->Destroy();
    }
    child_actor->Destroy();
    left_child_component->CreateChildActor();

    _setup_left();
    //Set Transform : abs Location / abs Rotation / abs Scale

    //Child Bind
    // left_driveside->_bind_constraint(Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()));

    return true;
};
bool UTrackForceAdapterComponent::_attach_right(AActor *child_actor)
{
    // //Already Bind ?
    // if (left_driveside)
    //     return false;
    //Child Component Exist ?
    if (!right_child_component)
        return false;

    //Is ChildActor a DriveSide ?
    if (!Cast<ADriveSide>(child_actor))
        return false;

    //                           #### TODO : Apply Instance Data
    right_child_component->SetChildActorClass(child_actor->GetClass(), child_actor);
    TArray<AActor *> children;
    child_actor->GetAllChildActors(children);
    for (AActor *child : children)
    {
        child->Destroy();
    }
    child_actor->Destroy();
    right_child_component->CreateChildActor();

    _setup_right();
    //Set Transform : abs Location / abs Rotation / abs Scale

    //Child Bind
    // right_driveside->_bind_constraint(Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()));

    return true;
};

//detach
void UTrackForceAdapterComponent::_detach_left_driveside()
{
    if (!left_driveside)
        return;
    FActorSpawnParameters parameters;
    parameters.Template = left_driveside;
    //Destroy
    TArray<AActor *> children;
    left_child_component->GetChildActor()->GetAllChildActors(children);
    for (AActor *child : children)
    {
        child->Destroy();
    }
    left_child_component->GetChildActor()->Destroy();
    //set nullptr
    left_driveside = nullptr;

    test_left = GetWorld()->SpawnActor<ADriveSide>(left_child_component->GetChildActorClass(), parameters);
    test_left->SetOwner(test_left);

    if (left_child_component->GetChildActor())
        UE_LOG(LogTemp, Error, TEXT("DONKEY : Detach Fail ~!"));
    // left_driveside = nullptr;
};
void UTrackForceAdapterComponent::_detach_right_driveside()
{
    if (!right_driveside)
        return;
    FActorSpawnParameters parameters;
    parameters.Template = right_driveside;
    //Destroy
    TArray<AActor *> children;
    right_child_component->GetChildActor()->GetAllChildActors(children);
    for (AActor *child : children)
    {
        child->Destroy();
    }
    right_child_component->GetChildActor()->Destroy();
    //set nullptr
    right_driveside = nullptr;

    test_right = GetWorld()->SpawnActor<ADriveSide>(right_child_component->GetChildActorClass(), parameters);
    test_right->SetOwner(test_right);
};

//detach
void UTrackForceAdapterComponent::_attach_test()
{
    _attach_left(test_left);
    _attach_right(test_right);
};

/*  - Move Input Format -   */

// - MOVE -
//keyboard
void UTrackForceAdapterComponent::_move_keyboard()
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
void UTrackForceAdapterComponent::_input_stick(float lt_x, float lt_y)
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
void UTrackForceAdapterComponent::_burst(bool if_burst)
{
    burst = if_burst;
};
//apply force
void UTrackForceAdapterComponent::_apply_force()
{
    if (left_driveside)
    {
        if (burst)
            left_driveside->_apply_force(left_throttle * burst_rate);
        else
            left_driveside->_apply_force(left_throttle);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Left track is nullptr 1 ~!"));
    }
    if (right_driveside)
    {
        if (burst)
            right_driveside->_apply_force(right_throttle * burst_rate);
        else
            right_driveside->_apply_force(right_throttle);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Right track is nullptr ~!"));
    }
}
void UTrackForceAdapterComponent::_stop_apply_force()
{
    if (left_driveside)
    {
        left_driveside->_apply_force(0.f);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Left track is nullptr 2 ~!"));
    }
    if (left_driveside)
    {
        right_driveside->_apply_force(0.f);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Right track is nullptr ~!"));
    }
    _burst(false);
};
//Brake
void UTrackForceAdapterComponent::_brake(bool if_brake)
{
    if (left_driveside)
        left_driveside->_brake(if_brake);
    if (right_driveside)
        right_driveside->_brake(if_brake);
};

// - Format Input -
//keyboard
void UTrackForceAdapterComponent::_move_forward(bool if_pressed)
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
                                               &UTrackForceAdapterComponent::_move_keyboard,
                                               pace, true);
};
void UTrackForceAdapterComponent::_move_backward(bool if_pressed)
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
                                               &UTrackForceAdapterComponent::_move_keyboard,
                                               pace, true);
};
void UTrackForceAdapterComponent::_move_left(bool if_pressed)
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
                                               &UTrackForceAdapterComponent::_move_keyboard,
                                               pace, true);
};
void UTrackForceAdapterComponent::_move_right(bool if_pressed)
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
                                               &UTrackForceAdapterComponent::_move_keyboard,
                                               pace, true);
};
//stick
// void _intend	----------------------------------------------	TODO
void UTrackForceAdapterComponent::_ai_direct(FVector intend_normal)
{
    // GetOwner()
    FVector forward = GetOwner()->GetActorForwardVector();
    // UE_LOG(LogTemp, Error, TEXT("DONKEY : Intend vector %s"), *(intend_normal.ToString()))
    float dot = FVector::DotProduct(intend_normal, forward);
    float cross = FVector::CrossProduct(intend_normal, forward).Z;
    left_throttle = FMath::Clamp<float>(dot - cross, -1.f, 1.f);
    right_throttle = FMath::Clamp<float>(dot + cross, -1.f, 1.f);
    // UE_LOG(LogTemp, Error, TEXT("DONKEY : Left %f"), left_throttle);
    //when intend on right of forward, cross is +, we should turn right, so left_throttle work, left + cross
    if (dot > 0.9)
    {
        _burst(true);
    }
    else
    {
        _burst(false);
    }
    _apply_force();
    GetWorld()->GetTimerManager().SetTimer(move_timer, this,
                                           &UTrackForceAdapterComponent::_stop_apply_force,
                                           pace * 5, false);
}
void UTrackForceAdapterComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    _ai_direct(MoveVelocity.GetSafeNormal());
};
