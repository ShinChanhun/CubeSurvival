// Fill out your copyright notice in the Description page of Project Settings.

#include "CSMonsterCharacterBase.h"
#include "CSMonsterrAbility.h"
#include "CharacterDamageComponent.h"
#include "CharacterDamage.h"
#include "DamageDeco.h"
#include "FireDamageDeco.h"
#include "CSGameInstance.h"


ACSMonsterCharacterBase::ACSMonsterCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MonsterAbility = CreateDefaultSubobject<UCSMonsterrAbility>(TEXT("MONSTERABILITY"));

	MonsterNameArray.Add(TEXT("02020002_m_redmushroom"));
	MonsterNameArray.Add(TEXT("02020023_m_twingworker"));
	MonsterNameArray.Add(TEXT("02020031_m_regenworm"));
	MonsterNameArray.Add(TEXT("02020086_m_blacklighting_wolf"));

	MonsterScale.Add(TEXT("02020002_m_redmushroom"), MonsterSize::MS_Small);
	MonsterScale.Add(TEXT("02020023_m_twingworker"), MonsterSize::MS_Small);
	MonsterScale.Add(TEXT("02020031_m_regenworm"), MonsterSize::MS_Small);
	MonsterScale.Add(TEXT("02020086_m_blacklighting_wolf"), MonsterSize::MS_Middle);


	//MonsterResource = CreateDefaultSubobject<UCharacterResourceManager>(TEXT("CHARACTERRESOURCE"));//에러가 나면 다시 이걸로 바꿀것

	
	
}

// Called when the game starts or when spawned
void ACSMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();


}
void ACSMonsterCharacterBase::Jump()
{
	ACharacter::Jump();
}
void ACSMonsterCharacterBase::MonsterSetting(class ACSMonsterCharacterBase* SetCharacter, FString MonsterName )
{
	if (MonsterName.Len() <= 0)
	{
		CSLOG(Warning, TEXT("MonterName Null"));
		return;
	}

	MonsterSize MSSize = MonsterScale[MonsterName];
	switch (MSSize)
	{
	case MonsterSize::MS_Small:

		MonsterCapsuleSize(SetCharacter, 28.0f);
		break;

	case MonsterSize::MS_Middle:
		MonsterCapsuleSize(SetCharacter, 60.0f);
		break;

	case MonsterSize::MS_Big:
		MonsterCapsuleSize(SetCharacter, 80.0f);
		break;
	}
	CSGameInstance = UCSGameInstance::GetGameInstance();
	CSCHECK(CSGameInstance != nullptr);
	MonsterResource = CSGameInstance->GetCharacterResourceManager();//생성자에서 호출하다가 값이 null로 되어서 여기로 호출
	CSCHECK(MonsterResource != nullptr);
	SetCharacter->GetMesh()->SetSkeletalMesh(MonsterResource->GetMonsterMesh()[MonsterName]);
	SetCharacter->GetMesh()->SetAnimInstanceClass(MonsterResource->GetNormalMonsterAnim()[MonsterName]);
	SetCharacter->GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	SetCharacter->bUseControllerRotationYaw = false;
	SetCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;
	SetCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	SetCharacter->GetCharacterMovement()->JumpZVelocity = 600.0f;
	if (MonsterName.Equals(TEXT("02020086_m_blacklighting_wolf")))
	{
		SetCharacter->GetMesh()->SetRelativeLocationAndRotation(FVector4(0.0f, 0.0f, -50.0f), FRotator(0.0f, 270.0f, 0.0f));
	}
	else
	{
		SetCharacter->GetMesh()->SetRelativeLocationAndRotation(FVector4(0.0f, 0.0f, -25.0f), FRotator(0.0f, 180.0f, 0.0f));
	}
	
	SetCharacter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	SetCharacter->GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	
	MonsterAbility->SetMonsterName(MonsterName);
}

void ACSMonsterCharacterBase::MonsterCapsuleSize(class ACSMonsterCharacterBase* SetCharacter,float Size)
{
	SetCharacter->GetCapsuleComponent()->SetCapsuleRadius(Size);
	SetCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(Size);
}

int32 ACSMonsterCharacterBase::GetExp() const
{
	return MonsterAbility->GetDropExp();
}
