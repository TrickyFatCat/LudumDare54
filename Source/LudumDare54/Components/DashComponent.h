// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;
class APlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashActivatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashFishishedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashCooldowFinishedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE54_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDashComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void Dash(const FVector& Direction);

	UFUNCTION(BlueprintGetter, Category=Dash)
	FTimerHandle GetCooldownHandle() const;

	UFUNCTION(BlueprintPure, Category=Dash)
	bool IsOnCooldown() const;

	float GetCooldownTime() const;

	float GetDashTime() const { return DashTime; }

	UPROPERTY(BlueprintAssignable, Category=Dash)
	FOnDashActivatedSignature OnDashActivated;
	
	UPROPERTY(BlueprintAssignable, Category=Dash)
	FOnDashFishishedSignature OnDashFinished;
	
	UPROPERTY(BlueprintAssignable, Category=Dash)
	FOnDashCooldowFinishedSignature OnCooldownFinished;
	
	UFUNCTION(BlueprintCallable, BlueprintGetter, Category=Dash)
	bool GetIsDashing();

protected:
	UPROPERTY()
	APlayerCharacter* Character = nullptr;

	UPROPERTY()
	UCharacterMovementComponent* MovementComponent = nullptr;

	UPROPERTY()
	APlayerController* PlayerController = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetIsDashing, Category=Dash)
	bool bIsDashing = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DashPower = 2700.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DashCooldown = 1.25f;

	UPROPERTY(BlueprintGetter=GetCooldownHandle)
	FTimerHandle DashCooldownHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DashTime = .4f;

	UFUNCTION()
	void SetIsDashing(const bool bEnableDash);

	UFUNCTION()
	void CallDelegate();
};
