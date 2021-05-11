#include "WARWorldActorRegistry.h"

AActor * UWARWorldActorRegistry::GetActorWithTag( const FGameplayTag gameplay_tag, bool is_tag_exact /*= true*/ ) const
{
    TArray< FGameplayTag > key_tags;
    Registry.GetKeys( key_tags );

    for ( const auto & key_tag : key_tags )
    {
        if ( is_tag_exact && !key_tag.MatchesTagExact( gameplay_tag ) )
        {
            continue;
        }

        if ( !is_tag_exact && !key_tag.MatchesTag( gameplay_tag ) )
        {
            continue;
        }

        const auto & actors = Registry[ key_tag ];
        if ( actors.Num() > 0 )
        {
            return actors[ 0 ];
        }
    }

    return nullptr;
}

TArray< AActor * > UWARWorldActorRegistry::GetAllActorsWithTag( const FGameplayTag gameplay_tag, bool is_tag_exact /*= true*/ ) const
{
    TArray< FGameplayTag > key_tags;
    Registry.GetKeys( key_tags );

    TArray< AActor * > result_actors;

    for ( const auto & key_tag : key_tags )
    {
        if ( is_tag_exact && key_tag.MatchesTagExact( gameplay_tag ) )
        {
            return Registry[ key_tag ];
        }

        if ( !is_tag_exact && key_tag.MatchesTag( gameplay_tag ) )
        {
            result_actors.Append( Registry[ key_tag ] );
        }
    }

    return result_actors;
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

    TArray< TArray< AActor * > > values;
    Registry.GenerateValueArray( values );

    for ( const auto & actor_array : values )
    {
        if ( actor_array.Contains( actor ) )
        {
            return false;
        }
    }

    auto & existing_actors = Registry.FindOrAdd( tag );
    existing_actors.Add( actor );
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

    if ( !ensure( tag.IsValid() ) )
    {
        return false;
    }

    auto * existing_actors = Registry.Find( tag );
    if ( existing_actors != nullptr )
    {
        return existing_actors->Remove( actor ) > 0;
    }

    return false;
}

void UWARWorldActorRegistry::Clear()
{
    Registry.Reset();
}
