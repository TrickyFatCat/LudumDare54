// Made by Titled Goose Team during Ludum Dare 54

#include "RandomLocationNode.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

URandomLocationNode::URandomLocationNode()
{
	NodeName = "NextLocation";
}

EBTNodeResult::Type URandomLocationNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Controller == nullptr || Blackboard == nullptr) return  EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (Pawn == nullptr) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (NavSys == nullptr) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	if (SelfCenter == false) {
		const auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (CenterActor == nullptr) return  EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}

	const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if (Found == false) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, NavLocation.Location);
	return   EBTNodeResult::Succeeded;
}