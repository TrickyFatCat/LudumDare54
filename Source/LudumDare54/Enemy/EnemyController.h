// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyController.generated.h"

class UEnemyPerceptionComponent;

UCLASS()
class LUDUMDARE54_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UEnemyPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName FocusOnKeyName = "Player";

	virtual void OnPossess(APawn* InPawn) override;
	virtual  void Tick(float DeltaTime) override;
	
private:
	AActor* GetFocusOnActor() const;
};
