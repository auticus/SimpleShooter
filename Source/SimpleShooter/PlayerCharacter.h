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
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure) // pure blueprint has no exe nodes - states that this won't change state anywhere
	bool IsDead() const;

private:
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUpDown(float AxisValue);
	void LookSide(float AxisValue);
	void LookUpDownWithDelta(float AxisValue);
	void LookSideWithDelta(float AxisValue);
	void FireWeapon();

	UPROPERTY(EditAnywhere)
	float RotationRate = 50; //used to help multiply rotation time for gamepad input

	UPROPERTY(EditDefaultsOnly) // we don't want this editable at runtime and we don't want to give the impression this should be changed at runtime
	TSubclassOf<class AWeapon> GunClass;

	UPROPERTY()
	AWeapon* Weapon;

	UPROPERTY(EditAnywhere) // used in Begin Play - not editable during run-time
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health; // the current health of the character
};
