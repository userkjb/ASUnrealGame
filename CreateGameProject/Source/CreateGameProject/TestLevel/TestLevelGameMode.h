// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TestLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CREATEGAMEPROJECT_API ATestLevelGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected :
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTransform CPPTrans;


	UPROPERTY(Category = Pawn, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UClass* CreateClass = nullptr;
};
