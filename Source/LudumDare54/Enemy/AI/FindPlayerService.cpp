// Made by Titled Goose Team during Ludum Dare 54


#include "FindPlayerService.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare54/Components/HitPointsComponent.h"
#include "LudumDare54/Player/PlayerCharacter.h"

UFindPlayerService::UFindPlayerService()
{
	NodeName = "Find Player";
}

void UFindPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (
		Blackboard &&
		GetWorld() != nullptr &&
		GetWorld()->GetFirstPlayerController() != nullptr &&
		GetWorld()->GetFirstPlayerController()->GetPawn() != nullptr
	)
	{
		const auto Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player == nullptr) return;

		Blackboard->SetValueAsObject(
			PlayerActorKey.SelectedKeyName,
			Player->HitPointsComponent->GetValue() == 0 ? nullptr : GetWorld()->GetFirstPlayerController()->GetPawn()
		);
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
