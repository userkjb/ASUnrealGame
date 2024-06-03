// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestLevelCharacter.h"

// Sets default values
ATestLevelCharacter::ATestLevelCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestLevelCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestLevelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestLevelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

