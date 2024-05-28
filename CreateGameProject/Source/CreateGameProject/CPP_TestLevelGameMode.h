// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CPP_TestLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CREATEGAMEPROJECT_API ACPP_TestLevelGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected :
	void BeginPlay();
	void Tick(float _DeltaTime) override;

public :
};
