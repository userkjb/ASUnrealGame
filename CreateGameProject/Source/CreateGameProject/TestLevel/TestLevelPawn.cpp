// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestLevelPawn.h"

// Sets default values
ATestLevelPawn::ATestLevelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestLevelPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestLevelPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestLevelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

