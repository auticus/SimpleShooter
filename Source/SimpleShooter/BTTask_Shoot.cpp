// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "PlayerCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	// Set this to call Tick() every frame.  This is required for this node that ticks otherwise set to false
	bNotifyTick = false;

	NodeName = "Shoot Player";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// the PlayerCharacter object has a Shoot Method
	// we can get a hold of the AI Controller and from that we can get the pawn.
	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	APlayerCharacter* pawn = Cast<APlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (pawn == nullptr) return EBTNodeResult::Failed;
	pawn->FireWeapon();
	return EBTNodeResult::Succeeded;
}