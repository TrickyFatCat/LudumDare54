// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemySystem.generated.h"

class ASpawnPointActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStarted);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnRoundFinished);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundFinished);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllRoundFinished);

USTRUCT(BlueprintType)
struct FEnemiesInWaveData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<ACharacter> Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int Count;
};

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<ACharacter>> Enemies;

	UPROPERTY(BlueprintReadOnly)
	float SpawnDelayDuringWave;

	UPROPERTY(BlueprintReadOnly)
	int CountOfEnemiesAtOnce;

	UPROPERTY(BlueprintReadOnly)
	int Spawned = 0;
};

UCLASS()
class LUDUMDARE54_API ASpawnEnemySystem : public AActor
{
	GENERATED_BODY()

public:
	ASpawnEnemySystem();
	void SortedSpawnActors();

	UFUNCTION(BlueprintCallable)
	void AddWave(UDataTable* Data) { Waves.Add(Data); }

	UFUNCTION(BlueprintCallable)
	void UpdateWaveDelay(const float Second) { WaveDelayTime = Second; }

	UFUNCTION(BlueprintCallable)
	void UpdateWaveMaxAtTime(const float MonsterCount) { WaveMaxAtTime = MonsterCount; }

	UFUNCTION(BlueprintCallable)
	void UpdateWaveRoundTime(const float Second) { RoundTimeDelay = Second; }

	UFUNCTION(BlueprintCallable)
	void UpdateRandomSpawn(const bool Random) { RoundTimeDelay = Random; }

	UPROPERTY(BlueprintAssignable)
	FOnRoundStarted OnRoundStarted;

	UPROPERTY(BlueprintAssignable)
	FOnSpawnRoundFinished OnSpawnRoundFinished;

	UPROPERTY(BlueprintAssignable)
	FOnRoundFinished OnRoundFinished;

	UPROPERTY(BlueprintAssignable)
	FOnAllRoundFinished OnAllRoundFinished;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	TArray<UDataTable*> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float WaveDelayTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	int WaveMaxAtTime = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float RoundTimeDelay = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	bool bIsRandomSpawn = true;


	void CallSpawn();
	void StartRound();
	FWaveData GenerateEnemies(int WaveIndex);

	virtual void BeginPlay() override;

private:
	TArray<ASpawnPointActor*> SpawnActors;

	FTimerHandle RoundTimerHandle;
	FTimerHandle WaveTimerHandle;

	FWaveData WaveData;
	int CurrentWave = 0;
};
