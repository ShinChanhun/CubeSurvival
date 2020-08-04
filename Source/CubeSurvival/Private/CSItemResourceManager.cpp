// Fill out your copyright notice in the Description page of Project Settings.

#include "CSItemResourceManager.h"


UCSItemResourceManager::UCSItemResourceManager()
{
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> SM_Sword_F06_Image(TEXT("Texture2D'/Game/Textures/SM_Sword_F06.SM_Sword_F06'"));
	if (SM_Sword_F06_Image.Succeeded())
	{
		ImageResource.Add(SM_Sword_F06_Image.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> WornoutClub_Image(TEXT("Texture2D'/Game/Textures/13200004_wornoutclub.13200004_wornoutclub'"));
	if (WornoutClub_Image.Succeeded())
	{
		ImageResource.Add(WornoutClub_Image.Object);
	}
	//
	static ConstructorHelpers::FObjectFinder<UTexture2D> StrongClub_Image(TEXT("Texture2D'/Game/Textures/13200005_strongclub.13200005_strongclub'"));
	if (StrongClub_Image.Succeeded())
	{
		ImageResource.Add(StrongClub_Image.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> Arenaa02Sword_Image(TEXT("Texture2D'/Game/Textures/13200268_arenaa02sword.13200268_arenaa02sword'"));
	if (Arenaa02Sword_Image.Succeeded())
	{
		ImageResource.Add(Arenaa02Sword_Image.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> UgclongSword02_Image(TEXT("Texture2D'/Game/Textures/13200314_ugclongsword02.13200314_ugclongsword02'"));
	if (UgclongSword02_Image.Succeeded())
	{
		ImageResource.Add(UgclongSword02_Image.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> FireprismSword_Image(TEXT("Texture2D'/Game/Textures/13200266_fireprismsword.13200266_fireprismsword'"));
	if (FireprismSword_Image.Succeeded())
	{
		ImageResource.Add(FireprismSword_Image.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> Frozen02longSword_Image(TEXT("Texture2D'/Game/Textures/13200302_frozen02longsword.13200302_frozen02longsword'"));
	if (Frozen02longSword_Image.Succeeded())
	{
		ImageResource.Add(Frozen02longSword_Image.Object);
	}
}

