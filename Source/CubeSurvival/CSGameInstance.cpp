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

//캐릭터 스탯 데이터//소멸시기도 같은데 굳이 NEWObject로 할당해야 할 이유가 있을까? 불러올때 new를 여러번 써서 할당하는 것보다 위에서 한번 할당해서 쓰는게 나을듯?
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