// Made by Titled Goose Team during Ludum Dare 54

#include "EnemyController.h"

#include "BaseEnemy.h"
#include "BrainComponent.h"
#include "EnemyPerceptionComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	EnemyPerceptionComponent = CreateDefaultSubobject<UEnemyPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*EnemyPerceptionComponent);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto Char = Cast<AUBaseEnemy>(InPawn);
	if (Char == nullptr) return;

	RunBehaviorTree(Char->BehaviorTreeAsset);
	Char->OnEnemyDied.AddDynamic(this, &AEnemyController::StopLogic);
}

void AEnemyController::StopLogic()
{
	BrainComponent->StopLogic("Die");
	BrainComponent->Cleanup();
}
