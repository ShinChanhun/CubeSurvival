// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "DunGeonManagerObject.generated.h"

UENUM()
enum class ERoomType : uint8
{
	RoomType_Default	UMETA(DisplayName = "Default"),
	RoomType_Start		UMETA(DisplayName = "Start"),
	RoomType_Hunt		UMETA(DisplayName = "Hunt"),
	RoomType_Collect	UMETA(DisplayName = "Collect"),
	RoomType_Trap		UMETA(DisplayName = "Trap"),
	RoomType_MiddleBoss	UMETA(DisplayName = "MiddleBoss"),
	RoomType_Boss		UMETA(DisplayName = "Boss"),
	RoomType_Treasure	UMETA(DisplayName = "Treasure"),
};

USTRUCT()
struct FDungeonInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 MapSize;

	UPROPERTY()
	ERoomType MapType;
};

USTRUCT()
struct FDungeonRoom
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool IsLinkedStartPoint;

	UPROPERTY()
	bool isCleared;

	UPROPERTY()
	ERoomType MapType;

	UPROPERTY()
	int32 Number;
};

UCLASS()
class CUBESURVIVAL_API UDungeonManagerObject : public UObject
{
	GENERATED_BODY()

private:
	void CreateRoom(FDungeonRoom& DungeonRoom);

	void MakeRealRoot(TArray<TArray<TSharedPtr<FDungeonRoom>>> DungeonMap, const int32 MinLength, const int32 MaxLength);
	void MakeFakeRoot();

	void SetObjectInTheRoom();
	void UpdateRoom();
	void UpdateDungeon();

public:
	void CreateDungeon();
	void MoveNextRoom(/*현재 방, 다음 방*/);
	void ClearDungeon();

	void RotateMap(/*IsRight*/);

	inline TArray<TArray<TSharedPtr<FDungeonRoom>>> GetDungeonMap() { return DungeonMap; }

private:
	UPROPERTY()
	FDungeonInfo DungeonInfo;

	TArray<TArray<TSharedPtr<FDungeonRoom>>> DungeonMap;

};
