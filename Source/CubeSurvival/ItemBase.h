// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"
UENUM()
enum class ItemType : uint8
{
	IT_Default UMETA(DisplayName = "일반"),
	IT_UseAble UMETA(DisplayName = "소모"),
	IT_Equipable UMETA(DisplayName = "장비"),
};
/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UItemBase : public UObject
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY()
	int32 ID;
	
	UPROPERTY()
	FName ItemName;
	
	UPROPERTY()
	ItemType Type;

	//메쉬 빠짐
	UPROPERTY()
	UStaticMeshComponent* Body;

};
