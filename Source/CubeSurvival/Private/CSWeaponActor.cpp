// Fill out your copyright notice in the Description page of Project Settings.

#include "CSWeaponActor.h"
#include "CSWeaponResource.h"

// Sets default values
ACSWeaponActor::ACSWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponResource = CreateDefaultSubobject< UCSWeaponResource>(TEXT("WEAPONRESOURCE"));
	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPONMESHCOMPONENT"));

	SetWeaponMesh(TEXT("SM_Sword_F06"));
	RootComponent = (USceneComponent*)WeaponMeshComponent;
	WeaponMeshComponent->SetCollisionProfileName("NoCollision");
	WeaponRange = 200.0f;
}

// Called when the game starts or when spawned
void ACSWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

float ACSWeaponActor::GetAttack(FString WeaponName) const
{
	return WeaponResource->GetCSItemData(WeaponName)->BaseAttack;
}

float ACSWeaponActor::GetAttributeAttack(FString WeaponName) const
{
	return WeaponResource->GetCSItemData(WeaponName)->AttributeAttack;
}

void ACSWeaponActor::SetWeaponMesh(FString WeaponName)
{	
	WeaponMeshComponent->SetStaticMesh(WeaponResource->GetWeaponMesh()[WeaponName]);
}

void ACSWeaponActor::SetWeapon(FString WeaponName)
{
	WeaponMeshComponent->SetStaticMesh(WeaponResource->GetWeaponMesh()[WeaponName]);
	WeaponAttack = GetAttack(WeaponName);
	AttritubeWeaponAttack = GetAttributeAttack(WeaponName);
}