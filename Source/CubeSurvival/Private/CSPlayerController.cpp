// Fill out your copyright notice in the Description page of Project Settings.

#include "CSPlayerController.h"




void ACSPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
 }
void ACSPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);
 }

void ACSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
