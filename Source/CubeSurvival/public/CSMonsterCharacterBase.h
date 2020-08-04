// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "CharacterResourceManager.h"
#include "CSMonsterCharacterBase.generated.h"

/**
 * 
 */
 //몬스터 사이즈를 정하는 Enum
UENUM(BlueprintType)
enum class MonsterSize : uint8
{
	MS_Small	UMETA(DisplayName = "Small"),
	MS_Middle	UMETA(DisplayName = "Middle"),
	MS_Big		UMETA(DisplayName = "Big")
};

UCLASS()
class CUBESURVIVAL_API ACSMonsterCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ACSMonsterCharacterBase();
	void MonsterSetting(class ACSMonsterCharacterBase* SetCharacter, FString MonsterName);//일반적인 NormalMonster 셋팅

	UFUNCTION()
	virtual void MonsterCapsuleSize(class ACSMonsterCharacterBase* SetCharacter, float Size);


	virtual void MonsterSpawn(AActor* Owner, FVector Orgin, float LimitSizeX, float LimitSizeY, int MonsterNum, bool bRndRot){}

	void Jump();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UCharacterResourceManager* MonsterResource;
	
	TArray<FString> MonsterNameArray;

	UPROPERTY(EditAnywhere, Category = Ability)
	class UCSMonsterrAbility* MonsterAbility;






private:
	TMap<FString, MonsterSize> MonsterScale;
};
