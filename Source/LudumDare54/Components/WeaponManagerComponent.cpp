// Made by Titled Goose Team during Ludum Dare 54


#include "WeaponManagerComponent.h"

#include "GameFramework/Character.h"
#include "LudumDare54/Weapons/WeaponBase.h"


UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (WeaponsToSpawn.Num() > 0 || Character)
	{
		for (TTuple<TSubclassOf<AWeaponBase>, FName> &WeaponPair : WeaponsToSpawn)
		{
			AWeaponBase* Weapon = GetWorld()->SpawnActorDeferred<AWeaponBase>(
				WeaponPair.Key,
				FTransform(FRotator::ZeroRotator, FVector::ZeroVector), GetOwner());

			if (!Weapon)
			{
				continue;
			}

			Weapons.Add(Weapon);
			FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, WeaponPair.Value);
			Weapon->FinishSpawning(FTransform(FRotator::ZeroRotator, FVector::ZeroVector));
		}
	}
}


void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UWeaponManagerComponent::MakeShot(const int32 WeaponId)
{
	if (!IsValidId(WeaponId))
	{
		return false;
	}

	return Weapons[WeaponId]->MakeShot();
}

bool UWeaponManagerComponent::StartShooting(const int32 WeaponId)
{
	if (!IsValidId(WeaponId))
	{
		return false;
	}

	return Weapons[WeaponId]->StartShooting();
}

bool UWeaponManagerComponent::StopShooting(const int32 WeaponId)
{
	if (!IsValidId(WeaponId))
	{
		return false;
	}

	return Weapons[WeaponId]->StopShooting();
}

bool UWeaponManagerComponent::SetWeaponTargetPoint(const int32 WeaponId, const FVector& TargetPoint)
{
	if (!IsValidId(WeaponId))
	{
		return false;
	}

	Weapons[WeaponId]->TargetPoint = TargetPoint;
	return true;
}

bool UWeaponManagerComponent::IsWeaponShooting(const int32 WeaponId) const
{
	if (!IsValidId(WeaponId))
	{
		return false;
	}

	return Weapons[WeaponId]->GetIsShooting();
}
