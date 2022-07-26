// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Weapon.h"
#include "Components/CapsuleComponent.h"

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

	Health = MaxHealth;
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
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerCharacter::FireWeapon);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// the const& parameter means you cannot change the parameter brought in - this is a readonly parameter
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageTaken;
	if (Health < 0) Health = 0;

	if (IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//alternate is to take that DamageTaken and say DamageTaken = FMath::Min(Health, DamageTaken); - I personally do not like how that reads
	return DamageTaken;
}

bool APlayerCharacter::IsDead() const
{
	return Health <= 0;
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

// ReSharper disable once CppMemberFunctionMayBeConst -> input bindings will not allow const function in its method signature
void APlayerCharacter::FireWeapon()
{
	if (Weapon == nullptr) return;
	Weapon->PullTrigger();
}
