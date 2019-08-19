// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "CharacterResourceManager.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCharacterResourceManager : public UObject
{
	GENERATED_BODY()
	

public:
	UCharacterResourceManager();

	//플레이어 메시를 가져온다
	USkeletalMesh* GetPlayerMesh() const;//skeletalmesh = SMesh 수정 ex) GetPlayerSMesh

	//플레이어 애니메이션을 가져온다 TSubclassOf TSubclassOf는 UClass 타입의 안정성을 보장해 주는 템플릿 클래스  
	//TSubclassOf 템플릿 클래스를 이용해 특정 멤버 변수나 변수를 특정 UObject/UClass의 하위 클래스로 한정지을 수 있다.
	//사이트 참조 http://egloos.zum.com/sweeper/v/3225016
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

	//일반 몬스터 애니메이션 (맵으로 관리)
	TMap<FString, class TSubclassOf<UAnimInstance>> NormalMonsterAnim;
	
	
};
