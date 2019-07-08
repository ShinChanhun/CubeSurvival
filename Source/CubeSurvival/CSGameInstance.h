// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JsonParsorObject.h"
#include "CSGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:	
	//UCSGameInstance()
	//{
	//	//UJsonParsorObject aa;
	//	//aa.Write("./aa");
	//};

	virtual void OnStart() override;

	
	
};
