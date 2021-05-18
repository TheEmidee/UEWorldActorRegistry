#include "WARWorldActorRegistrationComponent.h"

#include "WARWorldActorRegistry.h"

#include <GameFramework/Actor.h>

UWARWorldActorRegistrationComponent::UWARWorldActorRegistrationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWARWorldActorRegistrationComponent::BeginPlay()
{
    Super::BeginPlay();

    if ( !GetOwner()->HasAuthority() )
    {
        return;
    }

    if ( auto * world = GetWorld() )
    {
        if ( auto * world_actor_registry = world->GetSubsystem< UWARWorldActorRegistry >() )
        {
            if ( ensureAlwaysMsgf( GameplayTag.IsValid(), TEXT( "No valid gameplay tag set in WAR component!" ) ) )
            {
                world_actor_registry->AddActorToRegistry( GetOwner(), GameplayTag );
            }
        }
    }
}

void UWARWorldActorRegistrationComponent::BeginDestroy()
{
    Super::BeginDestroy();

    if ( GetOwner() == nullptr || GetWorld() == nullptr )
    {
        return;
    }

    if ( auto * world = GetWorld() )
    {
        if ( auto * world_actor_registry = world->GetSubsystem< UWARWorldActorRegistry >() )
        {
            world_actor_registry->RemoveActorFromRegistry( GetOwner(), GameplayTag );
        }
    }
}
