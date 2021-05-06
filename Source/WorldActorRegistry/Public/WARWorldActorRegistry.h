
#pragma once

#include "GameplayTagContainer.h"

#include <CoreMinimal.h>
#include <Subsystems/WorldSubsystem.h>

#include "WARWorldActorRegistry.generated.h"

UCLASS()
class WORLDACTORREGISTRY_API UWARWorldActorRegistry : public UWorldSubsystem {
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintPure)
  TArray<AActor *> GetActorsFromClass(UClass *actor_class) const;

  UFUNCTION(BlueprintPure)
  AActor *GetActorFromClass(UClass *actor_class) const;

  UFUNCTION(BlueprintPure)
  AActor *GetActorFromClassWithTag(UClass *actor_class,
                                   const FGameplayTag gameplay_tag) const;

  UFUNCTION(BlueprintCallable)
  bool AddActorToRegistry(AActor *actor, const FGameplayTag tag);

  UFUNCTION(BlueprintCallable)
  bool RemoveActorFromRegistry(AActor *actor, const FGameplayTag tag);

  UFUNCTION(BlueprintCallable)
  void Clear();

private:
  TMap<UClass *, TMap<FGameplayTag, AActor *>> Registry;
};
