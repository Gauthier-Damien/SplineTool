#include "LineActor.h"


ALineActor::ALineActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	p0 = CreateDefaultSubobject<USceneComponent>("p0");
	p1 = CreateDefaultSubobject<USceneComponent>("p1");


	points.Add(p0);
	points.Add(p1);

#if WITH_EDITOR
	PrimaryActorTick.bStartWithTickEnabled = true;
#endif

}

void ALineActor::BeginPlay()
{
	Super::BeginPlay();

}

void ALineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawVisualDebug();

}

bool ALineActor::ShouldTickIfViewportsOnly() const
{
	return bShouldDrawDebug;
}

void ALineActor::DrawVisualDebug()
{

	for (size_t i = 0; i < points.Num(); i++)
	{

		DrawDebugBox(GetWorld(), points[i]->GetRelativeLocation(), FVector(10), FColor::Green);
		DrawDebugLine(GetWorld(), points[i]->GetRelativeLocation(), points[i]->GetRelativeLocation() + (points[i]->GetUpVector() * debugOffset), FColor::Blue);
		DrawDebugSphere(GetWorld(), points[i]->GetRelativeLocation() + (points[i]->GetUpVector() * debugOffset), 10, 5, FColor::Blue);
		if(i > 0 && points[i ])
		DrawDebugLine(GetWorld(), points[i - 1]->GetRelativeLocation(), points[i]->GetRelativeLocation(), FColor::Red);

	}



	

	
}

void ALineActor::AddPoint()
{

	
	points.Add(NewObject<USceneComponent>(this));
	index++;
}

void ALineActor::RemovePoint()
{

	if (index <= 2) return;
	index--;
	USceneComponent* _temp = points[index];
	points.Remove(_temp);
	_temp->DestroyComponent();

}

