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

	//�÷��̾� �޽ø� �����´�
	USkeletalMesh* GetPlayerMesh() const;//skeletalmesh = SMesh ���� ex) GetPlayerSMesh

	//�÷��̾� �ִϸ��̼��� �����´� TSubclassOf TSubclassOf�� UClass Ÿ���� �������� ������ �ִ� ���ø� Ŭ����  
	//TSubclassOf ���ø� Ŭ������ �̿��� Ư�� ��� ������ ������ Ư�� UObject/UClass�� ���� Ŭ������ �������� �� �ִ�.
	//����Ʈ ���� http://egloos.zum.com/sweeper/v/3225016
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

	//�Ϲ� ���� �ִϸ��̼� (������ ����)
	TMap<FString, class TSubclassOf<UAnimInstance>> NormalMonsterAnim;
	
	
};
