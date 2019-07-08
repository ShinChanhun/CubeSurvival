// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonParsorObject.h"

void UJsonParsorObject::Write(FString path)
{
	FString jsonstr;	// Recive save json text
	TSharedRef<TJsonWriter<TCHAR>> jsonObj = TJsonWriterFactory<>::Create(&jsonstr);
	jsonObj->WriteObjectStart();
	
	TArray<int32> arr = {1,2,3};
	//FJsonValueArray a = new FJsonValueArray(,);

	jsonObj->WriteValue("a", arr);	// Value type : bool, int, float, string
	//jsonObj->

	//jsonObj

	jsonObj->WriteObjectEnd();
	jsonObj->Close();

	FFileHelper::SaveStringToFile(*jsonstr, *path);	// Save json to filePath
}

TArray<FMapData> UJsonParsorObject::GenerateStructsFromJson(FString Path){	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(Path));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<FMapData> MapDataStruct;
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		GenerateStructsFromJson(MapDataStruct, JsonObject);
	}
	else {

	}

	return MapDataStruct;
}

void UJsonParsorObject::Read(FString path)
{

}


void UJsonParsorObject::GenerateStructsFromJson(
	TArray<FMapData> &AwesomeStructs,
	TSharedPtr<FJsonObject> JsonObject
)
{
	FVector PrevEndPoint = FVector{ 0,0,0 };
	TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("MapDataStructs"));

	for (int32 i = 0; i < objArray.Num(); i++)
	{
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();

		FVector  MapDataPosition = ParseAsVector(json, FString("MapPosition"));
		FString  MapDataType = json->GetStringField(TEXT("MapType"));

		FMapData MapDataStruct = FMapData::CreateFMapDataStruct(
			MapDataPosition, 
			MapDataType
		);

		AwesomeStructs.Push(MapDataStruct);
	}
}

FString UJsonParsorObject::JsonFullPath(FString Path)
{
	FString FullPath = FPaths::GameContentDir();
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