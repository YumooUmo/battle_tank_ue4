// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
FVector **UTankTrack::_get_track_sockets()
{
    if(!track_on){
    sockets = new FVector *[3];
    *sockets = new FVector[2];
    _refresh_force_sockets();
    track_on = true;
    return sockets;
    }else{
        return nullptr;
    }
}

void UTankTrack::_free_track_sockets()
{
    if(track_on){
    delete[] * sockets;
    delete[] sockets;
    track_on = false;
    }
}

void UTankTrack::_refresh_force_sockets()
{
    if (sockets != nullptr)
    {
        sockets[0][0] = GetSocketRotation(FName(TEXT("front_socket"))).Vector();
        sockets[0][1] = GetSocketLocation(FName(TEXT("front_socket")));

        sockets[1][0] = GetSocketRotation(FName(TEXT("track_socket"))).Vector();
        sockets[1][1] = GetSocketLocation(FName(TEXT("track_socket")));

        sockets[2][0] = GetSocketRotation(FName(TEXT("back_socket"))).Vector();
        sockets[2][1] = GetSocketLocation(FName(TEXT("back_socket")));
    }
};
