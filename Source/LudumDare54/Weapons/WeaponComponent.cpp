// Made by Titled Goose Team during Ludum Dare 54


#include "WeaponComponent.h"

#include "ProjectileBase.h"


UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponComponent::BeginPlay()
{
	ShotDelay = RateOfFire <= 0.f ? 1.f : 1.f / RateOfFire;
	Super::BeginPlay();
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UWeaponComponent::MakeShot()
{
	if (!ProjectileClass)
	{
		return false;
	}

	FVector StartPoint = GetComponentLocation();
	FVector EndPoint = TargetLocation;
	FVector Direction = (EndPoint - StartPoint).GetSafeNormal();

	for (int32 i = 0; i <= ProjectilesPerShot; i++)
	{
		const FTransform SpawnTransform(FRotator::ZeroRotator, StartPoint);
		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileClass, SpawnTransform);

		if (Projectile)
		{
			Projectile->SetProjectileData(Direction, DamagePerProjectile);
			Projectile->SetOwner(GetOwner());
			Projectile->FinishSpawning(SpawnTransform);
		}
	}

	return true;
}

bool UWeaponComponent::StartShooting()
{
	if (bIsShooting || !bCanShoot)
	{
		return false;
	}

	if (!MakeShot())
	{
		return false;
	}

	bIsShooting = true;
	GetWorld()->GetTimerManager().SetTimer(ShotDelayTimer,
	                                       this,
	                                       &UWeaponComponent::HandleShotDelayTimer,
	                                       ShotDelay,
	                                       true);
	return true;
}

bool UWeaponComponent::StopShooting()
{
	if (!bIsShooting)
	{
		return false;
	}

	bIsShooting = false;
	bCanShoot = false;
	return true;
}

void UWeaponComponent::HandleShotDelayTimer()
{
	if (!bCanShoot)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShotDelayTimer);
		bCanShoot = true;
		return;
	}

	MakeShot();
}
