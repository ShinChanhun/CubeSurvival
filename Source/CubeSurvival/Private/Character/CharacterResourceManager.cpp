// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterResourceManager.h"


//#include "UObject/ConstructorHelpers.h"
//#include "Animation/AnimInstance.h"
//캐릭터 모델들과 UAnimInstance 클래스 모아둔 클래스이다.
//NPC나 적 몬스터 만들때 배열 또는 map을 사용하여 모델 정리 
UCharacterResourceManager::UCharacterResourceManager()
{

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Nana_Mesh(TEXT("SkeletalMesh'/Game/Model/Player/Nana/Meshes/SKM_Nana.SKM_Nana'"));

	if (Nana_Mesh.Succeeded())
	{
		PlayerMesh = Nana_Mesh.Object;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> Nana_Anim(TEXT("AnimBlueprint'/Game/Animation/Player/NanaAnim.NanaAnim_C'"));
	if (Nana_Anim.Succeeded())
	{
		PlayerAnimClass = Nana_Anim.Class;
	}

	static  ConstructorHelpers::FObjectFinder<USkeletalMesh>  m_redmushroom_Mesh(TEXT("SkeletalMesh'/Game/Model/Monster/02020002/02020002_m_redmushroom.02020002_m_redmushroom'"));

	if (m_redmushroom_Mesh.Succeeded())
	{
		MonsterMesh.Add(TEXT("02020002_m_redmushroom"), m_redmushroom_Mesh.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance> m_redmushroom_Anim(TEXT("AnimBlueprint'/Game/Animation/Monster/02020002_m_redmushroom.02020002_m_redmushroom_C'"));

	if (m_redmushroom_Anim.Succeeded())
	{
		NormalMonsterAnim.Add(TEXT("02020002_m_redmushroom"), m_redmushroom_Anim.Class);
	}

	static  ConstructorHelpers::FObjectFinder<USkeletalMesh>  m_twingworker_Mesh(TEXT("SkeletalMesh'/Game/Model/Monster/02020023/02020023_m_twingworker.02020023_m_twingworker'"));

	if (m_twingworker_Mesh.Succeeded())
	{
		MonsterMesh.Add(TEXT("02020023_m_twingworker"), m_twingworker_Mesh.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance> m_twingworker_Anim(TEXT("AnimBlueprint'/Game/Animation/Monster/02020023_m_twingworker.02020023_m_twingworker_C'"));

	if (m_twingworker_Anim.Succeeded())
	{
		NormalMonsterAnim.Add(TEXT("02020023_m_twingworker"), m_twingworker_Anim.Class);
	}


	static  ConstructorHelpers::FObjectFinder<USkeletalMesh>  m_regenworm_Mesh(TEXT("SkeletalMesh'/Game/Model/Monster/02020031/02020031_m_regenworm.02020031_m_regenworm'"));

	if (m_regenworm_Mesh.Succeeded())
	{
		MonsterMesh.Add(TEXT("02020031_m_regenworm"), m_regenworm_Mesh.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance> m_regenworm_Anim(TEXT("AnimBlueprint'/Game/Animation/Monster/02020031_m_regenworm.02020031_m_regenworm_C'"));

	if (m_regenworm_Anim.Succeeded())
	{
		NormalMonsterAnim.Add(TEXT("02020031_m_regenworm"), m_regenworm_Anim.Class);
	}


	static  ConstructorHelpers::FObjectFinder<USkeletalMesh>  m_blacklighting_wolf_Mesh(TEXT("SkeletalMesh'/Game/Model/Monster/02020086/02020086_m_blacklighting_wolf.02020086_m_blacklighting_wolf'"));

	if (m_blacklighting_wolf_Mesh.Succeeded())
	{
		MonsterMesh.Add(TEXT("02020086_m_blacklighting_wolf"), m_blacklighting_wolf_Mesh.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance>  m_blacklighting_wolf_Anim(TEXT("AnimBlueprint'/Game/Animation/Monster/02020086_m_blacklighting_wolf.02020086_m_blacklighting_wolf_C'"));

	if (m_blacklighting_wolf_Anim.Succeeded())
	{
		NormalMonsterAnim.Add(TEXT("02020086_m_blacklighting_wolf"), m_blacklighting_wolf_Anim.Class);
	}

	CSLOG(Warning, TEXT("UCharacterResourceManager"));
}


USkeletalMesh* UCharacterResourceManager::GetPlayerMesh() const
{
	return PlayerMesh;
}

class TSubclassOf<UAnimInstance> UCharacterResourceManager::GetPlayerAnimClass() const
{
	return PlayerAnimClass;
}

TMap<FString, USkeletalMesh*> UCharacterResourceManager::GetMonsterMesh() const
{
	return MonsterMesh;
}

TMap<FString, class TSubclassOf<UAnimInstance> > UCharacterResourceManager::GetNormalMonsterAnim() const
{
	return NormalMonsterAnim;
}



