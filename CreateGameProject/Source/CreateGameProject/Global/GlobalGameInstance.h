// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "Engine/DataTable.h"
#include "GlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CREATEGAMEPROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	

	// ��� UClass�� �� �ʿ� ������ TSubclassOf�� ����ؼ� ������ �ش�.
	//UPROPERTY(Category = Pawn, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<AActor> TestActorSubClass = nullptr;

	//UPROPERTY(Category = Pawn, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//TArray<TSubclassOf<AActor>> TestActorSubClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<class UPaperSprite*> Sprites;

	// Table ��ȯ �Լ�.
	const struct FGlobalActorRow* GetActorData(FName _Name);

private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* ActorDataTable;

	UGlobalGameInstance();
};
