// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSCharacterBase.h"
#include "UCharacterObject.h"
#include "CSMonsterCharacterBase.generated.h"

/**
 * 
 */
 //몬스터 사이즈를 정하는 Enum
UENUM(BlueprintType)
enum class MonsterSize : uint8
{
	MS_Small UMETA(DisplayName = "Small"),
	MS_Middle UMETA(DisplayName = "Middle"),
	MS_Big UMETA(DisplayName = "Big")
};

UCLASS()
class CUBESURVIVAL_API ACSMonsterCharacterBase : public ACSCharacterBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ACSMonsterCharacterBase();
	void MonsterSetting(class ACSMonsterCharacterBase* SetCharacter, FString MonsterName);//일반적인 NormalMonster 셋팅

	UFUNCTION()
	virtual void MonsterCapsuleSize(class ACSMonsterCharacterBase* SetCharacter, float Size);


	virtual void MonsterSpawn(AActor* Owner, FVector Orgin, float LimitSizeX, float LimitSizeY, int MonsterNum, bool bRndRot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UUCharacterObject* MonsterCharacter;
	
	TArray<FString> MonsterNameArray;

private:
	TMap<FString, MonsterSize> MonsterScale;
};
