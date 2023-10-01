// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckDistanceToPlayerDecorator.generated.h"


UCLASS()
class LUDUMDARE54_API UCheckDistanceToPlayerDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector PlayerActorKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float Distance;
};
