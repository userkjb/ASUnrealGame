// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/DataTable/SideScrollGameSettingRow.h"
#include "SideScrollCharacter.generated.h"

UCLASS()
class CREATEGAMEPROJECT_API ASideScrollCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASideScrollCharacter();

	UFUNCTION(BlueprintCallable)
	void FrontMove(float _DeltaTime);

	UFUNCTION(BlueprintCallable)
	void BackMove(float _DeltaTime);

	UFUNCTION(BlueprintCallable)
	void JumpMove();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Gravity(float _DeltaTime);

private :
	UPROPERTY(Category = "Side", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(Category = "Side", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// DT 담는 상수.
	const FSideScrollGameSettingRow* SideScrollData;
	FSideScrollPlayerData PlayerData;

	// 추가한 콜리전 담는 변수
	UPROPERTY(Category = "Contents", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* GainCollisionPtr;

	
	float GravityPower = 0.0f; // 누적된 중력.
};
