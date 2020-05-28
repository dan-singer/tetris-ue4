// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tetris/Tetris.h"
#include "Components/BoxComponent.h"
#include "TTetromino.generated.h"

UCLASS()
class TETRIS_API ATTetromino : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATTetromino();


	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BlockA;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BlockB;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BlockC;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BlockD;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Holder;

	FTimerHandle DescendTimer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Descend();

	UStaticMeshComponent* MakeBlock(FName Name);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Init();

};
