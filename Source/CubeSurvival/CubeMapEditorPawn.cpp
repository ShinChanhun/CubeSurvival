// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeMapEditorPawn.h"


ACubeMapEditorPawn::ACubeMapEditorPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ACubeMapEditorPawn::BeginPlay()
{
	Super::BeginPlay();

	MapDataPath = "EditMapData";

}

// Called every frame
void ACubeMapEditorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Zoom in if ZoomIn button is down, zoom back out if it's not
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}

	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotation);
	}

	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 100 units per second
			MovementInput = MovementInput.GetSafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void ACubeMapEditorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//Hook up every-frame handling for our four axes
	//InputComponent->BindAxis("MoveForwardME", this, &ACubeMapEditorPawn::MoveForward);
	//InputComponent->BindAxis("MoveRightME", this, &ACubeMapEditorPawn::MoveRight);
	//InputComponent->BindAxis("CameraPitchME", this, &ACubeMapEditorPawn::PitchCamera);
	//InputComponent->BindAxis("CameraYawME", this, &ACubeMapEditorPawn::YawCamera);

	//Hook up events for "ZoomIn"					
	//InputComponent->BindAction("ZoomInME", IE_PresIE_Pressed,sed, this, &ACubeMapEditorPawn::ZoomIn);
	//InputComponent->BindAction("ZoomInME", IE_ReleIE_Pressed,ased, this, &ACubeMapEditorPawn::ZoomOut);
	//InputComponent->BindAction("ClickME", IE_Pressed, this, &ACubeMapEditorPawn::ClickActor);


	//InputComponent->BindAction("CubeRotationRight", IE_Pressed, this, &ACubeMapEditorPawn::RotionSelectedActor_Right);
	//InputComponent->BindAction("CubeRotationLeft", IE_Pressed, this, &ACubeMapEditorPawn::RotationSelectedActor_Left);

	//InputComponent->BindAction("CubeMoveTop", IE_Pressed, this, &ACubeMapEditorPawn::MoveSelectedActor_Top);
	//InputComponent->BindAction("CubeMoveBottom", IE_Pressed, this, &ACubeMapEditorPawn::MoveSelectedActor_Bottom);
	//InputComponent->BindAction("CubeMoveUp", IE_Pressed, this, &ACubeMapEditorPawn::MoveSelectedActor_Up);
	//InputComponent->BindAction("CubeMoveDown", IE_Pressed, this, &ACubeMapEditorPawn::MoveSelectedActor_Down);
	//InputComponent->BindAction("CubeMoveRight", IE_Pressed, this, &ACubeMapEditorPawn::MoveSelectedActor_Right);
	//InputComponent->BindAction("CubeMoveLeft", IE_Pressed, this, &ACubeMapEditorPawn::MoveSelectedActor_Left);

	//InputComponent->BindAction("CubeMapSave", IE_Pressed, this, &ACubeMapEditorPawn::WriteCubeMapToJson);
	//InputComponent->BindAction("CubeMapLoad", IE_Pressed, this, &ACubeMapEditorPawn::ReadJsonToCubeMap);

}

//Input functions
void ACubeMapEditorPawn::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACubeMapEditorPawn::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACubeMapEditorPawn::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ACubeMapEditorPawn::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ACubeMapEditorPawn::ZoomIn()
{
	bZoomingIn = true;
}

void ACubeMapEditorPawn::ZoomOut()
{
	bZoomingIn = false;
}

void ACubeMapEditorPawn::ClickActor()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		FHitResult TraceResult(ForceInit);

		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

		if (TraceResult.GetActor() != nullptr)
		{
			CSLOG(Warning, TEXT("%s"), *TraceResult.GetActor()->GetName());

			SelectedActor = TraceResult.GetActor();
		}
	}
}

void ACubeMapEditorPawn::RotionSelectedActor_Right()
{
	if (SelectedActor == nullptr) return;

	FRotator Rotator = SelectedActor->GetActorRotation();

	Rotator.Yaw = 90;
	SelectedActor->AddActorLocalRotation(Rotator);

	CSLOG(Warning, TEXT("%s %f"), *SelectedActor->GetName(), Rotator.Roll);
}

