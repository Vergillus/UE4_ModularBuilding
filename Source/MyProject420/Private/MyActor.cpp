// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a root object
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = Root;
	
	/*--- Default Initialization--- */
	DoorPosition = 1;

	XNumToSpawn = 1;
	YNumToSpawn = 1;

	//InitialName = FName("BuildingBlock");

	TempPosition = FVector::ZeroVector;
	TempRotation = FRotator::ZeroRotator;

	/*-----------------------------------*/
}

// This function is essential to create and manage Modular Building inside the editor. Code presentation of blueprint ConstructionScript
void AMyActor::OnConstruction(const FTransform & transform)
{
	// Do NOT update the mesh if the this actor is moving or rotating.
	if (transform.GetLocation() != TempPosition || transform.GetRotation().Rotator() != TempRotation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Transform Position: %s"), *transform.GetLocation().ToString());				
	}
	else
	{
		// Empty the array everytime a change happens
		for (auto It = SMArray.CreateIterator(); It; It++)
		{
			(*It)->DestroyComponent();
		}

		SMArray.Empty();
		PrefixCount = 0;

		// This is required to render and create the mesh parts
		RegisterAllComponents();

		/* Functions for creating the building*/
		CreateFront();		
		CreateLeft();
		CreateRight();
		CreateBack();
		CreateRoof();
		/*------------------------------------*/
	}	

	TempPosition = transform.GetLocation();
	TempRotation = transform.GetRotation().Rotator();
	
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Create a mesh from provided static mesh and transform
void AMyActor::CreateMesh(UStaticMesh* staticMesh, const FTransform &transform)
{
	
	FString Str = "BuildingBlock" + FString::FromInt(PrefixCount++);

	UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this, InitialName);

	SMArray.Add(MeshComp);

	InitialName = (*Str);

	if (MeshComp)
	{
		// This is also required to create a mesh.
		MeshComp->RegisterComponent();		

		MeshComp->SetStaticMesh(staticMesh);
		MeshComp->Mobility = EComponentMobility::Movable;		

		MeshComp->SetRelativeTransform(transform);

		MeshComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		
	}	
	
}

// Create the front side of the building in X direction
void AMyActor::CreateFront()
{	
	UStaticMesh* TempMesh;

	FTransform PillarTransform;

	// Transform and Location of the face meshes.
	FTransform Transform;
	FVector Location;

	for (int32 z = 0; z < FloorCount; z++)
	{	
		
		for (int32 x = 0; x < XNumToSpawn; x++)
		{
			if (Window && Door && UpperWindow && DoorFiller)
			{
				Location.X = x * XOffset + XDistanceFromOrigin;
				Location.Z = z * ZOffset;

				Transform.SetLocation(Location);

				if (z == 0)
				{
					if ((x + 1) == DoorPosition)
					{
						TempMesh = Door;
					}
					else
					{
						TempMesh = DoorFiller;
					}					
				}				
				else if(z == FloorCount - 1)
				{
					TempMesh = UpperWindow;
				}
				else
				{
					TempMesh = Window;
				}

				CreateMesh(TempMesh, Transform);
			}
		}		

		// Create the pillar or edge of the building in X direction
		PillarTransform.SetLocation(FVector(-PillarOffsetX, 0., z * ZOffset));
		CreatePillar(z, PillarTransform);
	}
}

// Create the left side of the building in Y direction.
void AMyActor::CreateLeft()
{
	UStaticMesh* TempMesh;

	FTransform PillarTransform;

	// This is for rotating the face meshes so that they can align with the front faces.
	FRotator NewRotation = FRotator(0.0f,90.0f,0.0f);

	for (int32 z = 0; z < FloorCount; z++)
	{

		for (int32 y = 0; y < YNumToSpawn; y++)
		{
			if (Window && UpperWindow && DoorFiller)
			{

				FTransform Transform;
				FVector Location;

				Location.X = -PillarOffsetX;
				Location.Y = (y * XOffset + YOffset ) * -1;
				Location.Z = z * ZOffset;

				Transform.SetLocation(Location);
				Transform.SetRotation(NewRotation.Quaternion());
				if (z == 0)
				{
					TempMesh = DoorFiller;					
				}
				else if (z == FloorCount - 1)
				{
					TempMesh = UpperWindow;
				}
				else
				{
					TempMesh = Window;
				}
				
				
				CreateMesh(TempMesh, Transform);

			}
		}

		// Create the pillar or edge of the building in Y direction
		PillarTransform.SetLocation(FVector(XNumToSpawn * XOffset + PillarOffsetX, 0.0f , z * ZOffset));
		PillarTransform.SetRotation(FRotator(0.0, 270.f, 0.0f).Quaternion());
		CreatePillar(z, PillarTransform);
	}
}

