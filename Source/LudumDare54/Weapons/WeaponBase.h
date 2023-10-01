// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class AProjectileBase;
class USceneComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShotSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartShootingSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopShootingSignature);

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
	FVector TargetPoint = FVector::ZeroVector;

	UPROPERTY(BlueprintAssignable)
	FOnShotSignature OnShot;

	UPROPERTY(BlueprintAssignable)
	FOnStartShootingSignature OnStartShooting;

	UPROPERTY(BlueprintAssignable)
	FOnStopShootingSignature OnStopShooting;

	UFUNCTION(BlueprintCallable)
	void SetRateOfFire(const float Value);

	UFUNCTION(BlueprintCallable)
	void SetProjectilePerShot(const int32 Value);

	UFUNCTION(BlueprintCallable)
	void SetDamagePerProjectile(const int32 Value);
	
	UFUNCTION(BlueprintCallable)
	bool MakeShot();

	UFUNCTION(BlueprintCallable)
	bool StartShooting();

	UFUNCTION(BlueprintCallable)
	bool StopShooting();

	bool GetIsShooting() const { return bIsShooting; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin="0.25", ClampMax="15"))
	float RateOfFire = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin="1", ClampMax="30"))
	int32 ProjectilesPerShot = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DamagePerProjectile = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MuzzleOffset = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ShotAngle = 45.f;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsShooting = false;

	bool bCanShoot = true;

	FTimerHandle ShotDelayTimer;

	float ShotDelay = 1.0f;

	void HandleShotDelayTimer();
};
