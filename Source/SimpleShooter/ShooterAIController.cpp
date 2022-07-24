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
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the AI to set its movement priorities
	// If I can see the player, then I want to set my focus to them and try to move toward them
	// otherwise (right now) I will stop moving and lose my focus

	if (LineOfSightTo(PlayerPawn))
	{
		SetFocus(PlayerPawn);  // priority defaults to Gameplay anyway so use default
		MoveToActor(PlayerPawn, AIMinimumDistanceFromPlayer);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay); //gameplay was the default we set
		StopMovement();
	}
	
}