// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScroll/SideScrollCharacter.h"
#include "GameFramework/SpringArmComponent.h" // 스프링 암.
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerInput.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASideScrollCharacter::ASideScrollCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스프링 암
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCommponent"));
	
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	// 2D
	CameraComponent->OrthoWidth = 1280.0f * 2;

	// SpringArmComponent->SetupAttachment(RootComponent);
	// RootComponent == GetRootComponent()
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->bDoCollisionTest = false;
	CameraComponent->SetupAttachment(SpringArmComponent);

	FQuat Rot = UKismetMathLibrary::Quat_MakeFromEuler(FVector(0.0f, 0.0f, -90.0f));
	SpringArmComponent->SetRelativeRotation(Rot);
}

// Called when the game starts or when spawned
void ASideScrollCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASideScrollCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASideScrollCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	//// 이동
	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_Speed", EKeys::A, -1.f));
	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_Speed", EKeys::D, 1.f));

	//// 점프
	//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("DefaultPawn_Jump", EKeys::SpaceBar));

	//
	//PlayerInputComponent->BindAxis("DefaultPawn_Speed", this, &ASideScrollCharacter::SpeedChange);

	//PlayerInputComponent->BindAction("DefaultPawn_Jump", EInputEvent::IE_Pressed, this, &ASideScrollCharacter::PlayerJump);
}

void ASideScrollCharacter::FrontMove(float _DeltaTime)
{

}

void ASideScrollCharacter::BackMove(float _DeltaTime)
{
	
}

void ASideScrollCharacter::JumpMove()
{
	//ACharacter::JumpMaxCount = 2;
	//ACharacter::Jump();
}

//void ASideScrollCharacter::SpeedChange(float _Value)
//{
//	if (_Value != 0)
//	{
//		// 내가 만약 MoveComponent를 가지고 있다면 그 Component에 부탁을 한다.
//		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), _Value);
//	}
//}
