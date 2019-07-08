// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Json.h"
#include "JsonParsorObject.generated.h"

USTRUCT()
struct FMapData
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FVector Position;

	UPROPERTY()
	FString Type;

public:
	static FMapData CreateFMapDataStruct(
		FVector position,
		FString type
	)
	{
		FMapData mapData;
		mapData.Position = position;
		mapData.Type = type;

		return mapData;
	}
};


/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UJsonParsorObject : public UObject
{
	GENERATED_BODY()	
public:
	void Write(FString path);
	void Read(FString path);

	TArray<FMapData> GenerateStructsFromJson(FString Path);

private:
	void GenerateStructsFromJson(TArray<FMapData> &MapDataStructs, TSharedPtr<FJsonObject> JsonObject);
	
	FString JsonFullPath(FString Path);
	FVector ParseAsVector(TSharedPtr<FJsonObject> json, FString KeyName);
	FRotator ParseAsRotator(TSharedPtr<FJsonObject> json, FString KeyName);
	
};
