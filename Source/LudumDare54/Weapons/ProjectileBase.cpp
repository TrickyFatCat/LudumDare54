// Made by Titled Goose Team during Ludum Dare 54


#include "ProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LudumDare54/Components/HitPointsComponent.h"


AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}

void AProjectileBase::BeginPlay()
{
	ProjectileMovementComponent->Velocity = MovementDirection * ProjectileMovementComponent->InitialSpeed;
	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);

	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::HandleProjectileHit);

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

void AProjectileBase::HandleProjectileHit(UPrimitiveComponent* HitComponent,
                                          AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp,
                                          FVector NormalImpulse,
                                          const FHitResult& Hit)
{
	if (OtherActor)
	{
		UHitPointsComponent* HitPointsComponent = OtherActor->FindComponentByClass<UHitPointsComponent>();

		if (HitPointsComponent)
		{
			HitPointsComponent->DecreaseValue(Power);
		}
	}

	Destroy();
}
