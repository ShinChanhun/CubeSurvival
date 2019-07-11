// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
//#include "Engine/SkeletalMesh.h"
//#include "Classes/Components/SkeletalMeshComponent.h"
#include "UObject/NoExportTypes.h"
#include "UCharacterObject.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UUCharacterObject : public UObject
{
	GENERATED_BODY()
	
public:
	UUCharacterObject();

	USkeletalMesh* GetPlayerMesh() const;

	class TSubclassOf<UAnimInstance> GetPlayerAnimClass() const;

private:
	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMesh* PlayerMesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)




		class TSubclassOf<UAnimInstance> PlayerAnimClass;
	
	
};
