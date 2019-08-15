// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameState.h"

ACSGameState::ACSGameState()
{
	//CSLOG_S(Warning);

}

void ACSGameState::BeginPlay()
{
	Super::BeginPlay();

	CSLOG_S(Warning);

	MapManager = MakeWeakObjectPtr(NewObject<UMapManager>());
	MapManager->SetWorld((UWorld*)GetWorld());
	MapManager->SpawnMapDataToCube();

	DungeonManager = MakeWeakObjectPtr(NewObject<UDungeonManagerObject>());
	DungeonManager->CreateDungeon();
	auto a = DungeonManager->GetDungeonMap();

}