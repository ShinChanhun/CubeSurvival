// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "DunGeonManagerObject.generated.h"

#pragma region DungeonInfos

//#define DIRECTION uint8
//#define DIRECTION_TOP 1<<0
//#define DIRECTION_BOTTOM 1<<1
//#define DIRECTION_UP 1<<2
//#define DIRECTION_DOWN 1<<3
//#define DIRECTION_LEFT 1<<4
//#define DIRECTION_RIGHT 1<<5

UENUM()
enum class ERoomType : uint8
{
	Default		UMETA(DisplayName = "Default"),
	Start		UMETA(DisplayName = "Start"),
	Hunt		UMETA(DisplayName = "Hunt"),
	Collect		UMETA(DisplayName = "Collect"),
	Trap		UMETA(DisplayName = "Trap"),
	MiddleBoss	UMETA(DisplayName = "MiddleBoss"),
	Boss		UMETA(DisplayName = "Boss"),
	Treasure	UMETA(DisplayName = "Treasure"),
};



USTRUCT()
struct FDungeonRoom
{
	GENERATED_BODY()
public:
	//UPROPERTY()
	//bool IsLinkedStartPoint;

	UPROPERTY()
	bool bIsCleared;

	UPROPERTY()
	bool bIsLinked;

	UPROPERTY()
	ERoomType RoomType;
	
	UPROPERTY()
	int32 Depth;

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	TArray<TPair<EDirection, TWeakPtr<FDungeonRoom>>> LinkedDirectionArray;
};

USTRUCT()
struct FDungeonInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
	ERoomType MapType;

	UPROPERTY()
	int32 MapSize;

	UPROPERTY()
	int32 MinPathLength;

	UPROPERTY()
	int32 MaxPathLength;


	TWeakPtr<FDungeonRoom> CoreRoom;
	TWeakPtr<FDungeonRoom> StartRoom;
};

#pragma endregion

UCLASS()
class CUBESURVIVAL_API UDungeonManagerObject : public UObject
{
	GENERATED_BODY()

private:
	void CreateRoom(FDungeonRoom& DungeonRoom);

	void MakeCoreAndStart();

	void MakeRealRoot(/*TArray<TArray<TSharedPtr<FDungeonRoom>>> DungeonMap, const int32 MinLength, const int32 MaxLength*/);
	void MakeFakeRoot();
	TArray<TPair<EDirection, TSharedPtr<FDungeonRoom>>> FindNearRoom(TSharedPtr<FDungeonRoom> Room);

	TArray<TSharedPtr<FDungeonRoom>> GetAllShortestPath(const TSharedPtr<FDungeonRoom> Start, const TSharedPtr<FDungeonRoom> End);

	TSharedPtr<FDungeonRoom> FindRoomForPosition(int32 X, int32 Y, int32 Z);

	bool BFSPath(TSharedPtr<FDungeonRoom> Current, const TSharedPtr<FDungeonRoom> End, TArray<TSharedPtr<FDungeonRoom>> PassedPath);


	void SetObjectInTheRoom();
	void UpdateRoom();
	void UpdateDungeon();

public:
	void CreateDungeon();
	void MoveNextRoom(/*현재 방, 다음 방*/);
	void ClearDungeon();

	void RotateMap(/*IsRight*/);

	inline TArray<TArray<TSharedPtr<FDungeonRoom>>> GetDungeonMap() { return DungeonRoomArray; }

private:
	UPROPERTY()
	FDungeonInfo DungeonInfo;

	int32 MapSize;

	TArray<TArray<TSharedPtr<FDungeonRoom>>> DungeonRoomArray;

};
