// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBox.h"
#include "CSWeaponActor.h"
#include "CSItemResourceManager.h"

#include "CSPlayerCharacter.h"
#include "CSPlayerController.h"
#include "CSHUDWidget.h"

#include "CSGameInstance.h"
// Sets default values
AItemBox::AItemBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("StaticMesh'/Game/Cube/co_floor_wood_b01.co_floor_wood_b01'"));//아이템 박스 메시 바꿀것

	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = ACSWeaponActor::StaticClass();
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	auto CSGameInstance = Cast<UCSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int rndNum = FMath::RandRange(0, CSGameInstance->GetItemImageResourceManager()->ImageResource.Num() - 1);
	ItemImage = CSGameInstance->GetItemImageResourceManager()->ImageResource[rndNum];
	
	//CSLOG(Warning, TEXT("%s"), *ItemImage->GetFName().ToString());
}

void AItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnCharacterOverlap);
}

void AItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto CSCharacter = Cast<ACSPlayerCharacter>(OtherActor);
	CSCHECK(CSCharacter != nullptr);
	if (CSCharacter != nullptr&&WeaponItemClass != nullptr)
	{
		//TODO: PlayerControle를 통해서 hudwidget를 받아와야하는 playercharacter에서 컨트롤러를 받아올 수 있다.
		//CSCharacter->playercon
		CSCharacter->GetPlayerController()->GetHUDWidget()->InsertItem(ItemImage);
		CSCharacter->SetWeapon(ItemImage->GetFName().ToString());
		Destroy();
		/*
			if (ABCharacter->CanSetWeapon())
			{
				auto NewWeapon = GetWorld()->SpawnActor<AABWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
				ABCharacter->SetWeapon(NewWeapon);
				Effect->Activate(true);
				Box->SetHiddenInGame(true, true);
				SetActorEnableCollision(false);
				Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
			}
			else
			{
				ABLOG(Warning, TEXT("%s can't equip weapon currently."), *ABCharacter->GetName());
			}
		*/
	}

}