#pragma once

#include <CoreMinimal.h>
#include <GameplayTagContainer.h>
#include <Subsystems/WorldSubsystem.h>

#include "WARWorldActorRegistry.generated.h"

UCLASS()
class WORLDACTORREGISTRY_API UWARWorldActorRegistry : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure )
    AActor * GetActorWithTag( const FGameplayTag gameplay_tag, bool is_tag_exact = true ) const;

    UFUNCTION( BlueprintPure )
    TArray< AActor * > GetAllActorsWithTag( const FGameplayTag gameplay_tag, bool is_tag_exact = true ) const;

    UFUNCTION( BlueprintCallable )
    bool AddActorToRegistry( AActor * actor, const FGameplayTag tag );

    UFUNCTION( BlueprintCallable )
    bool RemoveActorFromRegistry( AActor * actor, const FGameplayTag tag );

    UFUNCTION( BlueprintCallable )
    void Clear();

    UFUNCTION( BlueprintPure )
    bool IsActorRegistered( AActor * actor ) const;

private:
    TMap< FGameplayTag, TArray< AActor * > > Registry;
};
