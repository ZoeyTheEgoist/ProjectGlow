// Fill out your copyright notice in the Description page of Project Settings.


#include <string>
#include "DialStone.h"

// Sets default values
ADialStone::ADialStone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Default Values
	CurrentValue = 1;
	CorrectValue = 5;

	// Add Text Renderer
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Renderer"));
	TextComponent->SetupAttachment(RootComponent);
	TextComponent->SetTextRenderColor(FColor::FromHex("000000FF"));
	TextComponent->K2_SetText(FText::FromString(FString::FromInt(CurrentValue)));

	bSet = false;
}

// Called when the game starts or when spawned
void ADialStone::BeginPlay()
{
	Super::BeginPlay();

	// Make sure correct number and color is shown when spawned
	TextComponent->SetTextRenderColor(FColor::FromHex("000000FF"));
	TextComponent->K2_SetText(FText::FromString(FString::FromInt(CurrentValue)));

	if (CurrentValue == CorrectValue) {
		bSet = true;
	}

}

// Called every frame
void ADialStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialStone::Interact_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Implementation"));

	CurrentValue++;
	if (CurrentValue > 8) {
		CurrentValue = 1;
	}

	TextComponent->K2_SetText(FText::FromString(FString::FromInt(CurrentValue)));

	if (CurrentValue == CorrectValue) {
		TextComponent->SetTextRenderColor(FColor::FromHex("00D7D3FF"));
		bSet = true;
	}
	else {
		TextComponent->SetTextRenderColor(FColor::FromHex("000000FF"));
		bSet = false;
	}

}

void ADialStone::InteractPure()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Pure"));
}
