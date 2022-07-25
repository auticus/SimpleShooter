// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
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

	if (AIBehavior == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Behavior was not set for the AI Controller!"));
		return;
	}

	RunBehaviorTree(AIBehavior);  //VERY IMPORTANT THAT THIS RUNS FIRST - this is what sets the BT up and without this the blackboard comes back null below
	SetupBlackboard();
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the AI to set its movement priorities
	// If I can see the player, then I want to set my focus to them and try to move toward them
	// otherwise (right now) I will stop moving and lose my focus

	/* Commented out for the purposes of seeing how to do this without a behavior tree
	if (LineOfSightTo(PlayerPawn))
	{
		SetFocus(PlayerPawn);  // priority defaults to Gameplay anyway so use default
		MoveToActor(PlayerPawn, AIMinimumDistanceFromPlayer); //this does set a focus but a lower priority focus
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay); //gameplay was the default we set
		StopMovement();
	}
	*/

	// the blackboard component has a PlayerLocation vector - we need to set it here
	// the demo lecture has this going in beginplay but I think we need to set player location in a behavior tree constantly ...
	UBlackboardComponent* controllerBlackboard = GetBlackboardComponent();
	if (controllerBlackboard == nullptr) return;

	controllerBlackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
}

void AShooterAIController::SetupBlackboard()
{
	AIBlackboard = GetBlackboardComponent();
	if (AIBlackboard == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Blackboard Component was not set on the Behavior Tree, or Behavior Tree was not set for the AI Controller"));
		return;
	}

	// set initial black board variables
	APawn* aiPawn = GetPawn();
	UE_LOG(LogTemp, Warning, TEXT("Preparing to set AIPawn"));
	if (aiPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AI PAWN WAS NOT FOUND"));
		return;
	}

	FVector startLocation = aiPawn->GetActorLocation();
	FVector endLocation = PlayerPawn->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Start Location = %s"), *startLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("End Locatio = %s"), *endLocation.ToString());
	AIBlackboard->SetValueAsVector(TEXT("PatrolStart"), startLocation);
	AIBlackboard->SetValueAsVector(TEXT("PatrolEnd"), endLocation);
}
