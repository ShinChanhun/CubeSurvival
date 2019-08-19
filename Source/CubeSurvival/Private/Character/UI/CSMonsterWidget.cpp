// Fill out your copyright notice in the Description page of Project Settings.
///////////////////나중에 CSCharacterWidget에 상속 받아서 사용
#include "CSMonsterWidget.h"
#include "CSMonsterrAbility.h"
#include "Components/ProgressBar.h"


void UCSMonsterWidget::BindMonsterStat(class UCSMonsterrAbility* MonsterStat)
{
	CSCHECK(MonsterStat != nullptr);

	CurrenMonsterStat = MonsterStat;
	MonsterStat->OnHPChange.AddUObject(this, &UCSMonsterWidget::UpdateHPWidget);
}

void UCSMonsterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgerssBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_MHPBar")));
	CSCHECK(HPProgerssBar != nullptr);
	UpdateHPWidget();

}

void UCSMonsterWidget::UpdateHPWidget()
{
	if (CurrenMonsterStat!=nullptr)
	{
		if (HPProgerssBar != nullptr)
		{
			HPProgerssBar->SetPercent(CurrenMonsterStat->GetHPRatio());
		}
	}
}


