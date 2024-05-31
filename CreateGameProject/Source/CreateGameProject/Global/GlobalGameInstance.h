// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CREATEGAMEPROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UGlobalGameInstance();

	// ��� UClass�� �� �ʿ� ������ TSubclassOf�� ����ؼ� ������ �ش�.
	//UPROPERTY(Category = Pawn, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<AActor> TestActorSubClass = nullptr;

	UPROPERTY(Category = Pawn, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> TestActorSubClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UPaperSprite*> Sprites;
};
