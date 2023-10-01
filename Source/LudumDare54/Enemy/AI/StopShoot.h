// Made by Titled Goose Team during Ludum Dare 54

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "StopShoot.generated.h"

UCLASS()
class LUDUMDARE54_API UStopShoot : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UStopShoot();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	int WeaponId = 0;
};
