// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "JsonParsorObject.h"
#include "CSGameStateBase.h"
#include "CSGameInstance.h"
#include "List.h"

#include "MapManager.generated.h"

USTRUCT()
struct FMapInfo
{
	GENERATED_BODY()

	public:
	UPROPERTY()
	FVector Position;

	UPROPERTY()
	FString Type;

	~FMapInfo()
	{
		UE_LOG(LogTemp, Log, TEXT("Log Message-----------------------------------------~FMapInfo"));
	}
};

UCLASS()
class CUBESURVIVAL_API UMapManager : public UObject
{
	GENERATED_BODY()
	
public:
	UMapManager();
	~UMapManager();

	void AddMap(FMapInfo MapInfo);
	//void a(int32 a = 0);
	
private:
	TArray<FMapInfo> Maps;
	FMapInfo TestSP;

};
