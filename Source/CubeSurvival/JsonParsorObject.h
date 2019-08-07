// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "JsonParsorObject.generated.h"

UENUM()
enum class EDirection : uint8
{
	Direction_Top		UMETA(DisplayName = "Top"),
	Direction_Bottom	UMETA(DisplayName = "Bottom"),
	Direction_Up		UMETA(DisplayName = "Up"),
	Direction_Down		UMETA(DisplayName = "Down"),
	Direction_Right		UMETA(DisplayName = "Right"),
	Direction_Left		UMETA(DisplayName = "Left"),
};

USTRUCT()
struct FMapData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 ID;

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	FString Type;

	UPROPERTY()
	FVector Rotation;

	UPROPERTY()
	FString TextureName;
	//UPROPERTY()
	//Direction Dir;
	
public:


	static FMapData CreateMapDataStruct(int32 id, FString type, FVector position, FVector rotation, FString TextureName = "co_floor_wood_a01.co_floor_wood_a01")
	{
		FMapData mapData;
		mapData.ID = id;
		mapData.Type = type;
		mapData.Position = position;
		mapData.Rotation = rotation;
		mapData.TextureName = TextureName;

		return mapData;
	}


	//TSharedPtr<FJsonValue> GetMapDataToFJsonValue()
	//{
	//	TArray< TSharedPtr<FJsonValue> > ValueArray;


	//	for (TFieldIterator<UProperty> PropIt(StaticStruct()); PropIt; ++PropIt)
	//	{
	//		UProperty* Property = *PropIt;
	//		FJsonValue* JsonValue;
	//		FJsonObjectConverter::UPropertyToJsonValue(Property, JsonValue, 0, 0);
	//		TSharedPtr<FJsonValue> SPtrJsonValue = MakeShareable(JsonValue);
	//		ValueArray.Push(SPtrJsonValue);
	//	}

	//	TSharedPtr<FJsonValue> NewVal = MakeShareable(new FJsonValueArray(ValueArray));
	//	
	//	return NewVal;
	//}

	//static TArray<FString> PropertyToStrings()
	//{
	//	TArray<FString> propertyArray;
	//	for (TFieldIterator<UProperty> PropIt(GetStaticStruct()); PropIt; ++PropIt)
	//	{
	//		UProperty* Property = *PropIt;
	//		propertyArray.Push(*(PropIt->GetFName()).ToString());			
	//	}

	//	return propertyArray;
	//}

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
	void WriteMapData(TArray<struct FMapData>& ArrMapData, FString Path);
	TArray<struct FMapData> Read(FString Path);
	void ReadMapData(TArray<struct FMapData>& ArrMapData, FString Path);

private:
	void GenerateStructsFromJson(TArray<FMapData> &MapDataStructs, TSharedPtr<FJsonObject> JsonObject);

	FString JsonFullPath(FString Path);
	FVector ParseAsVector(TSharedPtr<FJsonObject> json, FString KeyName);
	FRotator ParseAsRotator(TSharedPtr<FJsonObject> json, FString KeyName);

	void GetGameState();

	bool IsJsonDeserialize;
	bool IsJsonObjectIsValid;
};
