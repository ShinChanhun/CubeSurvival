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

	//�÷��̾� �޽ø� �����´�
	USkeletalMesh* GetPlayerMesh() const;

	//�÷��̾� �ִϸ��̼��� �����´�
	class TSubclassOf<UAnimInstance> GetPlayerAnimClass() const;

	//���� �޽ø� �����´�
	TMap<FString, USkeletalMesh*> GetMonsterMesh() const;

	//���� �ִϸ��̼��� �����´�
	TMap<FString, class TSubclassOf<UAnimInstance> > GetNormalMonsterAnim() const;


private:
	//�÷��̾� �޽�
	UPROPERTY(VisibleAnywhere, Category = Visual)
	USkeletalMesh* PlayerMesh;

	//�÷��̾� �ִϸ��̼� Ŭ����
	class TSubclassOf<UAnimInstance> PlayerAnimClass;

	//���� �޽� ��Ƶα� (������ ����)
	UPROPERTY(VisibleAnywhere, Category = Visual)
	TMap<FString, USkeletalMesh*> MonsterMesh;
	//UNomalMonsterAnimInstance

	//�Ϲ� ���� �ִϸ��̼� (���̷� ����)
	TMap<FString, class TSubclassOf<UAnimInstance>> NormalMonsterAnim;

	//TMap<FString, class TSubclassOf<UAnimInstance> > MonsterAnim;



	
};
