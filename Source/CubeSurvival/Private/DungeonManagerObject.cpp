// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonManagerObject.h"

void UDungeonManagerObject::CreateRoom(FDungeonRoom& Room)
{

}

void UDungeonManagerObject::MakeRealRoot(TArray<TArray<TSharedPtr<FDungeonRoom>>> DungeonMap, const int32 MinLength, const int32 MaxLength)
{

}

void UDungeonManagerObject::CreateDungeon()
{
	//TODO:���� �̹� �����ϴ��� üũ �ִٸ� �ʱ�ȭ

	int32 mapSize = 3;


	for (int j = 0; j < mapSize * mapSize; j++)
	{
		TArray<TSharedPtr<FDungeonRoom>> Dimension_2;

		for (int k = 0; k < mapSize; k++)
		{
			TSharedPtr<FDungeonRoom> Dimension_1 = MakeShareable(new FDungeonRoom());

			//TODO: �� �ʱ�ȭ	
			CreateRoom(*Dimension_1);


			Dimension_2.Add(Dimension_1);
		}

		DungeonMap.Add(Dimension_2);
	}

	CSLOG_S(Warning);
}
