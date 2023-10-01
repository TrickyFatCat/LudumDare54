// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class LUDUMDARE54_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AProjectileBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent;

public:
	void SetProjectileData(const FVector& Direction, const int32 Damage);

private:
	FVector MovementDirection = FVector::ForwardVector;

	int32 Power = 1;

	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent,
	                         AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp,
	                         FVector NormalImpulse,
	                         const FHitResult& Hit);
};
