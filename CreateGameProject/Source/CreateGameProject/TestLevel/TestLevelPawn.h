// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestLevelPawn.generated.h"

UCLASS()
class CREATEGAMEPROJECT_API ATestLevelPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestLevelPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Val);
	void MoveForward(float Val);
	void MoveUp_World(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

private:
	static FName MovementComponentName;
	static FName CollisionComponentName;
	static FName MeshComponentName;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> CollisionComponent;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPawnMovementComponent> MovementComponent;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> MeshComponent;

	float BaseTurnRate;
	float BaseLookUpRate;
	uint32 bAddDefaultMovementBindings = 1;
};
