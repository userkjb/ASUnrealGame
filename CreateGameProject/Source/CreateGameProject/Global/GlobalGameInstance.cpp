// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalGameInstance.h"
#include "Global/DataTable/GlobalActorRow.h"

UGlobalGameInstance::UGlobalGameInstance()
{

}

const FGlobalActorRow* UGlobalGameInstance::GetActorData(FName _Name)
{
	if (nullptr == ActorDataTable)
	{
		// ������!!!
		//UE_LOG(LogTemp, Fatal, TEXT("DataTable ������ ���� �ʾ���!!"));
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u) > nullptr is DataTable"), __FUNCTION__, __LINE__);
	}

	FGlobalActorRow* ActorData = ActorDataTable->FindRow<FGlobalActorRow>(_Name, nullptr);
	if (nullptr == ActorData)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) > %s Name Data Is Nullptr"), __FUNCTION__, __LINE__, *_Name.ToString());
		return nullptr;
	}

	return ActorData;
}
