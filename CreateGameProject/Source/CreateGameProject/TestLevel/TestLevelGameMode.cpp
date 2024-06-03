// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestLevelGameMode.h"
#include "Global/DataTable/GlobalActorRow.h"
#include "Global/GlobalGameInstance.h"

void ATestLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGlobalGameInstance* Ptr = GetWorld()->GetGameInstanceChecked<UGlobalGameInstance>();
	const FGlobalActorRow* ActorData = Ptr->GetActorData(TEXT("TestData"));

	if (nullptr == ActorData)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> MonsterData Data Is Null"), __FUNCTION__, __LINE__);
		return;
	}

	if (nullptr == ActorData->ActorUClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> MonsterData Data Is Null"), __FUNCTION__, __LINE__);
		return;
	}

	FTransform Trans;
	//Trans.SetLocation(FVector(0.0, 0.0, 100.0));
	//GetWorld()->SpawnActor<AActor>(CreateClass, Trans);
	GetWorld()->SpawnActor<AActor>(ActorData->ActorUClass, Trans);
}
