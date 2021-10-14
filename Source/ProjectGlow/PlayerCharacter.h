// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/InteractInterface.h"


#include "PlayerCharacter.generated.h"


UCLASS()
class PROJECTGLOW_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Camera Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	// Movement Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float JumpGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float FallGravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		int WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		int SprintSpeed;

	// Other Properties
	bool bDead;

	// Movement Methods
	void MoveFoward(float Axis);
	void MoveRight(float Axis);
	void Sprint();
	void StopSprinting();

	// Interact Interface Functions and Properties
	void Interact();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	float TraceDistance;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
