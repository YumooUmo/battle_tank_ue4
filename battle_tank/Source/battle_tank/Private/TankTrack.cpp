// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::_refresh_force_sockets()
{
    //  ####    For Add Sockets Condition
    // TArray<FName> names = GetAllSocketNames();
    // if(names.Num() != socket_amount){
    //     _reset_sockets();
    // }
    // socket_amount = names.Num();
    FName names[3] = {"front_socket", "track_socket", "back_socket"};

    for (int i = 0; i < socket_amount; i++)
    {
        sockets[i * 2] = GetSocketRotation(names[i]).Vector();
        sockets[i * 2 + 1] = GetSocketLocation(names[i]);
        // UE_LOG(LogTemp, Warning, TEXT("%s Socket Location is : %s ~!"), *(names[i].ToString()), *(sockets[i * 2 + 1].ToString()));
    }
};

void UTankTrack::_reset_sockets()
{
    if (sockets)
    {
        delete[] sockets;
        sockets = new FVector[socket_amount * 2];
    }
}

void UTankTrack::_apply_force(float throttle)
{
    // UE_LOG(LogTemp, Error, TEXT(" Root is : %s ~!"), *(GetOwner()->GetRootComponent()->GetName()));
    _refresh_force_sockets();
    //Applly Force To Left Track
    for (int i = 0; i < socket_amount; i++) //------------TODO
    {
        Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())
            ->AddForceAtLocation(
                throttle * (_max_force / socket_amount) * sockets[i * 2],
                sockets[i * 2 + 1]);
    }
};