// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCoin.h"
#include "BasePlayer.h"

// Sets default values
ABaseCoin::ABaseCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>("CoinMesh");
	CoinMesh->SetupAttachment(Root);
	CoinMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RotationRate = 100;

	OnActorBeginOverlap.AddDynamic(this, &ABaseCoin::OnOverlap);
}

// Called when the game starts or when spawned
void ABaseCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCoin::Tick(float DeltaTime)
{
	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

void ABaseCoin::DeathTimerComplete()
{
	Destroy();
}

void ABaseCoin::PlayCustomDeath()
{
	ABasePlayer* Player = Cast<ABasePlayer>(GetClass());
	Player->CoinCollected(1);

	RotationRate = 1500;
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ABaseCoin::DeathTimerComplete, 0.5f, false);
}

void ABaseCoin::OnOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor) {

	if (Cast<ABasePlayer>(OtherActor) != nullptr) {

		Destroy();

	}
}