// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "TestWorldSettingRow.generated.h"


USTRUCT(BlueprintType)
struct FTestWorldPlayerData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float PlayerMoveSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float PlayerRunSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float PlayerJumpPower = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int PlayerJumpMaxCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int Hp = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int Mp = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int DefaultDamage = 5;
};












/**
 *  This Main Struct
 */
USTRUCT(BlueprintType)
struct FTestWorldSettingRow : public FTableRowBase
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FTestWorldPlayerData PlayerData;
};
