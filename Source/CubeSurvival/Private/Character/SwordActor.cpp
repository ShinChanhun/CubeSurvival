// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordActor.h"


// Sets default values
ASwordActor::ASwordActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Weapon_Mesh(TEXT("StaticMesh'/Game/Model/Player/Nana/Meshes/SM_Sword_F06.SM_Sword_F06'"));
	if (Weapon_Mesh.Succeeded())
	{
		WeaponMesh->SetStaticMesh(Weapon_Mesh.Object);
	}
	RootComponent = (USceneComponent*)WeaponMesh;

	WeaponMesh->SetCollisionProfileName("NoCollision");

}


