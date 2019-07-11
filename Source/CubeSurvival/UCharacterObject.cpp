// Fill out your copyright notice in the Description page of Project Settings.

#include "UCharacterObject.h"

//#include "UObject/ConstructorHelpers.h"
//#include "Animation/AnimInstance.h"

//ĳ���� �𵨵鸸 ��Ƶδ� Ŭ����
//Classes
//NPC�� �� ���� ���鶧 �迭 �Ǵ� map�� ����Ͽ� �� ���� 
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