// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SingleShootService.generated.h"

UCLASS()
class LUDUMDARE54_API USingleShootService : public UBTService
{
	GENERATED_BODY()

public:
	USingleShootService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	int WeaponId = 0;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
