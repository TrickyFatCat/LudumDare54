// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"

#include "BaseEnemy.generated.h"

class UWeaponManagerComponent;
class UBehaviorTree;
class APickupBase;
class UHitPointsComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDied);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE54_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnEnemyDied;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	ABaseEnemy();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UWeaponManagerComponent> WeaponManagerComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animations")
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Drop", meta=(ClampMin = "0", ClampMax = "100"))
	int32 DropChance = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Drop")
	TSubclassOf<APickupBase> PickupClass = nullptr;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION()
	void Die();
	void SpawnPickup() const;

	virtual float TakeDamage(
		float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
};
