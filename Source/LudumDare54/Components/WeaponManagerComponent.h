// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"

class AWeaponBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE54_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponManagerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool MakeShot(const int32 WeaponId);

	UFUNCTION(BlueprintCallable)
	bool StartShooting(const int32 WeaponId);

	UFUNCTION(BlueprintCallable)
	bool StopShooting(const int32 WeaponId);

	UFUNCTION(BlueprintCallable)
	bool SetWeaponTargetPoint(const int32 WeaponId, const FVector& TargetPoint);

	UFUNCTION(BlueprintPure)
	bool IsWeaponShooting(const int32 WeaponId) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<AWeaponBase>, FName> WeaponsToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AWeaponBase>> Weapons;

	bool IsValidId(const int32 Id) const { return Id >= 0 && Id < Weapons.Num(); };
};
