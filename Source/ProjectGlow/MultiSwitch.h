// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "MultiSwitch.generated.h"

UCLASS()
class PROJECTGLOW_API AMultiSwitch : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiSwitch();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SwitchName)
		FString SwitchName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Appearance)
		class UStaticMesh* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Appearance)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		class UMaterial* MaterialActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		class UMaterial* MaterialInactive;

	bool bOpen;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interaction Implementation
	void Interact_Implementation() override;
	virtual void InteractPure() override;
};
