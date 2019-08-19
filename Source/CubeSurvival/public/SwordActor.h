// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/Actor.h"
#include "SwordActor.generated.h"

UCLASS()
class CUBESURVIVAL_API ASwordActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwordActor();


public:	


	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent* WeaponMesh;
	
};
