// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get patrol points
	auto AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController)) { return EBTNodeResult::Failed; }

	auto PatrollingGuard = AIController->GetPawn();
	if (!ensure(PatrollingGuard)) { return EBTNodeResult::Failed; }

	auto PatrolRoute = PatrollingGuard->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if ((PatrolPoints.Num() == 0)) // protect if patrol route is empty
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is missing patrol points"), *PatrollingGuard->GetName());
		return EBTNodeResult::Failed; 
	} 

	//set the next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	
	//set the next index
	auto NextIndex = FMath::Fmod(Index + 1, PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}