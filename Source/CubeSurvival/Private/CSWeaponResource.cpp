// Fill out your copyright notice in the Description page of Project Settings.

#include "CSWeaponResource.h"




UCSWeaponResource::UCSWeaponResource()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Sword_F06_Mesh(TEXT("StaticMesh'/Game/Model/Player/Nana/Meshes/SM_Sword_F06.SM_Sword_F06'"));
	if (SM_Sword_F06_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("SM_Sword_F06"), SM_Sword_F06_Mesh.Object);
		MonsterNameArray.Add(TEXT("SM_Sword_F06"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WornoutClub_Mesh(TEXT("StaticMesh'/Game/Model/Item/Weapon/13200004_wornoutclub.13200004_wornoutclub'"));
	if (WornoutClub_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("13200004_wornoutclub"), WornoutClub_Mesh.Object);
		MonsterNameArray.Add(TEXT("13200004_wornoutclub"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StrongClub_Mesh(TEXT("StaticMesh'/Game/Model/Item/Weapon/13200005_strongclub.13200005_strongclub'"));
	if (StrongClub_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("13200005_strongclub"), StrongClub_Mesh.Object);
		MonsterNameArray.Add(TEXT("13200005_strongclub"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Arenaa02Sword_Mesh(TEXT("StaticMesh'/Game/Model/Item/Weapon/13200268_arenaa02sword.13200268_arenaa02sword'"));
	if (Arenaa02Sword_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("13200268_arenaa02sword"), Arenaa02Sword_Mesh.Object);
		MonsterNameArray.Add(TEXT("13200268_arenaa02sword"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> UgclongSword02_Mesh(TEXT("StaticMesh'/Game/Model/Item/Weapon/13200314_ugclongsword02.13200314_ugclongsword02'"));//스턴
	if (UgclongSword02_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("13200314_ugclongsword02"), UgclongSword02_Mesh.Object);
		MonsterNameArray.Add(TEXT("13200314_ugclongsword02"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FireprismSword_Mesh(TEXT("StaticMesh'/Game/Model/Item/Weapon/13200266_fireprismsword.13200266_fireprismsword'"));//불검
	if (FireprismSword_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("13200266_fireprismsword"), FireprismSword_Mesh.Object);
		MonsterNameArray.Add(TEXT("13200266_fireprismsword"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Frozen02longSword_Mesh(TEXT("StaticMesh'/Game/Model/Item/Weapon/13200302_frozen02longsword.13200302_frozen02longsword'"));//얼음검
	if (Frozen02longSword_Mesh.Succeeded())
	{
		WeapnMesh.Add(TEXT("13200302_frozen02longsword"), Frozen02longSword_Mesh.Object);
		MonsterNameArray.Add(TEXT("13200302_frozen02longsword"));
	}

	FString WeaponDataPath = TEXT("DataTable'/Game/Data/WeponData.WeponData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CSCHARACTER(*WeaponDataPath);
	CSCHECK(DT_CSCHARACTER.Succeeded());
	CSItemTable = DT_CSCHARACTER.Object;
	CSCHECK(CSItemTable->RowMap.Num() > 0);
}

FCSItemData* UCSWeaponResource::GetCSItemData(FString Name)
{
	return CSItemTable->FindRow<FCSItemData>(FName(*Name), TEXT(""));
}

TMap<FString, UStaticMesh*> UCSWeaponResource::GetWeaponMesh() const
{
	return WeapnMesh;
}