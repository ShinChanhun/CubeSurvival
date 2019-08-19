// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CSCharacterStatDataManager.generated.h"


//����Ƽ�� Ŭ������ �ƴ� U������Ʈ Ŭ������ ����ϴ� ���� ����ü�� (BlueprintType)�� ����ϱ� ���ؼ�
//����Ƽ�� Ŭ������ UObject�� ��ӹ��� �͵��ƴϰ� generated����� ��� USTRUCT(BlueprintType),GENERATED_BODY()�� ����� ���� ����

 //ĳ���� ���� �����ʹ� ������ ����� �̷�� ������ �ʴ� �������̹Ƿ� ���� ���� ���� �ʱ�ȭ �ɶ� �ҷ��帰��. ���� ���� ���� �� ������ ĳ���� ���� �����ʹ� ���� 
USTRUCT(BlueprintType)
struct FCSPlayerStatData :public FTableRowBase
{
	GENERATED_BODY()

public:
	FCSPlayerStatData() :Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	//���̽����� ������ ���̺��� ���鶧 Name�� ID�� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 NextExp;

};

USTRUCT(BlueprintType)
struct FCSMonsterStatData :public FTableRowBase
{
	GENERATED_BODY()

public:
	FCSMonsterStatData() :Name("02020002_m_redmushroom"), MonsterName("Redmushroom"), MaxHP(100.0f), Attack(10.0f), DropExp(10) {}

	//���̽����� ������ ���̺��� ���鶧 Name�� ID�� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		FString MonsterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 DropExp;
};


/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSCharacterStatDataManager : public UObject
{
	GENERATED_BODY()
public:
	UCSCharacterStatDataManager();
	~UCSCharacterStatDataManager();
	FCSPlayerStatData* GetCSPlayerData(int32 Level);
	FCSMonsterStatData* GetCSMonsterData(FString Name);

private:
	UPROPERTY()
	class UDataTable* CSCharacterTable;

	UPROPERTY()
	class UDataTable* CSMonsterTable;
	
	
};
