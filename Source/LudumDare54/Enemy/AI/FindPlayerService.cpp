// Made by Titled Goose Team during Ludum Dare 54


#include "FindPlayerService.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare54/Components/HitPointsComponent.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (Blackboard && Controller)
	{
		const auto HP = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UHitPointsComponent>();
		if (HP == nullptr) return;

		Blackboard->SetValueAsObject(
			PlayerActorKey.SelectedKeyName,
			HP->GetValue() == 0 ? nullptr : GetWorld()->GetFirstPlayerController()->GetPawn()
		);
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
