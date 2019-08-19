// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "CSGameInstance.generated.h"
/**
 *
 */




UCLASS()
class CUBESURVIVAL_API UCSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UCSGameInstance();

	virtual void OnStart() override;
	virtual void Init() override;

	UFUNCTION()
	 class UCSCharacterStatDataManager* GetCharacterStatDataManager() ;

	UFUNCTION()
	class UCharacterResourceManager* GetCharacterResourceManager();

	static UCSGameInstance* GetGameInstance();

private:
	UPROPERTY()
	class UCSCharacterStatDataManager* CharacterStatData;

	UPROPERTY()
	class UCharacterResourceManager* CharacterResource;

	static UCSGameInstance* GameInstance;

};

