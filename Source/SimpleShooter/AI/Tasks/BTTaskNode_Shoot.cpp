// Copyrights Mattia De Prisco 2020


#include "BTTaskNode_Shoot.h"

#include "AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AIController = OwnerComp.GetAIOwner();

	if(!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(AIController->GetPawn());

	if(!ShooterCharacter)
	{
		return EBTNodeResult::Failed;
	}

	ShooterCharacter->PullTrigger();
	return EBTNodeResult::Succeeded;
}
