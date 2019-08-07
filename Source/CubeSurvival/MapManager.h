// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "JsonParsorObject.h"
#include "CubeActor.h"

#include "MapManager.generated.h"

USTRUCT()
struct FSelectedMap
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool IsSelected;
	
	UPROPERTY()
	FVector Position;
	
	~FSelectedMap()
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

	void AddMap(FMapData MapData);
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

	UPROPERTY()
	bool IsSeletedMap;


};
