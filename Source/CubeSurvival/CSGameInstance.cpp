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

//ĳ���� ���ҽ� ����� �ȵǴ°� ��ȭ�ΰ�?(static)
 UCharacterResourceManager* UCSGameInstance::GetCharacterResourceManager()
{
	 if (!CharacterResource)
	 {
		 CharacterResource = NewObject< UCharacterResourceManager>();
	 }
	return CharacterResource;
}


 UCSGameInstance* UCSGameInstance::GameInstance = nullptr;

 UCSGameInstance* UCSGameInstance::GetGameInstance()
 {
	 if (!GameInstance)
	 {
		 GameInstance = NewObject<UCSGameInstance>();
	 }
	 return GameInstance;
 }