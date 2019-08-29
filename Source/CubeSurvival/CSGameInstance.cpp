// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameInstance.h"
#include "CSCharacterStatDataManager.h"
#include "CharacterResourceManager.h"
UCSGameInstance::UCSGameInstance()
{
	CharacterStatData = CreateDefaultSubobject<UCSCharacterStatDataManager>(TEXT("CHARACTERSTATDATA"));
	CharacterResource = CreateDefaultSubobject<UCharacterResourceManager>(TEXT("CHARACTERRESOURCE"));
	
}

void UCSGameInstance::Init()
{
	
}

void UCSGameInstance::OnStart()
{
	
} 

//ĳ���� ���� ������//�Ҹ�ñ⵵ ������ ���� NEWObject�� �Ҵ��ؾ� �� ������ ������? �ҷ��ö� new�� ������ �Ἥ �Ҵ��ϴ� �ͺ��� ������ �ѹ� �Ҵ��ؼ� ���°� ������?
UCSCharacterStatDataManager* UCSGameInstance::GetCharacterStatDataManager()
{	
	return CharacterStatData;
}


 UCharacterResourceManager* UCSGameInstance::GetCharacterResourceManager()
{
	 if (CharacterResource==nullptr)
	 {
		 CharacterResource = NewObject< UCharacterResourceManager>();
	 }
	return CharacterResource;
}


 UCSGameInstance* UCSGameInstance::GameInstance = nullptr;

 UCSGameInstance* UCSGameInstance::GetGameInstance()
 {
	 if (GameInstance == nullptr)
	 {
		 GameInstance = NewObject<UCSGameInstance>();
	 }
	 return GameInstance;
 }