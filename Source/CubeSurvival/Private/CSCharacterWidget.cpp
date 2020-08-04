// Fill out your copyright notice in the Description page of Project Settings.
////////////여러 문제가 있는걸 확인 
#include "CSCharacterWidget.h"
#include "CSCharacterAbilityManagement.h"
#include "Components/ProgressBar.h"

void UCSCharacterWidget::BindCharacterStat(class UCSCharacterAbilityManagement* CharacterStat)
{
	CSCHECK(CharacterStat != nullptr);

	CurrentCharacerStat = CharacterStat;
	CharacterStat->OnHPChange.AddUObject(this, &UCSCharacterWidget::UpdateHPWidget);
}

void UCSCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgerssBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_MHPBar")));
	CSCHECK(HPProgerssBar != nullptr);
	UpdateHPWidget();

}

void UCSCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacerStat != nullptr)
	{
		if (HPProgerssBar != nullptr)
		{
			HPProgerssBar->SetPercent(CurrentCharacerStat->GetHPRatio());
		}
	}
}
