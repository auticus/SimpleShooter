// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Weapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//hide the existing weapon baked in to the model
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); //EPhysBodyOp not used anywhere but you have to put a value in

	// Spawn the selected weapon from blueprint into character's hands
	Weapon = GetWorld()->SpawnActor<AWeapon>(GunClass); //spawn the weapon class that will be set in the blueprint.
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// resharper tip - if the TEXT bindings say they aren't found you have to go into Unreal >> Tools >> Refresh Visual Studio Project
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &APlayerCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &APlayerCharacter::LookUpDown);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &APlayerCharacter::LookSide);
	PlayerInputComponent->BindAxis(TEXT("LookUpDownWithDelta"), this, &APlayerCharacter::LookUpDownWithDelta);
	PlayerInputComponent->BindAxis(TEXT("LookSideWithDelta"), this, &APlayerCharacter::LookSideWithDelta);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveSide(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUpDown(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::LookSide(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::LookUpDownWithDelta(float AxisValue)
{
	// the with Delta functions add delta time - which lets the gamepad get off of frame rate dependence.
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookSideWithDelta(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}
