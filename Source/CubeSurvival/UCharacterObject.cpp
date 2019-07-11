// Fill out your copyright notice in the Description page of Project Settings.

#include "UCharacterObject.h"

//#include "UObject/ConstructorHelpers.h"
//#include "Animation/AnimInstance.h"

//캐릭터 모델들만 모아두는 클래스
//Classes
//NPC나 적 몬스터 만들때 배열 또는 map을 사용하여 모델 정리 
UUCharacterObject::UUCharacterObject()
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


}


USkeletalMesh* UUCharacterObject::GetPlayerMesh() const
{
	return PlayerMesh;
}

class TSubclassOf<UAnimInstance> UUCharacterObject::GetPlayerAnimClass() const
{
	return PlayerAnimClass;
}