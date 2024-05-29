// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevelPawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/FloatingPawnMovement.h"

FName ATestLevelPawn::MovementComponentName(TEXT("MovementComponent0"));
FName ATestLevelPawn::CollisionComponentName(TEXT("CollisionComponent0"));
FName ATestLevelPawn::MeshComponentName(TEXT("MeshComponent0"));

// Sets default values
ATestLevelPawn::ATestLevelPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetCanBeDamaged(true);
	PrimaryActorTick.bCanEverTick = true;

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

UPawnMovementComponent* ATestLevelPawn::GetMovementComponent() const
{
	return MovementComponent;
}


void InitializeDefaultPawnInputBindings()
{
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveRight", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_Turn", EKeys::MouseX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_LookUp", EKeys::MouseY, -1.f));
	}
}

// Called to bind functionality to input
void ATestLevelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	if (bAddDefaultMovementBindings)
	{
		InitializeDefaultPawnInputBindings();

		// PlayerInputComponent 입력을 체크하는 기능과 인터페이스를 제공하는 녀석

		// 언리얼의 기초 입력 정의 방식
		PlayerInputComponent->BindAxis("DefaultPawn_MoveForward", this, &ATestLevelPawn::MoveForward);
		PlayerInputComponent->BindAxis("DefaultPawn_MoveRight", this, &ATestLevelPawn::MoveRight);
		PlayerInputComponent->BindAxis("DefaultPawn_MoveUp", this, &ATestLevelPawn::MoveUp_World);
		PlayerInputComponent->BindAxis("DefaultPawn_Turn", this, &ATestLevelPawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("DefaultPawn_TurnRate", this, &ATestLevelPawn::TurnAtRate);
		PlayerInputComponent->BindAxis("DefaultPawn_LookUp", this, &ATestLevelPawn::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("DefaultPawn_LookUpRate", this, &ATestLevelPawn::LookUpAtRate);
	}
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
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
		}
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
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ATestLevelPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ATestLevelPawn::MoveF()
{
	AddActorLocalOffset(FVector(1.0f, 0.0f, 0.0f));
}


void ATestLevelPawn::UpdateNavigationRelevance()
{
	if (CollisionComponent)
	{
		CollisionComponent->SetCanEverAffectNavigation(bCanAffectNavigationGeneration);
	}
}
