// Fill out your copyright notice in the Description page of Project Settings.


#include "DialStone.h"
#include "Kismet/GameplayStatics.h"
#include "MultiSwitch.h"

// Sets default values
AMultiSwitch::AMultiSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Multi Switch Name
	SwitchName = "Default Name";

	// Add Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	MaterialActive = CreateDefaultSubobject<UMaterial>(TEXT("Active Material"));
	MaterialInactive = CreateDefaultSubobject<UMaterial>(TEXT("Inactive Material"));
	MeshComponent->SetMaterial(0, MaterialInactive);


	bOpen = false;

}

// Called when the game starts or when spawned
void AMultiSwitch::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->SetMaterial(0, MaterialInactive);
	
}

// Called every frame
void AMultiSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMultiSwitch::Interact_Implementation()
{

	CheckDials();


}

void AMultiSwitch::InteractPure()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Pure"));
}


void AMultiSwitch::CheckDials() {

	// Find all DialStone actors
	TSubclassOf<ADialStone> classToFind;
	classToFind = ADialStone::StaticClass();
	TArray<AActor*> foundDialStones;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundDialStones);

	// Assume all dials are set.
	bOpen = true;

	for (auto& Dial : foundDialStones) {

		// If a single dial is unset, break.
		if ((Cast <ADialStone>(Dial)->bSet == false) && (Cast <ADialStone>(Dial)->DialName == SwitchName)) {
			bOpen = false;
			break;
		}
	}

	// Check if the switch can open
	if (bOpen) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("All Dials Set!"));
		MeshComponent->SetMaterial(0, MaterialActive);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Failed!"));
		MeshComponent->SetMaterial(0, MaterialInactive);
	}
}