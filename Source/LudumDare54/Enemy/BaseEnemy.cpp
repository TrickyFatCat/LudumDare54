// Made by Titled Goose Team during Ludum Dare 54l

#include "BaseEnemy.h"


void AUBaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnEnemyDied.Broadcast();
	Super::EndPlay(EndPlayReason);
}

AUBaseEnemy::AUBaseEnemy()
{
}
