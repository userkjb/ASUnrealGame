// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

private :
	UPROPERTY(Category = "Side", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(Category = "Side", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;


	
	float GravityPower; // 누적된 중력.
};
