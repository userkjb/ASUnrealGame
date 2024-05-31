// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestLevelGameMode.h"
#include "Global/GlobalGameInstance.h"

void ATestLevelGameMode::BeginPlay()
{
	UGlobalGameInstance* Ptr = GetWorld()->GetGameInstanceChecked<UGlobalGameInstance>();
	FTransform Trans;
	Trans.SetLocation(FVector(0.0, 0.0, 100.0));
	//GetWorld()->SpawnActor<AActor>(CreateClass, Trans);
	GetWorld()->SpawnActor<AActor>(Ptr->TestActorSubClass[0], Trans);
}
