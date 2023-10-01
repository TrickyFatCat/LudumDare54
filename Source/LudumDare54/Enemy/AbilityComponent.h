// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityActivatedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityDeactivatedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE54_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnAbilityActivatedSignature OnAbilityActivated;

	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnAbilityDeactivatedSignature OnAbilityDeactivated;

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool ActivateAbility();

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool DeactivateAbility();

protected:
	UPROPERTY(BlueprintReadOnly, Category="Ability")
	bool bIsActivated = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UAnimMontage* AbilityMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float CooldownDuration = 0.f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle CooldownTimerHandle;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability")
	void ActivateEffect();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability")
	void DeactivateEffect();

private:
	UFUNCTION()
	void FinishCooldown();
};
