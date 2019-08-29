// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "Components/ActorComponent.h"
#include "CSCharacterAbilityManagement.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBESURVIVAL_API UCSCharacterAbilityManagement : public UActorComponent
{
	GENERATED_BODY()
public:
	UCSCharacterAbilityManagement();

	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	void SetSpeed(float NewSpeed);

	float GetSpeed() { return Speed; }
	float GetAttack();
	float GetHPRatio();
	int32 GetDropExp() const { return Exp; }

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangeDelegate OnHPChange;
protected:	

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float MaxHP;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float Attack;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float Speed;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Exp;

private:



	
};
