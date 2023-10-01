// Made by Titled Goose Team during Ludum Dare 54


#include "WeaponBase.h"

#include "ProjectileBase.h"
#include "Kismet/KismetMaterialLibrary.h"


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

void AWeaponBase::SetRateOfFire(const float Value)
{
	RateOfFire = Value <= 0.f ? 1.f : Value;
	ShotDelay = 1.f / RateOfFire;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(ShotDelayTimer))
	{
		TimerManager.ClearTimer(ShotDelayTimer);
		TimerManager.SetTimer(ShotDelayTimer,
		                      this,
		                      &AWeaponBase::HandleShotDelayTimer,
		                      ShotDelay,
		                      true);
	}
}

void AWeaponBase::SetProjectilePerShot(const int32 Value)
{
	ProjectilesPerShot = Value;
}

void AWeaponBase::SetDamagePerProjectile(const int32 Value)
{
	DamagePerProjectile = Value;
}

bool AWeaponBase::MakeShot()
{
	if (!ProjectileClass)
	{
		return false;
	}

	const FVector StartPoint = GetActorLocation();

	const float Theta = FMath::DegreesToRadians(ShotAngle / ProjectilesPerShot);
	const float Phi = FMath::DegreesToRadians(ShotAngle * 0.5) - Theta * 0.5;

	for (int32 i = 0; i < ProjectilesPerShot; i++)
	{
		FVector Direction = (TargetPoint - StartPoint).GetSafeNormal();
		Direction = Direction.RotateAngleAxisRad(Theta * i - Phi, FVector::UpVector);
		const FTransform SpawnTransform(FRotator::ZeroRotator, StartPoint + Direction * MuzzleOffset);
		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileClass, SpawnTransform);

		if (Projectile)
		{
			Projectile->SetProjectileData(Direction, DamagePerProjectile);
			Projectile->SetOwner(GetOwner());
			Projectile->FinishSpawning(SpawnTransform);
		}
	}

	OnShot.Broadcast();
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
	OnStartShooting.Broadcast();
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
	OnStopShooting.Broadcast();
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
