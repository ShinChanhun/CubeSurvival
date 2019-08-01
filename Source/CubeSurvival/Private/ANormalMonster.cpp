// Fill out your copyright notice in the Description page of Project Settings.

#include "ANormalMonster.h"
#include "CS_AIController.h"


// Sets default values
AANormalMonster::AANormalMonster()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//MonsterSetting(this, TEXT("02020002_m_redmushroom"), MonsterSize::MS_Small);

	AIControllerClass = ACS_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Movement->MaxSpeed = 200.0f;

	IsTurn = false;
	TurnRot = FRotator::ZeroRotator;


}

// Called when the game starts or when spawned
void AANormalMonster::BeginPlay()
{
	Super::BeginPlay();//애니메이션이나 캐릭터들 동작이 제대로 이루어지지 않는다면 super가 있는지 확인하자

}

// Called every frame
void AANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsTurn == true)
	{
		timede += DeltaTime;
	}

}

// Called to bind functionality to input
void AANormalMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


