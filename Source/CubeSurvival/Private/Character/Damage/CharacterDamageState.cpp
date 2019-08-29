// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterDamageState.h"

#include "CharacterDamageComponent.h"
#include "CharacterDamage.h"
#include "DamageDeco.h"
#include "FireDamageDeco.h"
#include "IceDamageDeco.h"
#include "StunDamageDeco.h"

#include "CSCharacterAbilityManagement.h"
#include "CSPlayerAbility.h"

FCharacterDamageState::FCharacterDamageState()
{
	CSLOG(Warning, TEXT("CharacterDamageState"));
}

FCharacterDamageState::~FCharacterDamageState()
{
	CSLOG(Warning, TEXT("~CharacterDamageState"));
}

void FCharacterDamageState::ReleaseDamage(class APawn* Target, enum EDamageState DmageState)//물약 같은 거에서 사용
{
	if (!CharacterStateDamage.Find(DmageState))
	{
		return;
	}
	FDamageDeco* DmageRelease = *CharacterStateDamage.Find(DmageState);
	DmageRelease->DmageRelease(Target);
	CharacterStateDamage.Remove(DmageState);

	if (CharacterStateDamage.Num() == 0)
	{
		delete this;
	}
}

void FCharacterDamageState::ReleaseDamage(enum EDamageState DmageState)//FireDamageDeco클래스에서 사용
{
	if (!CharacterStateDamage.Find(DmageState))
	{
		return;
	}
	CharacterStateDamage.Remove(DmageState);
	if (CharacterStateDamage.Num() == 0)
	{
		delete this;
	}
}

void FCharacterDamageState::CharacterDamgeState(enum EDamageState CharacterState, class APawn* Target, class UCSCharacterAbilityManagement* InCharacterAbility)
{	
	if (CharacterStateDamage.Find(CharacterState))
	{
		return;
	}

	UpdateDamageState(CharacterState, Target, InCharacterAbility);
}

void FCharacterDamageState::UpdateDamageState(enum EDamageState CharacterState, class APawn* Target, class UCSCharacterAbilityManagement* InCharacterAbility)
{
	EDamageState ECharacterState = CharacterState;

	switch (ECharacterState)
	{
	case EDamageState::FireState:
	{
		UE_LOG(LogTemp, Log, TEXT("fire"));
		//TODO:상태값 및 데미지 클래스 넣는 코드
		FFireDamageDeco* Firedag = new FFireDamageDeco();
		CharacterStateDamage.Add(CharacterState, Firedag);
	
		Firedag->FireAttack(InCharacterAbility, Target,this);		
		break;
	}
	case EDamageState::IceState:
	{	UE_LOG(LogTemp, Log, TEXT("Ice"));
	FIceDamageDeco* Icedag = new FIceDamageDeco();
	CharacterStateDamage.Add(CharacterState, Icedag);
	Icedag->IceAttack(InCharacterAbility, Target, this);

	break;
	}
	case EDamageState::PoisonState:
	{//PlayerStat->SetDamage(FinalDamage);
		UE_LOG(LogTemp, Log, TEXT("Poison"));
		break;
	}
	case EDamageState::StunState:
	{
		UE_LOG(LogTemp, Log, TEXT("Stun"));
		FStunDamageDeco* Stundag = new FStunDamageDeco();
		CharacterStateDamage.Add(CharacterState, Stundag);
		Stundag->StunAttack(InCharacterAbility, Target, this);
		break;
	}
	case EDamageState::NormalState:
	{
		UE_LOG(LogTemp, Log, TEXT("NormalState"));
		break;
	}

	default:
	{
		break;
	}
	}
}

//나중에 데코레이터로 사용
void FCharacterDamageState::TestAttack(class FDamageDeco* Dm)
{
	//1
	Damcom = new FFireDamageDeco(new FCharacterDamage());

	//2
	/*Damcom = new FCharacterDamage();
	Damcom = new FFireDamageDeco(Damcom);*/

}


//void FCharacterDamageState::ObjectDamageState(enum EDamageState PlayerState, class AActor*  Target)
//{
//	EDamageState EPlayerState = PlayerState;
//
//	switch (EPlayerState)
//	{
//	case EDamageState::FireState:
//	{
//		UE_LOG(LogTemp, Log, TEXT("fire"));
//		FFireDamageDeco* Firedag = new FFireDamageDeco();
//
//		Firedag->FireAttack(CharacterAbility, Target, this);
//
//		//TODO:상태값 및 데미지 클래스 넣는 코드
//		CharacterStateDamage.Add(PlayerState, Firedag);
//		break;
//	}
//	case EDamageState::IceState:
//	{	UE_LOG(LogTemp, Log, TEXT("Ice"));
//	break;
//	}
//	case EDamageState::PoisonState:
//	{//PlayerStat->SetDamage(FinalDamage);
//		UE_LOG(LogTemp, Log, TEXT("Poison"));
//		break;
//	}
//	case EDamageState::StunState:
//	{
//		UE_LOG(LogTemp, Log, TEXT("Stun"));
//		break;
//	}
//	case EDamageState::NormalState:
//	{
//		UE_LOG(LogTemp, Log, TEXT("Stun"));
//		break;
//	}
//
//	default:
//	{
//		break;
//	}
//	}
//}