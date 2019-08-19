// Fill out your copyright notice in the Description page of Project Settings.

#include "CSMonsterSapwnActor.h"
#include "CSMonsterCharacterBase.h"
#include "CSNormalMonsterCharacter.h"

// Sets default values
ACSMonsterSapwnActor::ACSMonsterSapwnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetCollisionProfileName(TEXT("NoCollision"));
	MonsterTypeEnum = EMonsterType::NormalMonster;
	/*if (MonsterTypeEnum == EMonsterType::NormalMonster)
	{

	}
	else
	{

	}*/
	SpawnMonster = CreateAbstractDefaultSubobject<ACSNormalMonsterCharacter>(TEXT("NormalMonster"));

	bDirectionRnd = false;
	SpawnBox->SetBoxExtent(FVector(600.0f, 600.0f, 10.0f));
	MonsterNum = 5;

}

// Called when the game starts or when spawned
void ACSMonsterSapwnActor::BeginPlay()
{
	Super::BeginPlay();
	MonsterSpawn(SpawnMonster, bDirectionRnd);
}

void ACSMonsterSapwnActor::MonsterSpawn(class ACSMonsterCharacterBase* Monster, bool bInSpawnRnd)
{
	Monster->MonsterSpawn(this, this->GetActorLocation(), SpawnBox->GetScaledBoxExtent().X, SpawnBox->GetScaledBoxExtent().Y, MonsterNum, bInSpawnRnd);
}

