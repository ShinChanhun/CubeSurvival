// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/Actor.h"
#include "CSMonsterSapwnActor.generated.h"

UENUM(BlueprintType)
enum class EMonsterType :uint8
{
	NormalMonster UMETA(DisplayName = "NMonster"),
	MiddleMonster UMETA(DisplayName = "MMonster")
};

UCLASS()
class CUBESURVIVAL_API ACSMonsterSapwnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSMonsterSapwnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	

public:	
	UFUNCTION()//안붙혔을경우 2번 불림
	void MonsterSpawn(class ACSMonsterCharacterBase* Monster, bool bInSpawnRnd);

	UPROPERTY(EditAnywhere, Category = "Spawning")
	EMonsterType MonsterTypeEnum;

	UPROPERTY()
	class ACSMonsterCharacterBase* SpawnMonster;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	bool bDirectionRnd;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int MonsterNum;

private:
	//스폰 박스 액터
	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	UBoxComponent* SpawnBox;

};
