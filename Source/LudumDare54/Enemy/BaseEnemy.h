// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"

#include "BaseEnemy.generated.h"

class UBehaviorTree;
class APickupBase;
class UHitPointsComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDied);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE54_API AUBaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnEnemyDied;

	AUBaseEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(BlueprintReadOnly, Category="Components")
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Enemy")
	void OnDeathFinished();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animations")
	TObjectPtr<UAnimMontage> DeathMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Drop", meta=(ClampMin = "0", ClampMax = "100"))
	int32 DropChance = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Drop")
	TSubclassOf<APickupBase> PickupClass = nullptr;

	UFUNCTION()
	void PlayDeathMontage();
	void SpawnPickup() const;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