void ACubeMapEditorPawn::RotationSelectedActor_Left()
{
	if (SelectedActor == nullptr) return;

	FRotator Rotator = SelectedActor->GetActorRotation();

	Rotator.Yaw = -90;
	SelectedActor->AddActorLocalRotation(Rotator);

	CSLOG(Warning, TEXT("%s %f"), *SelectedActor->GetName(), Rotator.Roll);
}



void ACubeMapEditorPawn::MoveSelectedActor_Up()
{
	if (SelectedActor == nullptr) return;

	FVector Location = SelectedActor->GetActorLocation();

	FVector Vector(CUBE_SIZE, 0, 0);

	SelectedActor->SetActorLocation(Location + Vector);

}

void ACubeMapEditorPawn::MoveSelectedActor_Down()
{
	if (SelectedActor == nullptr) return;

	FVector Location = SelectedActor->GetActorLocation();

	FVector Vector(-CUBE_SIZE, 0, 0);
	SelectedActor->SetActorLocation(Location + Vector);


}

void ACubeMapEditorPawn::MoveSelectedActor_Top()
{
	if (SelectedActor == nullptr) return;

	FVector Location = SelectedActor->GetActorLocation();

	FVector Vector(0, 0, CUBE_SIZE);
	SelectedActor->SetActorLocation(Location + Vector);


}

void ACubeMapEditorPawn::MoveSelectedActor_Bottom()
{
	if (SelectedActor == nullptr) return;

	FVector Location = SelectedActor->GetActorLocation();

	FVector Vector(0, 0, -CUBE_SIZE);
	SelectedActor->SetActorLocation(Location + Vector);

}

void ACubeMapEditorPawn::MoveSelectedActor_Right()
{
	if (SelectedActor == nullptr) return;

	FVector Location = SelectedActor->GetActorLocation();

	FVector Vector(0, CUBE_SIZE, 0);
	SelectedActor->SetActorLocation(Location + Vector);
}

void ACubeMapEditorPawn::MoveSelectedActor_Left()
{
	if (SelectedActor == nullptr) return;

	FVector Location = SelectedActor->GetActorLocation();

	FVector Vector(0, -CUBE_SIZE, 0);
	SelectedActor->SetActorLocation(Location + Vector);
}

TArray<AActor*> ACubeMapEditorPawn::FindAllCubeActorsInWorld()
{
	TSubclassOf<AActor> ClassToFind;
	TArray<AActor*> FoundActors;
	TArray<AActor*> FoundCube;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	GetFolderPath();

	CSLOG(Warning, TEXT("%s"), *GetFolderPath().ToString());

	for (AActor* item : FoundActors)
	{
		if (item->GetFName().ToString().Contains("CubeValue") == true)
		{
			CSLOG(Warning, TEXT("%s"), *item->GetFName().ToString());

			FoundCube.Add(item);
		}
	}

	return FoundCube;
}

void ACubeMapEditorPawn::ParseActorToMapData()
{
	TArray<AActor*> FoundCube = FindAllCubeActorsInWorld();

	for (AActor* item : FoundCube)
	{
		FVector position = item->GetActorLocation();
		
		Maps.Add(
			FMapData::CreateMapDataStruct(
				Maps.Num() + 1,
				item->GetFName().ToString(),
				item->GetActorLocation(),
				item->GetActorRotation().Vector()
			)
		);
	}
}

void ACubeMapEditorPawn::WriteCubeMapToJson()
{
	if (GetWorld() != nullptr)
	{
		CSLOG(Warning, TEXT("World Is Null"));
	}

	ParseActorToMapData();

	TWeakObjectPtr<UJsonParsorObject> jo = MakeWeakObjectPtr(NewObject<UJsonParsorObject>());
	jo->WriteMapData(Maps, MapDataPath);
}

void ACubeMapEditorPawn::ReadJsonToCubeMap()
{
	TWeakObjectPtr<UJsonParsorObject> jo = MakeWeakObjectPtr(NewObject<UJsonParsorObject>());

	jo->ReadMapData(Maps, MapDataPath);
}

