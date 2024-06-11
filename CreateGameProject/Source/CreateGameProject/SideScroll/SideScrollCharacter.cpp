// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScroll/SideScrollCharacter.h"
#include "GameFramework/SpringArmComponent.h" // 스프링 암.
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerInput.h"
#include "Global/GlobalGameInstance.h"
#include "CreateGameProject.h"
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
	SpringArmComponent->bDoCollisionTest = false;
	//SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	FQuat Rot = UKismetMathLibrary::Quat_MakeFromEuler(FVector(0.0f, 0.0f, -90.0f));
	SpringArmComponent->SetRelativeRotation(Rot);
}

// Called when the game starts or when spawned
void ASideScrollCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 한 번만.
	GainCollisionPtr = FindComponentByTag<UCapsuleComponent>(TEXT("Gain"));
	if (nullptr == GainCollisionPtr)
	{
		UE_LOG(MyGameLog, Fatal, TEXT("%S(%u)> if (nullptr == Cap)"), __FUNCTION__, __LINE__);
	}

	UGlobalGameInstance* inst = GetWorld()->GetGameInstanceChecked<UGlobalGameInstance>();
	SideScrollData = inst->GetSideScrollData();

	PlayerData = SideScrollData->PlayerData;
}

// Called every frame
void ASideScrollCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(1.0f, 0.0f, 0.0f) * DeltaTime * PlayerData.PlayerSpeed);

	if (true == IsGroundValue)
	{
		Gravity(DeltaTime);
	}
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

void ASideScrollCharacter::Gravity(float _DeltaTime)
{
	GravityPower += PlayerData.GravityAccSpeed * _DeltaTime;
	GetMesh()->AddRelativeLocation(FVector(0.0f, 0.0f, GravityPower) * _DeltaTime);
	GainCollisionPtr->AddRelativeLocation(FVector(0.0f, 0.0f, GravityPower) * _DeltaTime);
}

void ASideScrollCharacter::SetViewChracterPos(FVector _Pos)
{
	GetMesh()->SetRelativeLocation(_Pos);
	_Pos.Z += GainCollisionPtr->GetScaledCapsuleHalfHeight();
	GainCollisionPtr->SetRelativeLocation(_Pos);
}

void ASideScrollCharacter::FrontMove(float _DeltaTime)
{
	GetMesh()->AddRelativeLocation(FVector(1.0f, 0.0f, 0.0f) * _DeltaTime * PlayerData.ViewChracterSpeed);
	FVector MeshPos = GetMesh()->GetRelativeLocation();
	if (PlayerData.FrontMax <= MeshPos.X)
	{
		MeshPos.X = PlayerData.FrontMax;
		GetMesh()->SetRelativeLocation(MeshPos);
	}
	
	SetViewChracterPos(MeshPos);
}

void ASideScrollCharacter::BackMove(float _DeltaTime)
{
	GetMesh()->AddRelativeLocation(FVector(-1.0f, 0.0f, 0.0f) * _DeltaTime * PlayerData.ViewChracterSpeed);
	FVector MeshPos = GetMesh()->GetRelativeLocation();
	if (PlayerData.BackMax >= MeshPos.X)
	{
		MeshPos.X = PlayerData.BackMax;
		GetMesh()->SetRelativeLocation(MeshPos);
	}

	SetViewChracterPos(MeshPos);
}

void ASideScrollCharacter::ViewJumpBegin(float _DeltaTime)
{
	//ACharacter::JumpMaxCount = 2;
	//ACharacter::Jump();
}

void ASideScrollCharacter::ViewJumpGravity(float _DeltaTime)
{
	if (true == IsGroundValue)
	{

	}

	GravityPower += PlayerData.GravityAccSpeed * _DeltaTime;
	GetMesh()->AddRelativeLocation(FVector(0.0f, 0.0f, GravityPower) * _DeltaTime);
	GainCollisionPtr->AddRelativeLocation(FVector(0.0f, 0.0f, GravityPower) * _DeltaTime);
}

void ASideScrollCharacter::PlayerCollision(AActor* _CollisionActor)
{
	if (true == _CollisionActor->ActorHasTag(TEXT("Coin")))
	{
		_CollisionActor->Destroy();
	}

	if (true == _CollisionActor->ActorHasTag(TEXT("Ground")))
	{
		FVector MeshPos = GetMesh()->GetRelativeLocation();
		MeshPos.Z = 0.0f; // 언덕이 없는 게임이라 가정한다.
		SetViewChracterPos(MeshPos);
		IsGroundValue = true;
	}
}

void ASideScrollCharacter::PlayerCollisionEnd(AActor* _CollisionActor)
{
	if (true == _CollisionActor->ActorHasTag(TEXT("Ground")))
	{
		IsGroundValue = false;
	}
}

//void ASideScrollCharacter::SpeedChange(float _Value)
//{
//	if (_Value != 0)
//	{
//		// 내가 만약 MoveComponent를 가지고 있다면 그 Component에 부탁을 한다.
//		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), _Value);
//	}
//}
