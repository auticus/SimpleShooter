// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUpDown(float AxisValue);
	void LookSide(float AxisValue);
	void LookUpDownWithDelta(float AxisValue);
	void LookSideWithDelta(float AxisValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 50; //used to help multiply rotation time for gamepad input
};
