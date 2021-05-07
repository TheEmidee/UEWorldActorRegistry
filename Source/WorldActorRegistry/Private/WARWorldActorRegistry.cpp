#include "WARWorldActorRegistry.h"

TArray< AActor * > UWARWorldActorRegistry::GetActorsFromClass( UClass * actor_class ) const
{
    TArray< AActor * > result;

    if ( const auto * existing_actors = Registry.Find( actor_class ) )
    {
        ( *existing_actors ).GenerateValueArray( result );
    }

    return result;
}

AActor * UWARWorldActorRegistry::GetActorFromClass( UClass * actor_class ) const
{
    const auto existing_actors = GetActorsFromClass( actor_class );

    if ( existing_actors.Num() > 0 )
    {
        return existing_actors[ 0 ];
    }

    return nullptr;
}

AActor * UWARWorldActorRegistry::GetActorFromClassWithTag( UClass * actor_class, const FGameplayTag gameplay_tag ) const
{
    const auto * existing_actors = Registry.Find( actor_class );

    if ( const auto * actor = existing_actors->Find( gameplay_tag ) )
    {
        return *actor;
    }

    return nullptr;
}

bool UWARWorldActorRegistry::AddActorToRegistry( AActor * actor, const FGameplayTag tag )
{
    if ( actor == nullptr || !actor->HasAuthority() )
    {
        return false;
    }

    auto & existing_actors = Registry.FindOrAdd( actor->GetClass() );

    if ( ensure( existing_actors.Find( tag ) ) )
    {
        return false;
    }

    existing_actors.Add( tag, actor );
    return true;
}

bool UWARWorldActorRegistry::RemoveActorFromRegistry( AActor * actor, const FGameplayTag tag )
{
    if ( actor == nullptr ||
         !actor->HasAuthority() ||
         Registry.Num() == 0 )
    {
        return false;
    }

    auto * existing_actors = Registry.Find( actor->GetClass() );

    if ( existing_actors->Find( tag ) )
    {
        return existing_actors->Remove( tag ) > 0;
    }

    return false;
}

void UWARWorldActorRegistry::Clear()
{
    Registry.Reset();
}
