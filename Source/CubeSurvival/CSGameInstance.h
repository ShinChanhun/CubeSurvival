// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Engine/GameInstance.h"
#include "MapManager.h"
#include "CSGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:	
	virtual void OnStart() override;

	UFUNCTION()
	void TestFunction();

	UPROPERTY()
	FString TestName;
	
	//UPROPERTY()
	//TSharedPtr<UMapManager> mm;
	TSharedFromThis<this>
};
