// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemySystem.h"

#include "EngineUtils.h"
#include "SpawnPointActor.h"
#include "LudumDare54/Enemy/BaseEnemy.h"

DECLARE_LOG_CATEGORY_CLASS(LogSpawnEnemySystem, All, All);

// Sets default values
ASpawnEnemySystem::ASpawnEnemySystem(): WaveData()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnEnemySystem::BeginPlay()
{
	Super::BeginPlay();

	SpawnPoints.Reset();
	CurrentWave = 0;

	for (TActorIterator<ASpawnPointActor> It(GetWorld()); It; ++It) { SpawnPoints.Add(*It); }
	UE_LOG(LogSpawnEnemySystem, Display, TEXT("Count wave: %i."), SpawnPoints.Num());

	if (Waves.IsEmpty()) return;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASpawnEnemySystem::StartWave, WaveTimeDelay, false);
}

void ASpawnEnemySystem::StartWave()
{
	if (CurrentWave == Waves.Num())
	{
		UE_LOG(LogSpawnEnemySystem, Display, TEXT("All waves finished."));
		return OnAllWaveFinished.Broadcast();
	}

	UE_LOG(LogSpawnEnemySystem, Display, TEXT("Start %i wave."), CurrentWave);

	WaveData = GenerateEnemies(CurrentWave);
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ASpawnEnemySystem::CreateWave, SpawnDelayDuringWave, true);
	OnWaveStarted.Broadcast(CurrentWave);
	CurrentWave++;
}

void ASpawnEnemySystem::CreateWave()
{
	UE_LOG(LogSpawnEnemySystem, Display, TEXT("Spawn round."));
	for (int i = 0; i < WaveData.CountOfEnemiesAtOnce; i++)
	{
		if (WaveData.Enemies.Num() == 0) break;
		SortedSpawnPoints();
		for (ASpawnPointActor* SpawnActor : SpawnPoints)
		{
			if (const auto Enemy = SpawnActor->Spawn(WaveData.Enemies[WaveData.Enemies.Num() - 1]); Enemy != nullptr)
			{
				Enemy->OnEnemyDied.AddDynamic(this, &ASpawnEnemySystem::ApplyEnemyDeath);
				WaveData.SpawnedEnemiesCount++;
				WaveData.Enemies.RemoveAt(WaveData.Enemies.Num() - 1);
				break;
			}
		}
	}

	if (WaveData.Enemies.Num() == 0)
	{
		UE_LOG(LogSpawnEnemySystem, Display, TEXT("Finish wave."));
		GetWorldTimerManager().ClearTimer(WaveTimerHandle);
		OnSpawnRoundFinished.Broadcast();
		WaveData.SpawnFinished = true;
	}
}

void ASpawnEnemySystem::SortedSpawnPoints()
{
	if (bIsRandomSpawn)
	{
		const int32 LastIndex = SpawnPoints.Num() - 1;
		for (int32 y = 0; y <= LastIndex; ++y)
		{
			const int32 Index = FMath::RandRange(y, LastIndex);
			if (y != Index) { SpawnPoints.Swap(y, Index); }
		}
		return;
	}

	if (GetWorld() == nullptr) return;
	const auto Control = GetWorld()->GetFirstPlayerController();
	if (Control == nullptr) return;
	const auto Pawn = Control->GetPawn();
	if (Pawn == nullptr) return;

	const auto Location = Pawn->GetActorLocation();
	SpawnPoints.Sort([Location](const ASpawnPointActor& A, const ASpawnPointActor& B)
	{
		return FVector::Dist(Location, A.GetActorLocation()) < FVector::Dist(Location, B.GetActorLocation());
	});
}

void ASpawnEnemySystem::ApplyEnemyDeath()
{
	WaveData.DeathCount++;
	if (WaveData.SpawnFinished && WaveData.DeathCount >= WaveData.SpawnedEnemiesCount)
	{
		GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASpawnEnemySystem::StartWave, WaveTimeDelay, false);
		OnWaveFinished.Broadcast(CurrentWave);
	}
}

FWaveData ASpawnEnemySystem::GenerateEnemies(const int WaveIndex)
{
	TArray<TSubclassOf<ABaseEnemy>> Enemies;

	TArray<FEnemiesInWaveData*> AllEnemies;
	Waves[WaveIndex]->GetAllRows<FEnemiesInWaveData>("", AllEnemies);

	for (const FEnemiesInWaveData* EnemyStat : AllEnemies)
		for (int i = 0; i < EnemyStat->Count; i++)
			Enemies.Add(EnemyStat->Enemy);

	const int32 LastIndex = Enemies.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		const int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index) { Enemies.Swap(i, Index); }
	}

	return {Enemies, SpawnDelayDuringWave, CountOfEnemiesAtOnce};
}
