// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CubeSurvival.h"
#include "GameFramework/Pawn.h"
#include "JsonParsorObject.h"
#include "CubeMapEditorPawn.generated.h"

UCLASS(Blueprintable)
class CUBESURVIVAL_API ACubeMapEditorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACubeMapEditorPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;

	//Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();


	//Cube Map Editor
	void ClickActor();
	void RotionSelectedActor_Right();
	void RotationSelectedActor_Left();

	//UP-Down:X
	void MoveSelectedActor_Up();
	void MoveSelectedActor_Down();
	//Top-Bottn:Y
	void MoveSelectedActor_Top();
	void MoveSelectedActor_Bottom();
	//Right-Left:Z
	void MoveSelectedActor_Right();
	void MoveSelectedActor_Left();

	void ParseActorToMapData();

	UFUNCTION(BlueprintCallable, Category = "MapEditor")
	void WriteCubeMapToJson();
	UFUNCTION(BlueprintCallable, Category = "MapEditor")
	void ReadJsonToCubeMap();

	TArray<AActor*> FindAllCubeActorsInWorld();

private:
	UPROPERTY()
	TArray<FMapData> Maps;

public:
	UPROPERTY(BlueprintReadOnly)
	AActor* SelectedActor;

	UPROPERTY(EditAnywhere)
	FString MapDataPath;
};
