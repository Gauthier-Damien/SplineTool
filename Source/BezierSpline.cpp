// Fill out your copyright notice in the Description page of Project Settings.


#include "BezierSpline.h"
#include "Bezier.h"

ABezierSpline::ABezierSpline()
{
	PrimaryActorTick.bCanEverTick = true;

	index = baseIndex;

	p0 = CreateDefaultSubobject<USceneComponent>("p0");
	p1 = CreateDefaultSubobject<USceneComponent>("p1");
	p2 = CreateDefaultSubobject<USceneComponent>("p2");
	p3 = CreateDefaultSubobject<USceneComponent>("p3");

	RootComponent = p0;

	points.Add(p0);
	points.Add(p1);
	points.Add(p2);
	points.Add(p3);

#if WITH_EDITOR
	PrimaryActorTick.bStartWithTickEnabled = true;
#endif

}

void ABezierSpline::BeginPlay()
{
	Super::BeginPlay();

}

void ABezierSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawVisualDebug();
}

bool ABezierSpline::ShouldTickIfViewportsOnly() const
{
	return bShouldDrawDebug;
}

void ABezierSpline::DrawVisualDebug()
{
	int _steps = 0;
	FVector _lineEnd = FVector::Zero();
	FVector _lineStart = FVector::Zero();
	DrawDefaultLines();


	_lineStart = GetPoint(0.f);

	for (int y = 1; y <= curveSteps; y++)
	{

		_lineEnd = GetPoint((float)y / (float)curveSteps);


		//LOG("%s", *_lineEnd.ToString());
		DrawDebugLine(GetWorld(), _lineStart, _lineEnd, FColor::White);
		if (bShouldDrawVelocityLine)
			DrawDebugLine(GetWorld(), _lineStart, _lineEnd + GetVelocity(y / curveSteps), FColor::Green);
		_lineStart = _lineEnd;

	}

	//for (int i = 1; i < points.Num(); i += 3) {
	//	_steps = curveSteps * CurveCount();
	//	for (float y = 1; y <= _steps; y++)
	//	{
	//		_lineEnd = GetPoint((float)y / (float)curveSteps);


	//		//LOG("%s", *_lineEnd.ToString());
	//		DrawDebugLine(GetWorld(), _lineStart, _lineEnd, FColor::White);
	//		if (bShouldDrawVelocityLine)
	//			DrawDebugLine(GetWorld(), _lineStart, _lineEnd + GetVelocity(y / curveSteps), FColor::Green);
	//		_lineStart = _lineEnd;

	//	}
	//}


}
void ABezierSpline::DrawDefaultLines()
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
}
void ABezierSpline::AddCurve()
{
	for (int i = 0; i < numOfCurvePoints; i++)
		AddPoint();
}
void ABezierSpline::AddPoint()
{
	points.Add(NewObject<USceneComponent>(this));
	index++;
}
void ABezierSpline::RemoveCurve()
{
	for (int i = 0; i < numOfCurvePoints; i++)
		RemovePoint();
}
void ABezierSpline::RemovePoint()
{
	if (index <= baseIndex) return;
	index--;
	USceneComponent* _temp = points[index];
	points.Remove(_temp);
	_temp->DestroyComponent();
}
void ABezierSpline::Reset()
{
	TArray<USceneComponent*> _temps = points;

	for (int i = index; i > baseIndex; i--)
	{
		points.Remove(_temps[i - 1]);
		_temps[i - 1]->DestroyComponent();
		index--;
	}
}
FVector ABezierSpline::GetDirection(const float& _time)
{

	FVector _temp = GetVelocity(_time);
	_temp.Normalize();
	return _temp;
}
FVector ABezierSpline::GetPoint(const float& _time)
{
	float t = _time;
	int i = 0;

	t >= 1.f ? [&]() {t = 1.f; i = points.Num() - baseIndex; }() : [&]() {t = FMath::Clamp(t, 0.f, 1.f) * CurveCount(); i = (int)t; t -= i; i *= 3; }();


	
	return !points.IsEmpty() && points.Num() >= baseIndex ? Bezier::GetPoint(points[i]->GetRelativeLocation(), points[i + 1]->GetRelativeLocation(), points[i + 2]->GetRelativeLocation(), points[i + 3]->GetRelativeLocation(), t) : FVector();

	//return !points.IsEmpty() && points.Num() >= baseIndex ? Bezier::GetPoint(points[0]->GetRelativeLocation(), points[1]->GetRelativeLocation(), points[2]->GetRelativeLocation(), points[3]->GetRelativeLocation(), _time) : FVector();
}
FVector ABezierSpline::GetVelocity(const float& _time)
{
	float t = _time;
	int i;

	t >= 1.f ? [&]() {t = 1.f; i = points.Num() - baseIndex; }() : [&]() {t = FMath::Clamp(t, 0.f, 1.f) * CurveCount(); i = (int)t; t -= i; i *= 3; }();

	return !points.IsEmpty() && points.Num() >= baseIndex ? Bezier::GetFirstDerivative(points[i]->GetRelativeLocation(), points[i + 1]->GetRelativeLocation(), points[i + 2]->GetRelativeLocation(), t) : FVector();
}

