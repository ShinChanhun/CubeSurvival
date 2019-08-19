// Fill out your copyright notice in the Description page of Project Settings.
///////////////////나중에 CSCharacterWidget에 상속 받아서 사용
#include "CSPlayerWidget.h"
#include "CSPlayerAbility.h"
#include "Components/ProgressBar.h"

void UCSPlayerWidget::BindCharacterStat(class UCSPlayerAbility* NewCharacterStat)
{
	CSCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;

	NewCharacterStat->OnHPChange.AddUObject(this, &UCSPlayerWidget::UpdateHPWidget);
}

//UI 시스템이 준비 되면 호출 UI생성은 Beginplay에서 호출되므로 postinitializecomponents함수에서 발생된 명령은 UI에 반영되지 않음. 따라서 이 함수에서 위젯 내용을 업데이하는 로직을 구현
void UCSPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgerssBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	CSCHECK(HPProgerssBar != nullptr);
	UpdateHPWidget();

}

void UCSPlayerWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (HPProgerssBar != nullptr)
		{
			HPProgerssBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}



