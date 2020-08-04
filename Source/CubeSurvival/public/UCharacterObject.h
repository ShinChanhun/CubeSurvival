// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UNomalMonsterAnimInstance.h"
//#include "Engine/SkeletalMesh.h"
//#include "Classes/Components/SkeletalMeshComponent.h"
#include "UObject/NoExportTypes.h"
#include "UCharacterObject.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UUCharacterObject : public UObject
{
	GENERATED_BODY()
	
public:
	UUCharacterObject();

	//플레이어 메시를 가져온다
	USkeletalMesh* GetPlayerMesh() const;

	//플레이어 애니메이션을 가져온다
	class TSubclassOf<UAnimInstance> GetPlayerAnimClass() const;

	//몬스터 메시를 가져온다
	TMap<FString, USkeletalMesh*> GetMonsterMesh() const;

	//몬스터 애니메이션을 가져온다
	TMap<FString, class TSubclassOf<UAnimInstance> > GetNormalMonsterAnim() const;


private:
	//플레이어 메시
	UPROPERTY(VisibleAnywhere, Category = Visual)
	USkeletalMesh* PlayerMesh;

	//플레이어 애니메이션 클래스
	class TSubclassOf<UAnimInstance> PlayerAnimClass;

	//몬스터 메시 모아두기 (맵으로 관리)
	UPROPERTY(VisibleAnywhere, Category = Visual)
	TMap<FString, USkeletalMesh*> MonsterMesh;
	//UNomalMonsterAnimInstance

	//일반 몬스터 애니메이션 (맵이로 관리)
	TMap<FString, class TSubclassOf<UAnimInstance>> NormalMonsterAnim;

	//TMap<FString, class TSubclassOf<UAnimInstance> > MonsterAnim;



	
};
