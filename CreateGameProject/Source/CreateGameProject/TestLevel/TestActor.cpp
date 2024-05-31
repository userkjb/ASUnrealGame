// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestActor.h"
#include "Global/GlobalGameInstance.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nullptr == SpriteComponent)
	{
		return;
	}

	Time += DeltaTime;
	if (0.5f <= Time)
	{
		UGlobalGameInstance* Ptr = GetWorld()->GetGameInstanceChecked<UGlobalGameInstance>();

		if (SpriteIndex == 0)
		{
			SpriteIndex = 1;
		}
		else
		{
			SpriteIndex = 0;
		}

		SpriteComponent->SetSprite(Ptr->Sprites[SpriteIndex]);

		Time = 0.0f;
	}
}

