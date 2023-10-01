// Made by Titled Goose Team during Ludum Dare 54


#include "WeaponBase.h"

#include "ProjectileBase.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	ShotDelay = RateOfFire <= 0.f ? 1.f : 1.f / RateOfFire;
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeaponBase::MakeShot()
{
	if (!ProjectileClass)
	{
		return false;
	}

	const FVector StartPoint = GetActorLocation();
	const FVector Direction = (TargetPoint - StartPoint).GetSafeNormal();

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

bool AWeaponBase::StartShooting()
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
	                                       &AWeaponBase::HandleShotDelayTimer,
	                                       ShotDelay,
	                                       true);
	return true;
}

bool AWeaponBase::StopShooting()
{
	if (!bIsShooting)
	{
		return false;
	}

	bIsShooting = false;
	bCanShoot = false;
	return true;
}

void AWeaponBase::HandleShotDelayTimer()
{
	if (!bCanShoot)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShotDelayTimer);
		bCanShoot = true;
		return;
	}

	MakeShot();
}
