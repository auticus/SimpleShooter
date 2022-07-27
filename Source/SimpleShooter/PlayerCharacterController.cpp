// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void APlayerCharacterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Warning, TEXT("Player has died!!"));

	//when player dies, let it sit for however long the delay property is and then restart the level with existing UE RestartLevel function
	//warning - if you restart your level and you are not playing in STANDALONE GAME mode you will get
	//TravelFailure: ClientTravelFailure, Reason for Failure 'Failed to Load Package ' something something UEDPIE_0_SandBox - Shutting down PIE
	//PIE means Play in Editor
	UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
	if (LoseScreen != nullptr)
	{
		//display the you lose screen
		//this will require "UMG" to be added to the Build.cs class - otherwise you will get bizarre compile errors
		LoseScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
