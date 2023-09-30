// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class AProjectileBase;

UCLASS()
class LUDUMDARE54_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectileBase> ProjectileClass = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin="0.25", ClampMax="15"))
	float RateOfFire = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin="1", ClampMax="30"))
	int32 ProjectilesPerShot = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DamagePerProjectile = 5;

	UFUNCTION(BlueprintCallable)
	bool MakeShot();

	UFUNCTION(BlueprintCallable)
	bool StartShooting();

	UFUNCTION(BlueprintCallable)
	bool StopShooting();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsShooting = false;

	bool bCanShoot = true;

	FTimerHandle ShotDelayTimer;

	float ShotDelay = 1.0f;

	void HandleShotDelayTimer();
};
