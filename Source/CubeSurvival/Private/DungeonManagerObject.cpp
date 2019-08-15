// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonManagerObject.h"

void UDungeonManagerObject::CreateRoom(FDungeonRoom& Room)
{

}



void UDungeonManagerObject::MakeRealRoot(/*TArray<TArray<TSharedPtr<FDungeonRoom>>> DungeonMap, const int32 MinLength, const int32 MaxLength*/)
{
	//MakeCoreAndStart();



	TArray<TSharedPtr<FDungeonRoom>> Path;


}

void UDungeonManagerObject::MakeCoreAndStart()
{
	if (DungeonInfo.MapSize < 3 || DungeonRoomArray.Num() < 3)
	{
		CSLOG(Warning, TEXT("Error : Dungeon must be at least 3 in size "));
		return;
	}

	int32 MapSize = DungeonInfo.MapSize;
	int32 CoreIndex_2D = (MapSize * MapSize) / 2;
	int32 CoreIndex_3D = MapSize / 2;
	int32 EntranceCount = FMath::RandRange(2, 3);

	auto CoreRoom = DungeonRoomArray[CoreIndex_2D][CoreIndex_3D];
	CoreRoom->RoomType = ERoomType::Boss;

	auto StartRoom = DungeonRoomArray[0][0];
	StartRoom->RoomType = ERoomType::Start;
	StartRoom->Depth = 0;

	DungeonInfo.CoreRoom = CoreRoom;
	DungeonInfo.StartRoom = StartRoom;

	//TODO:Array �� � ������ ��ƿ��Ƽ�� ���� ����

	TArray<TWeakPtr<FDungeonRoom>> CoreNearRoom = (TArray<TWeakPtr<FDungeonRoom>>)FindNearRoom(CoreRoom);

	while (CoreNearRoom.Num() > EntranceCount)
	{
		int32 RandNum = FMath::RandRange(0, CoreNearRoom.Num() - 1);

		CoreNearRoom.RemoveAt(RandNum);
	}

	for (const TWeakPtr<FDungeonRoom>& item : CoreNearRoom)
	{
		auto MiddleBossRoom =  TPair<EDirection, TWeakPtr<FDungeonRoom>>(EDirection::Bottom, item);
		MiddleBossRoom.Value.Pin()->bIsLinked = true;
		CoreRoom->LinkedDirectionArray.Add(MiddleBossRoom);
	}

}

TArray<TPair<EDirection, TSharedPtr<FDungeonRoom>>> UDungeonManagerObject::FindNearRoom(TSharedPtr<FDungeonRoom> Room)
{
	TArray<TPair<EDirection, TSharedPtr<FDungeonRoom>>> FoundRoom;

	FVector Position = Room->Position;
	int32 X = Position.X;
	int32 Y = Position.Y;
	int32 Z = Position.Z;

	int32 MapSize = DungeonInfo.MapSize;

	int32 XArray[6] = { -1, 1, 0, 0, 0, 0 };
	int32 YArray[6] = {  0, 0, -1, 1, 0, 0 };
	int32 ZArray[6] = {  0, 0, 0, 0, -1, 1 };

	for (int i = 0; i < 6; i++)
	{
		if (X + XArray[i] > 0		&&
			Y + YArray[i] > 0		&& 
			Z + ZArray[i] > 0		&&
			X + XArray[i] < MapSize &&
			Y + YArray[i] < MapSize	&&
			Z + ZArray[i] < MapSize)
		{
			TSharedPtr<FDungeonRoom> LinkedRoom = 
				FindRoomForPosition(X + XArray[i], Y + YArray[i], Z + ZArray[i]);

			auto NearRoomAndDirectionPair = TPair<EDirection, TSharedPtr<FDungeonRoom>>(
				(EDirection)i,
				FindRoomForPosition(X + XArray[i], Y + YArray[i], Z + ZArray[i]));

			FoundRoom.Add(NearRoomAndDirectionPair);

		}
	}

	return FoundRoom;
}

