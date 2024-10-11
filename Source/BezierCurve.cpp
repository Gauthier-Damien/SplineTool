#include "BezierCurve.h"
#include "Bezier.h"

ABezierCurve::ABezierCurve()
{
	PrimaryActorTick.bCanEverTick = true;


	p0 = CreateDefaultSubobject<USceneComponent>("p0");
	p1 = CreateDefaultSubobject<USceneComponent>("p1");
	p2 = CreateDefaultSubobject<USceneComponent>("p2");

	RootComponent = p0;

	points.Add(p0);
	points.Add(p1);
	points.Add(p2);

#if WITH_EDITOR
	PrimaryActorTick.bStartWithTickEnabled = true;
#endif

}

void ABezierCurve::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABezierCurve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawVisualDebug();
}

bool ABezierCurve::ShouldTickIfViewportsOnly() const
{
	return bShouldDrawDebug;
}

void ABezierCurve::DrawVisualDebug()
{
	for (size_t i = 0; i < points.Num(); i++)
	{
		if (!points[i]) continue;
		DrawDebugBox(GetWorld(), points[i]->GetRelativeLocation(), FVector(10), FColor::Green);
		DrawDebugLine(GetWorld(), points[i]->GetRelativeLocation(), points[i]->GetRelativeLocation() + (points[i]->GetUpVector() * debugOffset), FColor::Blue);
		DrawDebugSphere(GetWorld(), points[i]->GetRelativeLocation() + (points[i]->GetUpVector() * debugOffset), 10, 5, FColor::Blue);
		if (i > 0 && points[i])
			DrawDebugLine(GetWorld(), points[i - 1]->GetRelativeLocation(), points[i]->GetRelativeLocation(), FColor::Red);
	}


	FVector _lineStart = GetPoint(0.f);

	for (float i = 1; i <= lineSteps; i++) 
	{

		FVector _lineEnd = GetPoint(i / lineSteps);
		DrawDebugLine(GetWorld(), _lineStart, _lineEnd, FColor::White);

		if(bShouldDrawVelocityLine)
			DrawDebugLine(GetWorld(), _lineStart, _lineEnd + GetVelocity(i/lineSteps), FColor::Green);
		_lineStart = _lineEnd;
	}


}

void ABezierCurve::AddPoint()
{
	points.Add(NewObject<USceneComponent>(this));
	index++;
}

void ABezierCurve::RemovePoint()
{
	if (index <= baseIndex) return;
	index--;
	USceneComponent* _temp = points[index];
	points.Remove(_temp);
	_temp->DestroyComponent();
}

void ABezierCurve::Reset()
{
	TArray<USceneComponent*> _temps = points;

	for (int i = index; i > baseIndex; i--)
	{
		points.Remove(_temps[i - 1]);
		_temps[i - 1]->DestroyComponent();
		index--;
	}


}


FVector ABezierCurve::GetPoint(const float& _time)
{
	return !points.IsEmpty() && points.Num() >= baseIndex ? Bezier::GetPoint(points[0]->GetRelativeLocation(), points[1]->GetRelativeLocation(), points[2]->GetRelativeLocation(), _time) : FVector();
}



FVector ABezierCurve::GetVelocity(const float& _time)
{
	return !points.IsEmpty() && points.Num() >= baseIndex ? Bezier::GetFirstDerivative(points[0]->GetRelativeLocation(), points[1]->GetRelativeLocation(), points[2]->GetRelativeLocation(), _time) : FVector();
}


