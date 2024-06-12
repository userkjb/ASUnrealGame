// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWorldLevel/TestWorldCharacter.h"

// Sets default values
ATestWorldCharacter::ATestWorldCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestWorldCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestWorldCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