TArray<TSharedPtr<FDungeonRoom>> UDungeonManagerObject::GetAllShortestPath(TSharedPtr<FDungeonRoom> Start, const TSharedPtr<FDungeonRoom> End)
{
	TArray<TSharedPtr<FDungeonRoom>> ResultPath;// = MakeShareable(new TArray< TWeakPtr<FDungeonRoom>>);
	TArray<TSharedPtr<FDungeonRoom>> PassedPath;// = MakeShareable(new TArray< TWeakPtr<FDungeonRoom>>);
	TArray<TSharedPtr<FDungeonRoom>> EdgePath;// = MakeShareable(new TArray< TWeakPtr<FDungeonRoom>>);

	//������ �ʱ�ȭ �ϴ� ������� �ִ� ������ ��� ������ ����

	ResultPath.Add(Start);
	PassedPath.Add(Start);

	int32 CurrentDepth = Start->Depth;

	bool bFoundPath = false;

	while (bFoundPath)
	{
		TArray<TPair<EDirection, TSharedPtr<FDungeonRoom>>> FoundNearRooms = FindNearRoom(PassedPath[PassedPath.Num() - 1]);
		
		for (int i = 0; i < FoundNearRooms.Num();)
		{
			if (FoundNearRooms[i].Value->bIsLinked == true)
			{
				FoundNearRooms.RemoveAt(i);
			}
			else
			{
				i++;

				ResultPath.Add(MakeShareable(PassedPath[PassedPath.Num() - 1].Get()));

				auto NextRoom = TPair<EDirection, TWeakPtr<FDungeonRoom>>(EDirection::Bottom, PassedPath[PassedPath.Num() - 1]);
				NextRoom.Value.Pin()->bIsLinked = true;
				ResultPath[ResultPath.Num() - 1]->LinkedDirectionArray.Add(NextRoom);

			}
		}




		for (int i = 0; i < ResultPath.Num(); i++)
		{
			ResultPath.Add(MakeShareable(ResultPath[i].Get()));

		}
	}

	int32 MaxLength = 5;
	
	return ResultPath;
}

TSharedPtr<FDungeonRoom> UDungeonManagerObject::FindRoomForPosition(int32 X, int32 Y, int32 Z)
{
	return DungeonRoomArray[X + (DungeonInfo.MapSize * Y)][Z];
}

bool UDungeonManagerObject::BFSPath(TSharedPtr<FDungeonRoom> Current, const TSharedPtr<FDungeonRoom> End, TArray<TSharedPtr<FDungeonRoom>> PassedPath)
{
	/*
	1. �ֺ� Ž��
	2. ���ռ� Ȯ��
	3. ���� Ȯ��
	4. �߰� or ����
	*/
	
	PassedPath.Add(Current);

	if (Current == End)
	{
		return true; //Ž�� ����
	}
	else if (DungeonInfo.MaxPathLength <= Current->Depth)
	{
		return false; //�ִ� ���̸� �Ѿ� ����
	}

	TArray<TPair<EDirection, TSharedPtr<FDungeonRoom>>> NearRoomArray = FindNearRoom(Current);

	//�̹� ��ο� �ִ� �� ����
	//for (const auto& Room : PassedPath)
	//{
	//	int32 FoundIndex = NearRoomArray.Find(Room);
	//	if (FoundIndex != INDEX_NONE)
	//	{
	//		NearRoomArray.RemoveAt(FoundIndex);

	//		if (NearRoomArray.Num() == 0)
	//		{
	//			return false; // ��ó�� ���� ��ο� ���Ե� ����
	//		}
	//	}
	//}

	//for (const auto& Room : NearRoomArray)
	//{
	//	if (BFSPath(Room, End, PassedPath) == false)
	//	{
	//		return false;
	//	}
	//}

	return false;
}

void UDungeonManagerObject::CreateDungeon()
{
	//TODO:���� �̹� �����ϴ��� üũ �ִٸ� �ʱ�ȭ

	DungeonInfo.MapSize = 3;
	int32 MapSize = DungeonInfo.MapSize;


	for (int i = 0; i < MapSize * MapSize; i++)
	{
		TArray<TSharedPtr<FDungeonRoom>> Dimension_2;

		for (int j = 0; j < MapSize; j++)
		{
			TSharedPtr<FDungeonRoom> Dimension_1 = MakeShareable(new FDungeonRoom());

			//TODO: �� �ʱ�ȭ	
			CreateRoom(*Dimension_1);

			Dimension_1->Position = FVector( i % MapSize, i / MapSize, j);
			Dimension_2.Add(Dimension_1);
		}

		DungeonRoomArray.Add(Dimension_2);
	}

	CSLOG_S(Warning);

	MakeCoreAndStart();

	CSLOG_S(Warning);

}