// Create the right side of the building in Y direction
void AMyActor::CreateRight()
{
	UStaticMesh* TempMesh;

	FTransform PillarTransform;

	// This is for rotating the face meshes so that they can align with the front faces.
	FRotator NewRotation = FRotator(0.0f, -90.0f, 0.0f);

	for (int32 z = 0; z < FloorCount; z++)
	{

		for (int32 y = 0; y < YNumToSpawn; y++)
		{
			if (Window && UpperWindow && DoorFiller)
			{

				FTransform Transform;
				FVector Location;

				Location.X = XNumToSpawn * XOffset + PillarOffsetX;
				Location.Y = (y * XOffset + XDistanceFromOrigin + YOffset) * -1;
				Location.Z = z * ZOffset;

				Transform.SetLocation(Location);
				Transform.SetRotation(NewRotation.Quaternion());
				if (z == 0)
				{
					TempMesh = DoorFiller;
				}
				else if (z == FloorCount - 1)
				{
					TempMesh = UpperWindow;
				}
				else
				{
					TempMesh = Window;
				}

				CreateMesh(TempMesh, Transform);
			}
		}

		// Create the pillar or edge of the building in Y direction
		PillarTransform.SetLocation(FVector(-PillarOffsetX, -YNumToSpawn * XOffset - PillarOffsetY, z * ZOffset));
		PillarTransform.SetRotation(FRotator(0.0,90.f,0.0f).Quaternion());
		CreatePillar(z, PillarTransform);
	}
}

// Create the backside of the building in X direction
void AMyActor::CreateBack()
{
	UStaticMesh* TempMesh;

	FTransform PillarTransform;

	// This is for rotating the face meshes so that they can align with the front faces.
	FRotator NewRotation = FRotator(0.0f, 180.0f, 0.0f);

	for (int32 z = 0; z < FloorCount; z++)
	{

		for (int32 x = 0; x < XNumToSpawn; x++)
		{
			if (Window && UpperWindow && DoorFiller)
			{

				FTransform Transform;
				FVector Location;

				Location.X = (x * XOffset);
				Location.Y = (YNumToSpawn * XOffset + PillarOffsetY) *  -1.0f  ;
				Location.Z = z * ZOffset;

				Transform.SetLocation(Location);
				Transform.SetRotation(NewRotation.Quaternion());
				if (z == 0)
				{
					TempMesh = DoorFiller;
				}
				else if (z == FloorCount - 1)
				{
					TempMesh = UpperWindow;
				}
				else
				{
					TempMesh = Window;
				}


				CreateMesh(TempMesh, Transform);

			}
		}

		// Create the pillar or edge of the building in X direction
		PillarTransform.SetLocation(FVector(XNumToSpawn * XOffset + PillarOffsetX, -YNumToSpawn * XOffset - PillarOffsetY, z * ZOffset));
		PillarTransform.SetRotation(FRotator(0.0, 180.f, 0.0f).Quaternion());
		CreatePillar(z, PillarTransform);
	}
}

// Create the roof 
void AMyActor::CreateRoof()
{
	FRotator NewRotation = FRotator(0.0f, 0.0f, -90.0f);
	
	// Becuse pillars/edges creates extra space add 1 to X/YNumToSpawn for creating a proper roof
	for (int32 y = 0; y < YNumToSpawn + 1; y++)
	{
		for (int32 x = 0; x < XNumToSpawn + 1; x++)
		{
			if (Roof)
			{
				FTransform Transform;
				FVector Location;

				//Location.X = (x * XOffset + XDistanceFromOrigin);
				Location.X = (x * XOffset + PillarOffsetX);
				Location.Y = y *  XOffset * -1;
				Location.Z = FloorCount * ZOffset;

				Transform.SetLocation(Location);
				Transform.SetRotation(NewRotation.Quaternion());
				
				CreateMesh(Roof, Transform);

			}
		}

	}
}

// Create the pillar mesh 
void AMyActor::CreatePillar(const float z, const FTransform &transform)
{	

	UStaticMesh * TempMesh;

	if (PillarBase && UpperPillar)
	{
		if (z == FloorCount - 1)
		{
			TempMesh = UpperPillar;
		}
		else
		{
			TempMesh = PillarBase;
		}

		CreateMesh(TempMesh, transform);
	}
}



