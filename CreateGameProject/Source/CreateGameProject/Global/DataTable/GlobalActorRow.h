// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GlobalActorRow.generated.h"

/**
 * 
 */
USTRUCT(Blueprinttype)
struct FGlobalActorRow : public FTableRowBase
{
	GENERATED_BODY()
	
public :
	
	// EditAnyWhere : 에디터에서 사용하겠다.
	// BlueprintReadWrite : 블루프린트에서 편집 가능.
	// Catagory = "Resources"

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TSubclassOf<AActor> ActorUClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	class UPaperSprite* ActorSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	class UStaticMesh* ActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	class USkeletalMesh* ActorSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	class USoundWave* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float Speed;
};
