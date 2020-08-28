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
    FName names[3] = {"front_socket","track_socket","back_socket"};

    for (int i = 0; i < socket_amount; i++)
    {
            sockets[i*2] = GetSocketRotation(names[i]).Vector();
            sockets[i*2+1] = GetSocketLocation(names[i]);
    }

};

void UTankTrack::_reset_sockets(){
    if (sockets){
        delete[] sockets;
        sockets = new FVector[socket_amount * 2];
    }
}

