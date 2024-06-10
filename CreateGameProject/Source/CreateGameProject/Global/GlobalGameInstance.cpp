// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/GlobalGameInstance.h"
#include "Global/DataTable/GlobalActorRow.h"
#include "CreateGameProject.h"

UGlobalGameInstance::UGlobalGameInstance()
{

}

const FGlobalActorRow* UGlobalGameInstance::GetActorData(FName _Name)
{
	if (nullptr == ActorDataTable)
	{
		// 터져라!!!
		//UE_LOG(LogTemp, Fatal, TEXT("DataTable 세팅을 하지 않았음!!"));
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

const FSideScrollGameSettingRow* UGlobalGameInstance::GetSideScrollData()
{
	if (nullptr == SideScrollData)
	{
		UE_LOG(MyGameLog, Fatal, TEXT("%S(%u)> if (nullptr == SideScrollData)"), __FUNCTION__, __LINE__);
	}

	FSideScrollGameSettingRow* Data = SideScrollData->FindRow<FSideScrollGameSettingRow>(TEXT("Data"), nullptr);
	if (nullptr == Data)
	{
		UE_LOG(MyGameLog, Error, TEXT("%S(%u) > Side Scroll Data Is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Data;
}
