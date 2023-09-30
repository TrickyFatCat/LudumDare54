// Made by Titled Goose Team during Ludum Dare 54


#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"


AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}

void AProjectileBase::BeginPlay()
{
	ProjectileMovementComponent->Velocity = MovementDirection * ProjectileMovementComponent->InitialSpeed;
	// ProjectileCollision->IgnoreActorWhenMoving(GetOwner(), true);
	
	Super::BeginPlay();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::SetProjectileData(const FVector& Direction, const int32 Damage)
{
	MovementDirection = Direction;
	Power = Damage <= 0 ? 1 : Damage;
}

