// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"
UENUM()
enum class ItemType : uint8
{
	IT_Default UMETA(DisplayName = "�Ϲ�"),
	IT_UseAble UMETA(DisplayName = "�Ҹ�"),
	IT_Equipable UMETA(DisplayName = "���"),
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

	//�޽� ����
	UPROPERTY()
	UStaticMeshComponent* Body;

};
