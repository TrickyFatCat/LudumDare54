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

private:
	UPROPERTY()
	APlayerController* PlayerController = nullptr;

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
	void Shoot();

	void UseAbility();

	void Pause();
};
