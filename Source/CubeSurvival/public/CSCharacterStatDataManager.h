// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CSCharacterStatDataManager.generated.h"


//네이티브 클래스가 아닌 U오브젝트 클래스를 사용하는 이유 구조체에 (BlueprintType)을 사용하기 위해서
//네이티브 클래스는 UObject를 상속받은 것도아니고 generated헤더가 없어서 USTRUCT(BlueprintType),GENERATED_BODY()를 사용할 수가 없다

 //캐릭터 스탯 데이터는 게임의 기반을 이루는 변하지 않는 데이터이므로 보통 게임 앱이 초기화 될때 불러드린다. 게임 앱이 종료 될 때까지 캐릭터 스탯 데이터는 보존 
USTRUCT(BlueprintType)
struct FCSPlayerStatData :public FTableRowBase
{
	GENERATED_BODY()

public:
	FCSPlayerStatData() :Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	//제이슨으로 데이터 테이블을 만들때 Name은 ID와 같은것
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

	//제이슨으로 데이터 테이블을 만들때 Name은 ID와 같은것
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
