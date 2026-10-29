// Fill out your copyright notice in the Description page of Project Settings.


#include "Libs/BlueprintSubsystemsLib.h"

#include "Subsystems/BlueprintSubsystemManager.h"
#include "Subsystems/BlueprintWorldSubsystemManager.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


UBlueprintSubsystemBase* UBlueprintSubsystemsLib::GetBlueprintSubsystem(const UObject* WorldContextObject,
                                                                        TSubclassOf<UBlueprintSubsystemBase>
                                                                        SubsystemClass)
{
	if (!IsValid(WorldContextObject) || !SubsystemClass || !GEngine)
		return nullptr;

	// A GameInstance has no world context of its own, so resolve it directly first.
	UGameInstance* gameInstance = Cast<UGameInstance>(const_cast<UObject*>(WorldContextObject));
	if (!IsValid(gameInstance))
	{
		gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	}

	if (!IsValid(gameInstance))
		return nullptr;

	UBlueprintSubsystemManager* manager = gameInstance->GetSubsystem<UBlueprintSubsystemManager>();
	if (!IsValid(manager))
		return nullptr;

	return manager->GetSubsystem(SubsystemClass);
}

UBlueprintSubsystemBase* UBlueprintSubsystemsLib::GetBlueprintWorldSubsystem(
	const UObject* WorldContextObject,
	TSubclassOf<UBlueprintSubsystemBase> SubsystemClass)
{
	if (!IsValid(WorldContextObject) || !SubsystemClass || !GEngine)
	{
		return nullptr;
	}

	UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(world))
	{
		return nullptr;
	}
	UBlueprintWorldSubsystemManager* manager = world->GetSubsystem<UBlueprintWorldSubsystemManager>();
	return IsValid(manager) ? manager->GetSubsystem(SubsystemClass) : nullptr;
}
