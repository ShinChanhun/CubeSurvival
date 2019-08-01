// Fill out your copyright notice in the Description page of Project Settings.

#include "AMonsterCharacterBase.h"




// Sets default values
AAMonsterCharacterBase::AAMonsterCharacterBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MonsterCharacter = CreateDefaultSubobject<UUCharacterObject>(TEXT("MonsterModel"));

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	//기본 캡슐 베이스와 메시 위치 
	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	
}

// Called when the game starts or when spawned
void AAMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AAMonsterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//
//void AAMonsterCharacterBase:: MonsterSetting(class AAMonsterCharacterBase* SetCharacter, FString MonsterName, MonsterSize MSSize )
//{
//	if (MonsterName.Len()<=0)
//	{
//		CSLOG(Warning,  TEXT("MonterName Null"));
//		return;
//	}
//
//	
//	switch (MSSize)
//	{
//	case MonsterSize::MS_Small:
//		SetCharacter->RootComponent = SetCharacter->Capsule;
//		SetCharacter->Mesh->SetupAttachment(SetCharacter->Capsule);
//		SetCharacter->Capsule->SetCapsuleHalfHeight(28.0f);
//		SetCharacter->Capsule->SetCapsuleRadius(28.0f);
//		SetCharacter->Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -30.0f), FRotator(0.0f, 0.0f, 0.0f));
//
//		Mesh->SetSkeletalMesh(MonsterCharacter->GetMonsterMesh()[MonsterName]);
//		Mesh->SetAnimInstanceClass(MonsterCharacter->GetNormalMonsterAnim()[MonsterName]);
//		break;
//	case MonsterSize::MS_Middle:
//		break;
//	case MonsterSize::MS_Big:
//		break;
//
//	}
//
//}
//
