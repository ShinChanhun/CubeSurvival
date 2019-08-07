// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonParsorObject.h"

#define PROJECT_DIR_PATH FPaths::ProjectContentDir()
#define DATA_DIR PROJECT_DIR_PATH + "Data/"
#define MAP_DATA "MapData"
#define MAPDATA_PATH DATA_DIR + MAP_DATA

void UJsonParsorObject::Write(FString Path)
{
	//FString jsonstr;
	//TSharedRef<TJsonWriter<TCHAR>> jsonObj = TJsonWriterFactory<>::Create(&jsonstr);

	//jsonObj->WriteObjectStart();

	////TODO: Empty

	//jsonObj->WriteObjectEnd();
	//jsonObj->Close();

	//FString DirectoryFilePath = PROJECT_DIR_PATH + Path;
	//FFileHelper::SaveStringToFile(*jsonstr, *DirectoryFilePath);
}

void UJsonParsorObject::WriteMapData(TArray<struct FMapData>& ArrMapData, FString Path)
{
	FString jsonstr;
	TSharedRef<TJsonWriter<TCHAR>> jsonObj = TJsonWriterFactory<>::Create(&jsonstr);


	TArray<int32> Position = { 0,0,0 };
	TArray<int32> Rotation = { 0,0,0 };

	jsonObj->WriteObjectStart();
	jsonObj->WriteIdentifierPrefix("MapDataStructs");
	jsonObj->WriteArrayStart();

	for (const FMapData& item : ArrMapData)
	{
		//TODO: 동적으로 작업 시간적 여유가 부족하기에 추후 작업
#pragma region DynamicRegion


		//for (TFieldIterator<UStructProperty> It(item.StaticStruct()); It; ++It)
		//{
		//	UProperty* Property = *It;
		//	if (It->IsA(UIntProperty::StaticClass()))
		//	{
		//		UIntProperty *IntProp = CastChecked<UIntProperty>(*It);
		//		int32 a = IntProp->GetPropertyValue(IntProp);
		//		//int32 value = IntProp->GetSignedIntPropertyValue(Property->ContainerPtrToValuePtr<int32>());
		//		jsonObj->WriteValue(Property->GetName(), a);

		//	}
		//	else if (It->IsA(UClass::StaticClass()))
		//	{
		//		//FString *IntProp = CastChecked<FString>(*It);
		//		jsonObj->WriteValue(Property->GetName(), *It);

		//	}
		//	else if (It->IsA(UStruct::StaticClass()))
		//	{
		//		UStructProperty* aaaa = *It;
		//		FVector* pv = aaaa->ContainerPtrToValuePtr<FVector>(this);

		//		UFloatProperty *FloatProp = CastChecked<UFloatProperty>(*It);
		//		float a = FloatProp->GetPropertyValue(FloatProp);
		//		//int32 value = IntProp->GetSignedIntPropertyValue(Property->ContainerPtrToValuePtr<int32>());
		//		jsonObj->WriteValue(Property->GetName(), a);
		//		//FString *IntProp = CastChecked<FString>(*It);
		//		//jsonObj->WriteValue(Property->GetName(), IntProp);

		//	}
		//	//jsonObj->WriteValue("Type", item.Type);

		//}
#pragma endregion

		//정적으로 작업
		//jsonObj->WriteIdentifierPrefix("MapDataStructs");

		jsonObj->WriteObjectStart();

		jsonObj->WriteValue("ID", item.ID);
		jsonObj->WriteValue("Type", item.Type);
		Position[0] = item.Position.X;
		Position[1] = item.Position.Y;
		Position[2] = item.Position.Z;
		Rotation[0] = item.Rotation.X;
		Rotation[1] = item.Rotation.Y;
		Rotation[2] = item.Rotation.Z;
		jsonObj->WriteValue("Position", Position);
		jsonObj->WriteValue("Rotation", Rotation);
		jsonObj->WriteValue("TextureName", item.TextureName);

		jsonObj->WriteObjectEnd();
	}

	jsonObj->WriteArrayEnd();
	jsonObj->WriteObjectEnd();

	jsonObj->Close();

	FString DirectoryFilePath = DATA_DIR + Path;

	FFileHelper::SaveStringToFile(*jsonstr, *DirectoryFilePath);
}

TArray<struct FMapData> UJsonParsorObject::Read(FString Path)
{
	FString DirectoryFilePath = PROJECT_DIR_PATH + Path;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(DirectoryFilePath));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<struct FMapData> MapDataStruct;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		GenerateStructsFromJson(MapDataStruct, JsonObject);
	}
	else
	{
		//CSLOG(WARNING_LOCATION, TEXT("Error : Could not open json file"));
	}

	return MapDataStruct;
}

void UJsonParsorObject::ReadMapData(TArray<struct FMapData>& ArrMapData, FString Path)
{
	FString jsonstr = JsonFullPath(Path);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonstr);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	IsJsonDeserialize = FJsonSerializer::Deserialize(JsonReader, JsonObject);
	IsJsonObjectIsValid = JsonObject.IsValid();

	if (IsJsonDeserialize && IsJsonObjectIsValid)
	{
		GenerateStructsFromJson(ArrMapData, JsonObject);
	}
	else
	{
		//TODO:에러 표기
	}

}

void UJsonParsorObject::GenerateStructsFromJson(TArray<struct FMapData> &MapDataStructs, TSharedPtr<FJsonObject> JsonObject)
{
	TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("MapDataStructs"));

	for (int32 i = 0; i < objArray.Num(); i++)
	{
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();

		int32 MapDataID = json->GetIntegerField(TEXT("ID"));
		FString  MapDataType = json->GetStringField(TEXT("Type"));
		FVector  MapDataPosition = ParseAsVector(json, TEXT("Position"));
		FVector MapDataRotation = ParseAsVector(json, TEXT("Rotation"));
		FString  MapDataTextureName = json->GetStringField(TEXT("TextureName"));

		FMapData MapDataStruct = FMapData::CreateMapDataStruct(
			MapDataID,
			MapDataType,
			MapDataPosition,
			MapDataRotation
		);

		MapDataStructs.Push(MapDataStruct);
	}
}

FString UJsonParsorObject::JsonFullPath(FString Path)
{
	FString FullPath = FPaths::ProjectContentDir() + "Data/";
	FullPath += Path;
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);

	return JsonStr;
}

FVector UJsonParsorObject::ParseAsVector(TSharedPtr<FJsonObject> json, FString KeyName)
{
	TArray<FString> ArrayJson;

	json->TryGetStringArrayField(*KeyName, ArrayJson);

	FVector Vector = FVector{
		FCString::Atof(*ArrayJson[0]),
		FCString::Atof(*ArrayJson[1]),
		FCString::Atof(*ArrayJson[2])
	};

	return Vector;
}

FRotator UJsonParsorObject::ParseAsRotator(TSharedPtr<FJsonObject> json, FString KeyName)
{
	TArray<FString> ArrayJson;
	json->TryGetStringArrayField(*KeyName, ArrayJson);
	FRotator Rotator = FRotator{
		FCString::Atof(*ArrayJson[0]),
		FCString::Atof(*ArrayJson[1]),
		FCString::Atof(*ArrayJson[2])
	};
	return Rotator;
}

void UJsonParsorObject::GetGameState()
{
	//UE_LOG(LogTemp, Log, GetWorld()->GetGameState.GetTypedOuter().ToString());
	//GetWorld()->GetGameState.GetTypedOuter;
	/*auto a = Cast<ACSGameStateBase>(GetWorld()->GetGameState());
	a->*/
}

