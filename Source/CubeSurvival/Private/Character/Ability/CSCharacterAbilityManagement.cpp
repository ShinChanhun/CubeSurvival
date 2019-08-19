// Fill out your copyright notice in the Description page of Project Settings.

#include "CSCharacterAbilityManagement.h"

// Sets default values for this component's properties
UCSCharacterAbilityManagement::UCSCharacterAbilityManagement()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UCSCharacterAbilityManagement::SetDamage(float NewDamage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, MaxHP));
}
void UCSCharacterAbilityManagement::SetHP(float NewHP)
{
	CurrentHP = NewHP;

	OnHPChange.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UCSCharacterAbilityManagement::GetAttack()
{
	return Attack;
}

float UCSCharacterAbilityManagement::GetHPRatio()
{
	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP);
}

