// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshcomponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PullTrigger()
{
	// ignore the resharper warning - you cannot make this a const function - the input mapping function will fail
	//spawn our muzzle flash
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	FireBullet();
}

void AWeapon::FireBullet() const
{
	APawn* owner = Cast<APawn>(GetOwner()); //need this to be a pawn because we need this to get at the controller which pawns have
	if (owner == nullptr) return;
	AController* ownerController = owner->GetController();
	if (ownerController == nullptr) return;

	//get the player's view point via controller function passing in two output parms
	FVector location;
	FRotator rotation;
	ownerController->GetPlayerViewPoint(location, rotation);

	//get the end of the max range from the player view point
	FVector endPoint = location + rotation.Vector() * MaxRange;
	FHitResult hit;

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(hit, location, endPoint, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		DrawDebugPoint(GetWorld(), hit.Location, 20, FColor::Red, true);
	}
}