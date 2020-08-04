// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "UObject/NoExportTypes.h"
#include "CSItemResourceManager.generated.h"

/**
 * 
 */
UCLASS()
class CUBESURVIVAL_API UCSItemResourceManager : public UObject
{
	GENERATED_BODY()

public:
	UCSItemResourceManager();
	
	UPROPERTY()
	TArray< class UTexture2D*> ImageResource;

private:


	
};
