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
	MonsterResource = CreateDefaultSubobject<UCharacterResourceManager>(TEXT("CHARACTERRESOURCE"));

	//MonsterStat = CreateDefaultSubobject<UCSMonsterrAbility>(TEXT("MONSTERABILITY"));원래 이거였습니다 변수 이름도 바꾸는걸 추천한다. 아니면 바꾸고 다시 컴파일하자 에러뜬다

	//아래 이름은 변수 이름만 바꾼거
	MonsterAbility = CreateDefaultSubobject<UCSMonsterrAbility>(TEXT("MONSTERABILITY"));

	MonsterNameArray.Add(TEXT("02020002_m_redmushroom"));
	MonsterNameArray.Add(TEXT("02020023_m_twingworker"));
	MonsterNameArray.Add(TEXT("02020031_m_regenworm"));
	MonsterNameArray.Add(TEXT("02020086_m_blacklighting_wolf"));

	MonsterScale.Add(TEXT("02020002_m_redmushroom"), MonsterSize::MS_Small);
	MonsterScale.Add(TEXT("02020023_m_twingworker"), MonsterSize::MS_Small);
	MonsterScale.Add(TEXT("02020031_m_regenworm"), MonsterSize::MS_Small);
	MonsterScale.Add(TEXT("02020086_m_blacklighting_wolf"), MonsterSize::MS_Middle);
	
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
	//auto CSGameInstance = Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//MonsterResource = UCSGameInstance::GetGameInstance()->GetCharacterResourceManager();
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
	//class CharacterDamageComponent* deco = new FireDamageDeco(new DamageDeco(new CharacterDamage(MonsterStat->GetAttack())));

	//deco->GetAttack();

	//delete deco;
	//float damage= MonsterStat->GetAttack() + NewObject<UCSFireDamageDeco>()->GetAttack();
	// NewObject< UCSFireDamageDeco>(NewObject<UCSDamageDeco>(NewObject<UCSMonsterDamage>()));
	
	//추가 공격들을 배열에 추가
	//class UCSCharacterDamageComponent* cdc = MonsterStat;
	//cdc->dearr.Add(NewObject<UCSFireDamageDeco>());
	//cdc->dearr.Add(NewObject<UCSDamageDeco>());
	//cdc->dearr.Add(MonsterStat);
	//MonsterStat->dearr.Add(NewObject<UCSFireDamageDeco>());
	//MonsterStat->dearr.Add(NewObject<UCSDamageDeco>());
	//배열에서 꺼내어 공격
	/*for (int32 i = 0; i != MonsterStat->dearr.Num(); i++)
	{
		MonsterStat->dearr[i]->GetAttack();
	}
	MonsterStat->GetAttack();
	MonsterStat->dearr.Empty();*/
}

void ACSMonsterCharacterBase::MonsterCapsuleSize(class ACSMonsterCharacterBase* SetCharacter,float Size)
{
	SetCharacter->GetCapsuleComponent()->SetCapsuleRadius(Size);
	SetCharacter->GetCapsuleComponent()->SetCapsuleHalfHeight(Size);
}
