// Made by Titled Goose Team during Ludum Dare 54

#include "CheckDistanceToPlayerDecorator.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UCheckDistanceToPlayerDecorator::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory
) const
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Obj = Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (Obj == nullptr) return false;
	
	const auto Player = Cast<APawn>(Obj);
	if (Player == nullptr) return false;
	
	const auto Enemy = OwnerComp.GetAIOwner()->GetInstigatorController()->GetPawn();
	if (Enemy == nullptr) return false;
	
	return FVector::Dist(Enemy->GetActorLocation(), Player->GetActorLocation()) >= Distance;
}
