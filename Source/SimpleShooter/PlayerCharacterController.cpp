// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "TimerManager.h"

void APlayerCharacterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Player has died!!"));

	//when player dies, let it sit for however long the delay property is and then restart the level with existing UE RestartLevel function
	//warning - if you restart your level and you are not playing in STANDALONE GAME mode you will get
	//TravelFailure: ClientTravelFailure, Reason for Failure 'Failed to Load Package ' something something UEDPIE_0_SandBox - Shutting down PIE
	//PIE means Play in Editor

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
