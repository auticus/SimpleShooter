// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* Pawn)
{
	Super::PawnKilled(Pawn);
	UE_LOG(LogTemp, Warning, TEXT("A Pawn called %s has been killed"), *Pawn->GetName());

	// now get the controller for that pawn and fire off its GameHasEnded method.  If its the Player, we have a special player controller that will end the game
	// AI player when it dies, this comes back null (when logging out this showed to be the case, so its AI Controller is not being returned)
	// AAIController comes off of AController as does APlayerController - but only a player will have APlayerController
	APlayerController* playerController = Cast<APlayerController>(Pawn->GetController());
	if (playerController == nullptr)
	{
		// this was an AI controller, determine if all of them are dead.  If yes then end the game and player has won
		for (AShooterAIController* controller : TActorRange<AShooterAIController>(GetWorld()))
		{
			if (!controller->IsDead()) return;
		}

		EndGame(true);
	}
	else
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// let everyone in the game know that the game is over and if they won or not
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		//remember that player controllers and AI controllers are both AControllers
		bool controllerOwnerHasWon = Controller->IsPlayerController() == bIsPlayerWinner;

		// set the focus to the dead pawn instead of nullptr.  In multiplayer games maybe you want to set focus to the player that pwned you.
		Controller->GameHasEnded(Controller->GetPawn(), controllerOwnerHasWon);
	}
}