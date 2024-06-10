// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "SideScrollGameSettingRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSideScrollPlayerData : public FTableRowBase
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float PlayerSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float ViewChracterSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float JumpZVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float GravityScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float FrontMax = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float BackMax = -500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float GravityAccSpeed = -500.0f;

};

USTRUCT(BlueprintType)
struct FSideScrollGameScoreData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int GainCoinScore = 100;
};


USTRUCT(BlueprintType)
struct FSideScrollGameSettingRow : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FSideScrollPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FSideScrollGameScoreData ScoreData;
};