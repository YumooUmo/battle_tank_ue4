// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectile.h"
//FIRST include
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATankProjectile::ATankProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//SET move_component
	// projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("projectile_movement_component")));
	// projectile_movement_component->bAutoActivate = false;
	projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	SetRootComponent(projectile_mesh);
	projectile_mesh->SetNotifyRigidBodyCollision(true);
	projectile_mesh->SetVisibility(true);
	projectile_mesh->SetSimulatePhysics(true);
	
	launch_blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	launch_blast->AttachTo(projectile_mesh);
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	_set_mass(mass_toset);
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// - GET -
// //get ammo
// uint8 ATankProjectile::_get_ammo_defaults()
// {
// 	return ammo_defaults;
// }
//get mass
float ATankProjectile::_get_mass()
{
	if (mass_toset > 0.f)
		return mass_toset;
	return 1.f;
}
//get reload time
float ATankProjectile::_get_reload_time()
{
	return reload_time;
};
//get image
UTexture2D *ATankProjectile::_get_projectile_image()
{
	return projectile_image;
}
//get speed
float ATankProjectile::_get_launch_speed(float launch_force)
{
	if (launch_force_override > 0)
	{
		launch_force = launch_force_override;
	}
	if (mass_toset > 0)
		return launch_force / mass_toset;
	return 1.f;
};

// - SET -
//set image
void ATankProjectile::_set_projectile_image(UTexture2D *projectile_image_toset)
{
	projectile_image = projectile_image_toset;
};
//set mass
void ATankProjectile::_set_mass(float mass_override)
{
	UPrimitiveComponent *root = Cast<UPrimitiveComponent>(RootComponent);
	if (ensure(root))
	{
		root->SetMassOverrideInKg(NAME_None, mass_override, true);
	}
};
// //set ammo
// void ATankProjectile::_set_ammo_defaults(uint8 ammo_toset)
// {
// 	_set_ammo_defaults = ammo_toset;
// };

//Launch
void ATankProjectile::_launch(float launch_force)
{
	if (launch_force_override > 0)
	{
		launch_force = launch_force_override;
	}
	UPrimitiveComponent *projectile;
	projectile = Cast<UPrimitiveComponent>(this->GetRootComponent());
	if (this->IsRootComponentMovable())
	{
		// UE_LOG(LogTemp,Error,TEXT("ForwardVector Component of %s is "),*(GetActorForwardVector().ToString()));
		UE_LOG(LogTemp, Warning, TEXT("DONKEY :Projectile Add Impulse  %f ~! "), launch_force);
		projectile->AddImpulse(GetActorForwardVector() * launch_force);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Potential Error : 1/ Root Component of %s is not moveable. 2/ Root Component is Not a Primitive Component."), *(this->GetName()));
	}
};
