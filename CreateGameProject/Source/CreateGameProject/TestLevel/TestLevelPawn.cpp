// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/TestLevelPawn.h"
#include "GameFramework/PlayerInput.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

FName ATestLevelPawn::MovementComponentName(TEXT("MovementComponent0"));
FName ATestLevelPawn::CollisionComponentName(TEXT("CollisionComponent0"));
FName ATestLevelPawn::MeshComponentName(TEXT("MeshComponent0"));

// Sets default values
ATestLevelPawn::ATestLevelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetCanBeDamaged(true);

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	NetPriority = 3.0f;

	BaseEyeHeight = 0.0f;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(ATestLevelPawn::CollisionComponentName);
	CollisionComponent->InitSphereRadius(35.0f);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;

	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(ATestLevelPawn::MovementComponentName);
	MovementComponent->UpdatedComponent = CollisionComponent;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh;
		FConstructorStatics()
			: SphereMesh(TEXT("/Engine/EngineMeshes/Sphere")) {}
	};

	static FConstructorStatics ConstructorStatics;

	MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(ATestLevelPawn::MeshComponentName);
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(ConstructorStatics.SphereMesh.Object);
		MeshComponent->AlwaysLoadOnClient = true;
		MeshComponent->AlwaysLoadOnServer = true;
		MeshComponent->bOwnerNoSee = true;
		MeshComponent->bCastDynamicShadow = true;
		MeshComponent->bAffectDynamicIndirectLighting = false;
		MeshComponent->bAffectDistanceFieldLighting = false;
		MeshComponent->bVisibleInRayTracing = false;
		MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		const float Scale = CollisionComponent->GetUnscaledSphereRadius() / 160.f; // @TODO: hardcoding known size of EngineMeshes.Sphere. Should use a unit sphere instead.
		MeshComponent->SetRelativeScale3D(FVector(Scale));
		MeshComponent->SetGenerateOverlapEvents(false);
		MeshComponent->SetCanEverAffectNavigation(false);
	}

	// This is the default pawn class, we want to have it be able to move out of the box.
	bAddDefaultMovementBindings = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
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

	check(PlayerInputComponent);

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::W, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::S, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::A, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::D, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_Turn", EKeys::MouseX, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUpRate", EKeys::Gamepad_RightY, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUp", EKeys::MouseY, -1.f));


	PlayerInputComponent->BindAxis("DefaultPawn_MoveForward", this, &ATestLevelPawn::MoveForward);
	PlayerInputComponent->BindAxis("DefaultPawn_MoveRight", this, &ATestLevelPawn::MoveRight);
	PlayerInputComponent->BindAxis("DefaultPawn_MoveUp", this, &ATestLevelPawn::MoveUp_World);
	PlayerInputComponent->BindAxis("DefaultPawn_Turn", this, &ATestLevelPawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("DefaultPawn_TurnRate", this, &ATestLevelPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("DefaultPawn_LookUp", this, &ATestLevelPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("DefaultPawn_LookUpRate", this, &ATestLevelPawn::LookUpAtRate);
}

void ATestLevelPawn::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
		}
	}
}

void ATestLevelPawn::MoveForward(float Val)
{


	//if (Val != 0.f)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Forward"));

	//	// 초당 60 프레임 제한이 걸려있어서 
	//	// 텔타타임을 곱해줘야 한다.
	//	SetActorLocation(GetActorLocation() + FVector(1.0f, 0.0f, 0.0f));
	//}

	if (Val != 0.f)
	{
		FRotator const ControlSpaceRot = Controller->GetControlRotation();
		AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
	}
}

void ATestLevelPawn::MoveUp_World(float Val)
{
	if (Val != 0.f)
	{
		AddMovementInput(FVector::UpVector, Val);
	}
}

void ATestLevelPawn::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ATestLevelPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}
