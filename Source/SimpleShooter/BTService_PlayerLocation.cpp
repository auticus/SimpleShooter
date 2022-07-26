// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "Update Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// dev notes: this was originally in AIController cpp file and required line of sight
	// this should be called on the BT under a node that has determined it can see the player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //index 0 is the player in this game

	//GetSelectedBlackboardKey() is important because in the BT this will be set as the key that this service will be affecting.
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}