// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/Actor.h"
#include "CSWeaponActor.generated.h"

UCLASS()
class CUBESURVIVAL_API ACSWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACSWeaponActor();

	void SetWeaponMesh(FString WeaponName);
	void SetWeapon(FString WeaponName);
	float GetAttack(FString WeaponName) const;
	float GetAttributeAttack(FString WeaponName) const;
	float GetAttack() const { return WeaponAttack; }
	float GetAttributeAttack() const { return AttritubeWeaponAttack; }
	float GettWeaponRange() const { return WeaponRange; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


public:

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class UCSWeaponResource* WeaponResource;

private:
	float WeaponAttack;
	float AttritubeWeaponAttack;
	float WeaponRange;


};
