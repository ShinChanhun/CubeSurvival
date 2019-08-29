// Fill out your copyright notice in the Description page of Project Settings.

#include "CSCharacterStatDataManager.h"


UCSCharacterStatDataManager::UCSCharacterStatDataManager()
{
	FString CharacterDataPath = TEXT("DataTable'/Game/Data/PlayerStateData.PlayerStateData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CSCHARACTER(*CharacterDataPath);
	CSCHECK(DT_CSCHARACTER.Succeeded());
	CSCharacterTable = DT_CSCHARACTER.Object;
	CSCHECK(CSCharacterTable->RowMap.Num() > 0);

	FString MonsterDataPath = TEXT("DataTable'/Game/Data/MonsterStatData.MonsterStatData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CSMONSTER(*MonsterDataPath);
	CSCHECK(DT_CSMONSTER.Succeeded());
	CSMonsterTable = DT_CSMONSTER.Object;
	CSCHECK(CSMonsterTable->RowMap.Num() > 0);

}
UCSCharacterStatDataManager::~UCSCharacterStatDataManager()
{
	CSLOG(Warning, TEXT("~UCSCharacterStatDataManager"));
}


FCSPlayerStatData* UCSCharacterStatDataManager::GetCSPlayerData(int32 Level)
{
	return CSCharacterTable->FindRow<FCSPlayerStatData>(*FString::FromInt(Level), TEXT(""));
}
FCSMonsterStatData* UCSCharacterStatDataManager::GetCSMonsterData(FString Name)
{
	return CSMonsterTable->FindRow<FCSMonsterStatData>(FName(*Name), TEXT(""));
}