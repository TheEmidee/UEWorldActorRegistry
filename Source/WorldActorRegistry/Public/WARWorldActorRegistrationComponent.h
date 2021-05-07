#pragma once

#include <Components/ActorComponent.h>
#include <CoreMinimal.h>

#include "GameplayTagContainer.h"

#include "WARWorldActorRegistrationComponent.generated.h"

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class WORLDACTORREGISTRY_API UWARWorldActorRegistrationComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    UWARWorldActorRegistrationComponent();

    void BeginPlay() override;
    void BeginDestroy() override;

private:
    UPROPERTY( EditDefaultsOnly )
    FGameplayTag GameplayTag;
};