#include "WARWorldActorRegistry.h"

AActor * UWARWorldActorRegistry::GetActorWithTag( const FGameplayTag gameplay_tag ) const
{
    if ( const auto * actor = Registry.Find( gameplay_tag ) )
    {
        return *actor;
    }

    return nullptr;
}

AActor * UWARWorldActorRegistry::GetActorsWithTag( const FGameplayTag gameplay_tag ) const
{
    TArray< FGameplayTag > tags;
    Registry.GetKeys( tags );

    for(const auto &tag : tags)
    {
        
    }
}

bool UWARWorldActorRegistry::AddActorToRegistry( AActor * actor, const FGameplayTag tag )
{
    if ( actor == nullptr || !actor->HasAuthority() )
    {
        return false;
    }

    if ( !ensure( tag.IsValid() ) )
    {
        return false;
    }

    auto & existing_actors = Registry.FindOrAdd( actor->GetClass() );

    if ( !ensure( !existing_actors.Find( tag ) ) )
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
