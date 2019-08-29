// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"


UENUM(BlueprintType)
enum class EDamageState : uint8
{
	NormalState	UMETA(DisplayName = "Normal"),
	FireState	UMETA(DisplayName = "Fire"),
	IceState	UMETA(DisplayName = "Ice"),
	StunState	UMETA(DisplayName = "Stun"),
	PoisonState	UMETA(DisplayName = "Poison"),
	DefalutState UMETA(DisplayName = "Defalut"),
};

/**
 * 
 */
class CUBESURVIVAL_API FCharacterDamageState
{
public:
	FCharacterDamageState();
	~FCharacterDamageState();
	void ReleaseDamage(class APawn* Target, enum EDamageState DmageState);
	void ReleaseDamage( enum EDamageState DmageState);
	void CharacterDamgeState(enum EDamageState CharacterState,  class APawn* Target, class UCSCharacterAbilityManagement* InCharacterAbility);

	void TestAttack(class FDamageDeco* Dm);
	//void ObjectDamageState(enum EDamageState ObjectState, class AActor*  Target);

private:
	void UpdateDamageState(enum EDamageState CharacterState,class APawn*  Target,  class UCSCharacterAbilityManagement* InCharacterAbility);

private:
	TMap<enum EDamageState, class FDamageDeco* > CharacterStateDamage;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UCSCharacterAbilityManagement* CharacterAbility;

	//나중에 데코레이터로 사용
	class FCharacterDamageComponent* Damcom;
};
