// Made by Titled Goose Team during Ludum Dare 54

#include "EnemyController.h"

#include "BaseEnemy.h"
#include "BrainComponent.h"
#include "EnemyPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LudumDare54/Components/HitPointsComponent.h"
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
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetFocus(GetFocusOnActor());
}

AActor* AEnemyController::GetFocusOnActor() const
{
	const auto Enemy = Cast<AUBaseEnemy>(GetPawn());
	if (Enemy == nullptr) return nullptr;

	if (Enemy->HitPointsComponent->GetValue() == 0) return nullptr;
	if (GetBlackboardComponent() == nullptr) return nullptr;
	
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
