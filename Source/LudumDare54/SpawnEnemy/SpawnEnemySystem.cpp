// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemySystem.h"

#include "EngineUtils.h"
#include "SpawnPointActor.h"
#include "GameFramework/Character.h"

DECLARE_LOG_CATEGORY_CLASS(LogSpawnEnemySystem, All, All);

// Sets default values
ASpawnEnemySystem::ASpawnEnemySystem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnEnemySystem::SortedSpawnActors()
{
	if (bIsRandomSpawn)
	{
		const int32 LastIndex = SpawnActors.Num() - 1;
		for (int32 y = 0; y <= LastIndex; ++y)
		{
			const int32 Index = FMath::RandRange(y, LastIndex);
			if (y != Index) { SpawnActors.Swap(y, Index); }
		}
		return;
	}

	if (GetWorld() == nullptr) return;
	const auto Control = GetWorld()->GetFirstPlayerController();
	if (Control == nullptr) return;
	const auto Pawn = Control->GetPawn();
	if (Pawn == nullptr) return;

	const auto Location = Pawn->GetActorLocation();
	SpawnActors.Sort([Location](const ASpawnPointActor& A, const ASpawnPointActor& B)
	{
		return FVector::Dist(Location, A.GetActorLocation()) < FVector::Dist(Location, B.GetActorLocation());
	});
}

void ASpawnEnemySystem::CallSpawn()
{
	UE_LOG(LogSpawnEnemySystem, Display, TEXT("Count Spawn!"));
	for (int i = 0; i < WaveData.MaxAtTime; i++)
	{
		if (WaveData.MaxEnemies == WaveData.Spawned) break;
		SortedSpawnActors();
		for (ASpawnPointActor* SpawnActor : SpawnActors)
		{
			if (SpawnActor->Spawn(WaveData.Enemies[WaveData.Enemies.Num() - 1]))
			{
				WaveData.Spawned++;
				WaveData.Enemies.RemoveAt(WaveData.Enemies.Num() - 1);
				break;
			}
		}
	}

	if (WaveData.MaxEnemies == WaveData.Spawned)
	{
		GetWorldTimerManager().ClearTimer(WaveTimerHandle);
		GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASpawnEnemySystem::CallRound, RoundTimeDelay, false);
		OnRoundFinished.Broadcast();
	}
}

void ASpawnEnemySystem::CallRound()
{
	UE_LOG(LogSpawnEnemySystem, Display, TEXT("Count Round!"));
	WaveData = GenerateEnemies();
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ASpawnEnemySystem::CallSpawn, WaveDelayTime, true);
	OnRoundStarted.Broadcast();
}

FWaveData ASpawnEnemySystem::GenerateEnemies()
{
	TArray<TSubclassOf<ACharacter>> Enemies;

	TArray<FEnemyData*> AllEnemies;
	Wave->GetAllRows<FEnemyData>("", AllEnemies);

	for (const FEnemyData* EnemyStat : AllEnemies)
	{
		for (int i = 0; i < EnemyStat->Count; i++)
		{
			Enemies.Add(EnemyStat->Enemy);
		}
	}

	const int32 LastIndex = Enemies.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		const int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index) { Enemies.Swap(i, Index); }
	}

	return {
		Enemies,
		Enemies.Num(),
		0,
		WaveDelayTime,
		WaveMaxAtTime
	};
}


void ASpawnEnemySystem::BeginPlay()
{
	Super::BeginPlay();

	SpawnActors.Reset();
	for (TActorIterator<ASpawnPointActor> It(GetWorld()); It; ++It) { SpawnActors.Add(*It); }
	UE_LOG(LogSpawnEnemySystem, Display, TEXT("Count Spawn: %i."), SpawnActors.Num());

	if (Wave == nullptr) return;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASpawnEnemySystem::CallRound,WaveDelayTime, false);
}
