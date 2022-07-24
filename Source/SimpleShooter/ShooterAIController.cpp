// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get a pointer to the player pawn and instruct this controller to set its focus on that
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //index 0 is the player in this game

	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Pawn was not found for AI to focus on!"));
		return;
	}

	SetFocus(PlayerPawn);  // priority defaults to Gameplay anyway so use default
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the AI to set its movement priorities
	MoveToActor(PlayerPawn, AIMinimumDistanceFromPlayer);
}