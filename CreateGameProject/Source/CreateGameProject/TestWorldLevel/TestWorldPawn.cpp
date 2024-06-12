// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWorldLevel/TestWorldPawn.h"

// Sets default values
ATestWorldPawn::ATestWorldPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestWorldPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestWorldPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestWorldPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

