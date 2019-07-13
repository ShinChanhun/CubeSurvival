// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"

UMapManager::UMapManager()
{
	UE_LOG(LogTemp, Log, TEXT("Log Message-----------------------------------------UMapManager"));


}

UMapManager::~UMapManager()
{
	UE_LOG(LogTemp, Log, TEXT("Log Message-----------------------------------------~UMapManager"));

}

void UMapManager::AddMap(FMapInfo MapInfo)
{
	Maps.Add(MapInfo);

	auto a = ((UCSGameInstance*)(GetWorld()->GetGameInstance<UCSGameInstance>()));
	a->TestFunction();
	//ACSGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<ACSGameStateBase>() : NULL;
}