// Fill out your copyright notice in the Description page of Project Settings.

#include "CSPlayerAbility.h"
#include "CSCharacterStatDataManager.h"
#include "CSGameInstance.h"




UCSPlayerAbility::UCSPlayerAbility()
{

}

void UCSPlayerAbility::SetNewLevel(int32 NewLevel)
{

	auto CSGameInstance = Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CSCHECK(CSGameInstance != nullptr);

	CurrentPlayerStatData = CSGameInstance->GetCharacterStatDataManager()->GetCSPlayerData(NewLevel);
		//UCSGameInstance::GetGameInstance()->GetCharacterStatDataManager()->GetCSPlayerData(NewLevel);
		//

	if (CurrentPlayerStatData != nullptr)
	{
		Level = NewLevel;
		MaxHP = CurrentPlayerStatData->MaxHP;
		Attack = CurrentPlayerStatData->Attack;
		Speed = CurrentPlayerStatData->Speed;
		SetHP(CurrentPlayerStatData->MaxHP);
	}
	else
	{
		CSLOG(Error, TEXT("LEVEL (%d) data donsn't exist"), NewLevel);
	}
	
}


//float UCSPlayerAbility::GetAttack()
//{
//	return CurrentPlayerStatData->Attack;
//}