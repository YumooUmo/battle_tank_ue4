// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
UTankTrack::UTankTrack()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    // ...
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    // ...
    if (Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
        tank_mass = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetMass();
    OnComponentHit.AddDynamic(this, &UTankTrack::_grounded);
}
 
// - Force -
//sockets
bool UTankTrack::_refresh_force_sockets()
{
    //  ####    For Add Sockets Condition
    TArray<FName> names = GetAllSocketNames();
    if (names.Num() < 1)
    {
        return false;
    }
    if (names.Num() != socket_amount)
    {
        socket_amount = names.Num();
        _reset_sockets();
    }
    // FName names[3] = {"front_socket", "track_socket", "back_socket"};
    if (ensure(sockets))
        for (uint8 i = 0; i < socket_amount; i++)
        {
            sockets[i * 2] = GetSocketRotation(names[i]).Vector();
            sockets[i * 2 + 1] = GetSocketLocation(names[i]);
        }
    return true;
};
void UTankTrack::_reset_sockets()
{
    if (sockets)
    {
        delete[] sockets;
        sockets = new FVector[socket_amount * 2];
    }
}

//apply
void UTankTrack::_apply_force(float throttle)
{
    if (!_refresh_force_sockets())
    {
        UE_LOG(LogTemp, Error, TEXT("Track Sockets is Null~!"));
        return;
    }
    force = throttle * _max_force;
};
void UTankTrack::_apply_force()
{
    if (FMath::Abs(force) < 1.f)
    {
        return;
    }
    //Applly Force
    if (!sockets)
    {
        return;
    }
    for (uint8 i = 0; i < socket_amount; i++) //------------TODO
    {
        Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())
            ->AddForceAtLocation(
                (force / socket_amount) * sockets[i * 2],
                sockets[i * 2 + 1]);
    }
};

// - Friction -
void UTankTrack::_apply_side_friction()
{
    side_speed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    if (FMath::Abs(side_speed) > 0.1f)
    {
        if (side_speed > 0)
        {
            //重力加速度/2 = 4.9
            AddForce(-(GetRightVector() * tank_mass * friction_factor * 10.f));
        }
        else
        {
            AddForce(GetRightVector() * tank_mass * friction_factor * 10.f);
        }
    }
};

// - Grounded -
void UTankTrack::_grounded(UPrimitiveComponent *HitComponent,
                           AActor *OtherActor,
                           UPrimitiveComponent *OtherComponent,
                           FVector NormalImpulse,
                           const FHitResult &Hit)
{
    _apply_side_friction();
    _apply_force();
};
