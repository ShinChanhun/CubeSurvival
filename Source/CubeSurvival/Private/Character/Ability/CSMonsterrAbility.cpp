// Fill out your copyright notice in the Description page of Project Settings.

#include "CSMonsterrAbility.h"
#include "CSGameInstance.h"
#include "CSCharacterStatDataManager.h"

UCSMonsterrAbility::UCSMonsterrAbility()
{

}

void UCSMonsterrAbility::SetMonsterName(FString InMonsterName)
{	
	auto CSGameInstance = Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	CSCHECK(CSGameInstance != nullptr);
	 CurrentMonsterStatData = CSGameInstance->GetCharacterStatDataManager()->GetCSMonsterData(InMonsterName);
		 //UCSGameInstance::GetGameInstance()->GetCharacterStatDataManager()->GetCSMonsterData(InMonsterName);

	if (CurrentMonsterStatData != nullptr)
	{
		MonsterName = CurrentMonsterStatData->MonsterName;
		MaxHP = CurrentMonsterStatData->MaxHP;
		Attack = CurrentMonsterStatData->Attack;
		SetHP(MaxHP);
	}
	else
	{
		CSLOG(Error, TEXT("Name (%s) data donsn't exist"), *CurrentMonsterStatData->Name);
	}
}
