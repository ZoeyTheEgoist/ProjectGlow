// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Set half height and radius of capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Forbids character to rotate
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Allow the camera to rotate
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	// Attach Camera Boom to Player
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	//Add Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; //camera doesn't rotate relative to the arm

	// Initial Properties
	bDead = false;

	// Character Jumping Stats & Gravity
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
	JumpGravity = 2;
	FallGravity = 4;

	// Character Speeds
	WalkSpeed = 400;
	SprintSpeed = 650;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if player is falling
	if ((GetCharacterMovement()->IsFalling() == true) && (GetVelocity().Z <= 0) && (GetCharacterMovement()->GravityScale != FallGravity)) {
		// Raise the gravity
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Falling!"));
		GetCharacterMovement()->GravityScale = FallGravity;
	}
	else if (GetCharacterMovement()->GravityScale != JumpGravity) {
		// Reset gravity when on ground
		GetCharacterMovement()->GravityScale = JumpGravity;
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Look around
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Move around
	PlayerInputComponent->BindAxis("MoveFoward", this, &APlayerCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprinting);
}



void APlayerCharacter::MoveFoward(float Axis)
{
	if (!bDead) {
		// Move relative to the direction you're facing
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::MoveRight(float Axis)
{
	if (!bDead) {
		// Move relative to the direction you're facing
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::Sprint()
{
	if (!bDead) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sprinting"));
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void APlayerCharacter::StopSprinting()
{
	if (!bDead) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Stopped Sprinting"));
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

