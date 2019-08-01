// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ACharacterBase.generated.h"

UCLASS()
class CUBESURVIVAL_API AACharacterBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetHP() { return CharacterHP; }
	virtual void SetHP(float _HP) { CharacterHP = _HP; }

	virtual float GetMoveSpeed() { return CharacterMoveSpeed; }
	virtual void SetMoveSpeed(float Speed) { CharacterMoveSpeed = Speed; }

private:
	float CharacterHP;
	float CharacterMoveSpeed;
	
};
