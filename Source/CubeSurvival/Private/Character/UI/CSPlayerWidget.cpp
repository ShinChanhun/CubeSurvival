// Fill out your copyright notice in the Description page of Project Settings.
///////////////////���߿� CSCharacterWidget�� ��� �޾Ƽ� ���
#include "CSPlayerWidget.h"
#include "CSPlayerAbility.h"
#include "Components/ProgressBar.h"

void UCSPlayerWidget::BindCharacterStat(class UCSPlayerAbility* NewCharacterStat)
{
	CSCHECK(NewCharacterStat != nullptr);

	CurrentCharacterStat = NewCharacterStat;

	NewCharacterStat->OnHPChange.AddUObject(this, &UCSPlayerWidget::UpdateHPWidget);
}

//UI �ý����� �غ� �Ǹ� ȣ�� UI������ Beginplay���� ȣ��ǹǷ� postinitializecomponents�Լ����� �߻��� ����� UI�� �ݿ����� ����. ���� �� �Լ����� ���� ������ �������ϴ� ������ ����
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



