// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/Actor.h"
#include "AWeaponActor.generated.h"

UCLASS()
class CUBESURVIVAL_API AAWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAWeaponActor();

protected:


public:	

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent* Weapon;
	
	
};
