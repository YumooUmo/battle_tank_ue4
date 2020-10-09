// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectile.h"
//FIRST include
#include "Config.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"

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
	launch_blast->AttachToComponent(projectile_mesh,
									FAttachmentTransformRules::KeepRelativeTransform);

	impact_blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	impact_blast->bAutoActivate = false;
	impact_blast->AttachToComponent(projectile_mesh,
									FAttachmentTransformRules::KeepRelativeTransform);

	pawn_blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("PawnBlast"));
	pawn_blast->bAutoActivate = false;
	pawn_blast->AttachToComponent(projectile_mesh,
								  FAttachmentTransformRules::KeepRelativeTransform);

	radial_force = CreateDefaultSubobject<URadialForceComponent>(FName("RadialForce"));
	radial_force->bAutoActivate = false;
	radial_force->AttachToComponent(projectile_mesh,
									FAttachmentTransformRules::KeepRelativeTransform);
};

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	_set_mass(mass_toset);
	projectile_mesh->OnComponentHit.AddDynamic(this, &ATankProjectile::_hit);
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
};

// - GET -
//get mass
float ATankProjectile::_get_mass()
{
	if (mass_toset > 0.f)
		return mass_toset;
	return 1.f;
};
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
//set controller that take this projectile
void ATankProjectile::_set_controller(AController *InController)
{
	controller = Cast<APlayerController>(InController);
};
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
		projectile->AddImpulse(GetActorForwardVector() * launch_force);
		radial_force->FireImpulse();

		GetWorld()->GetTimerManager().SetTimer(destroy_timer, this,
											   &ATankProjectile::_take_damage,
											   life_span, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Potential Error : 1/ Root Component of %s is not moveable. 2/ Root Component is Not a Primitive Component."), *(this->GetName()));
	}
};

// - Hit -
void ATankProjectile::_hit(UPrimitiveComponent *HitComponent,
						   AActor *OtherActor,
						   UPrimitiveComponent *OtherComponent,
						   FVector NormalImpulse,
						   const FHitResult &Hit)
{
	//Blast
	if (!bHit)
	{
		if (impact_blast)
			// UE_LOG(LogTemp, Error, TEXT("DONKEY : Impact Blast"));
			impact_blast->Activate();
		if (radial_force)
		{
			// UE_LOG(LogTemp, Error, TEXT("DONKEY : Radial Force"));
			radial_force->FireImpulse();
		}
		bHit = true;
	}
	//Hit Damage
	APawn *HitPawn = Cast<APawn>(Hit.Actor);
	if (HitPawn)
	{
		FVector CurrentVelocity = GetVelocity();
		if (CurrentVelocity.Size() > min_speed_for_damage)
		{
			UGameplayStatics::ApplyDamage(HitPawn,
										  FVector::DotProduct(Hit.Normal, CurrentVelocity) * mass_toset,
										  nullptr,
										  nullptr,
										  UDamageType::StaticClass());

			if (launch_blast)
				launch_blast->Deactivate();
		}
	//Blast
		if (pawn_blast)
		{
			// UE_LOG(LogTemp, Error, TEXT("DONKEY : Pawn Blast"));
			pawn_blast->Activate();
		}
	}
};

// - Destroy -
void ATankProjectile::_take_damage()
{
	this->Destroy();
};