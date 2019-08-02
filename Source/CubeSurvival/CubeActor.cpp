// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeActor.h"

#define CUBE_PATH "/Game/Cube/"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CSLOG(Warning, TEXT("ACubeActor Constructor"));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));

	RootComponent = Body;


}

ACubeActor::~ACubeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CSLOG(Warning, TEXT("ACubeActor Distructor"));

}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACubeActor::InitializeSetStaticMesh(const TCHAR* ContentPath)
{
	UStaticMesh* NewMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, ContentPath));
	if (NewMesh)
	{
		Body->SetStaticMesh(NewMesh);
	}

}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeActor::Initialize(FString TextureName)
{
	this->TextureName = TextureName;
	InitializeSetStaticMesh(*(CUBE_PATH + TextureName));
}

