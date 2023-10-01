// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UHitPointsComponent;
class APlayerController;
class UWeaponManagerComponent;

UCLASS()
class LUDUMDARE54_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Components")
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UWeaponManagerComponent> WeaponManagerComponent = nullptr;

private:
	UPROPERTY()
	APlayerController* PlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	FVector ProjectionLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AbilityAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction = nullptr;

	void Move(const FInputActionValue& Value);

	void AimAtCursor();

	void ProjectCursorToWorld();

	bool CalculateProjection(const FVector& RayOrigin,
	                         const FVector& RayDirection,
	                         const float Range,
	                         const FVector& PlaneOrigin,
	                         const FVector& PlaneNormal,
	                         FVector& Intersection);


	UFUNCTION(BlueprintCallable)
	void UpdateWeaponTargetPoint(const int32 WeaponId);
	
	void StartShooting();

	void StopShooting();

	void UseAbility();

	void Pause();
};
