// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"

UMapManager::UMapManager()
{
	ReadJsonMapData();
}


UMapManager::~UMapManager()
{

}

void UMapManager::MakeBasicMap()
{
	UE_LOG(LogTemp, Log, TEXT("Write Json Map Data"));

	TWeakObjectPtr<UJsonParsorObject> jo = MakeWeakObjectPtr(NewObject<UJsonParsorObject>());

	int count = 1;
	for (int i = -12; i < 13; i++)
	{
		for (int j = -12; j < 13; j++)
		{
			TotalMapData.Add(FMapData::CreateMapDataStruct(count, FString::FromInt(count), FVector(i, j, 0), FVector(0, 0, 0)));

			count++;
		}
	}

	jo->WriteMapData(TotalMapData, "BasicMap");
}

void UMapManager::SpawnMapDataToCube()
{
	TSharedPtr<FVector> location = MakeShareable(new FVector(0, 0, 0));
	TSharedPtr<FRotator> Rotator = MakeShareable(new FRotator(0, 0, 0));

	CSLOG_S(Warning);

	if (World != nullptr)
	{
		for (FMapData md : TotalMapData)
		{
			TSharedPtr<FVector> location = MakeShareable(new FVector(md.Position * CUBE_SIZE));
			TSharedPtr<FRotator> Rotator = MakeShareable(new FRotator(md.Rotation.Rotation()));
			TWeakObjectPtr<ACubeActor> tCA = MakeWeakObjectPtr(
				(ACubeActor*)World->SpawnActor(ACubeActor::StaticClass(), location.Get(), Rotator.Get())
			);

			tCA->Initialize(md.TextureName);

			TotalCube.Add(tCA);
		}
	}
	else
	{
	}
}

void UMapManager::ReadJsonMapData()
{
	TWeakObjectPtr<UJsonParsorObject> jo = MakeWeakObjectPtr(NewObject<UJsonParsorObject>());

	jo->ReadMapData(TotalMapData, "BasicMap");
}

void UMapManager::SetWorld(UWorld * World)
{
	this->World = World;
}

void UMapManager::WriteJsonMapData()
{
	TWeakObjectPtr<UJsonParsorObject> jo = MakeWeakObjectPtr(NewObject<UJsonParsorObject>());

	jo->WriteMapData(TotalMapData, "BasicMap");
}

void UMapManager::AddMap(FMapInfo MapInfo)
{
	//Maps.Add(MapInfo);

}