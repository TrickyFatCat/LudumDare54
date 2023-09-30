// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"

#include "BaseEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDied);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE54_API AUBaseEnemy : public ACharacter
{
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	GENERATED_BODY()

public:
	AUBaseEnemy();

	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnEnemyDied;
};
