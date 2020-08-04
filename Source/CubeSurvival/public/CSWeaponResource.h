// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CSWeaponResource.generated.h"

USTRUCT(BlueprintType)
struct FCSItemData :public FTableRowBase
{
	GENERATED_BODY()

public:
	FCSItemData() :Name("SM_Sword_F06"), ItemName("Sword_F06"), Attribute("Normal"), BaseAttack(10), AttributeAttack(0) {}

	//���̽����� ������ ���̺��� ���鶧 Name�� ID�� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float BaseAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float AttributeAttack;
};
/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSWeaponResource : public UObject
{
	GENERATED_BODY()
	
public:
	UCSWeaponResource();


	TMap<FString, UStaticMesh*> GetWeaponMesh() const;

	FCSItemData* GetCSItemData(FString Name);

	TArray<FString> GetWeaponName()const {return MonsterNameArray;}

private:

	//���� �޽� ��Ƶα� (������ ����)
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TMap<FString, UStaticMesh*> WeapnMesh;
	
	TArray<FString> MonsterNameArray;
	
	UPROPERTY()
	class UDataTable* CSItemTable;

	
};
