// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT420_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	virtual void OnConstruction(const FTransform &transform) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateFront();

	void CreateLeft();

	void CreateRight();

	void CreateBack();

	void CreateRoof();

	void CreatePillar(const float z, const FTransform &transform);

	// A number for the name prefix e.g BuildingBlock_"1"
	int32 PrefixCount;

	FName InitialName;

	FVector TempPosition;
	FRotator TempRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateMesh(class UStaticMesh* staticMesh, const FTransform &transform);
	
	/*------ Static Meshes-------- */
	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* Mesh;	

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* Wall;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* Door;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* DoorFiller;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* Window;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* UpperWindow;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* Roof;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* PillarBase;

	UPROPERTY(EditAnywhere, Category = "Building Parts")
	class UStaticMesh* UpperPillar;

	/*----------------------------------------*/

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Root;
	
	// Array that stores the created building parts
	TArray<UStaticMeshComponent*> SMArray;

	// The distance between modular parts in X direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	float XOffset;

	// The distance between modular parts in Y direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	float YOffset;

	// The distance between modular parts in Z direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	float ZOffset;

	// The offset position for pillar/edge object in X direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	float PillarOffsetX;

	// The offset position for pillar/edge object in Y direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	float PillarOffsetY;

	// The offset distance from origin of this actor  
	UPROPERTY(EditAnywhere, Category = "Construction")
	float XDistanceFromOrigin;	

	// Total floor count 
	UPROPERTY(EditAnywhere, Category = "Construction")
	int32 FloorCount;
	
	// Total face count to spawn in X direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	int32 XNumToSpawn;

	// Total face count to spawn in Y direction
	UPROPERTY(EditAnywhere, Category = "Construction")
	int32 YNumToSpawn;

	// The position of the door object
	UPROPERTY(EditAnywhere, Category = "Construction")
	int32 DoorPosition;	

};
