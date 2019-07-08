// Fill out your copyright notice in the Description page of Project Settings.

#include "CSGameInstance.h"



void UCSGameInstance::OnStart()
{
	UJsonParsorObject * jpo = (UJsonParsorObject*)GetTransientPackage();

	jpo->Write("aa");

}
