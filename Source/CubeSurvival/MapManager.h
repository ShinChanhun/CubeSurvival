// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "JsonParsorObject.h"
#include "CubeActor.h"
#include "List.h"

#include "MapManager.generated.h"

USTRUCT()
struct FMapInfo
{
	GENERATED_BODY()

public:

	~FMapInfo()
	{
		UE_LOG(LogTemp, Log, TEXT("Log Message-----------------------------------------~FMapInfo"));
	}
};

UCLASS()
class CUBESURVIVAL_API UMapManager : public UObject
{
	GENERATED_BODY()
private:
	UMapManager();
	~UMapManager();
	
	void MakeBasicMap();

public:

	void AddMap(FMapInfo MapInfo);
	void WriteJsonMapData();
	void ReadJsonMapData();
	void SpawnMapDataToCube();

	void SetWorld(UWorld* World);

private:
	UPROPERTY()
	TArray<FMapData> TotalMapData;

	UPROPERTY()
	TArray<TWeakObjectPtr<ACubeActor>> TotalCube;

	UPROPERTY()
	UWorld* World;
};
