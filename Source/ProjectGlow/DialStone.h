// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "Components/TextRenderComponent.h"
#include "DialStone.generated.h"

UCLASS()
class PROJECTGLOW_API ADialStone : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialStone();

	// Dial Value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DialValues)
		int CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DialValues)
		int CorrectValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DialValues)
		FString DialName;

	// Text Render
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TextRender)
		UTextRenderComponent* TextComponent;

	// Real Time Properties
	bool bSet;

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
