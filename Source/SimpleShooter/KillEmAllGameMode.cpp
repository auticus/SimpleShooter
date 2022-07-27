// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* Pawn)
{
	Super::PawnKilled(Pawn);
	UE_LOG(LogTemp, Warning, TEXT("A Pawn called %s has been killed"), *Pawn->GetName());

	// now get the controller for that pawn and fire off its GameHasEnded method.  If its the Player, we have a special player controller that will end the game
	APlayerController* playerController = Cast<APlayerController>(Pawn->GetController());
	if (playerController == nullptr) return;

	playerController->GameHasEnded(nullptr, false);
	// null ptr is for where focus should go to now that the player has died, in this case no one
	// bIsWinner says that this player death definitely didn't trigger a win condition
}