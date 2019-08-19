// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageDeco.h"

FDamageDeco::FDamageDeco()
{
	CSLOG(Warning, TEXT("DamageDeco"));
}

FDamageDeco::~FDamageDeco()
{
	CSLOG(Warning, TEXT("~nullDamageDeco"));
	
	if (DamgeComponent!=nullptr)
	{
		CSLOG(Warning, TEXT("~DamageDeco"));
		delete DamgeComponent;
		
	}
}
float FDamageDeco::GetAttack()
{
	
	if (DamgeComponent)
	{
		CSLOG(Warning, TEXT("DamageDeco GetAttack"));
		return DamgeComponent->GetAttack();
	}
	else
	{
		return 0.0f;
	}
}

float FDamageDeco::ContinuousDamage()
{
	CSLOG(Warning, TEXT("DamageDeco ContinuousDamage"));
	return 0.0f;
}

void FDamageDeco::DmageRelease(class AActor* FireReleaseTarget)
{
	if (FireReleaseTarget != nullptr)
	{
		FireReleaseTarget->GetWorldTimerManager().ClearTimer(DamageTimerHandle);
		delete this;
	}
}