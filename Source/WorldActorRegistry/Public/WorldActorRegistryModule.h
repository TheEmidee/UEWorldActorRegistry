#pragma once

#include <Modules/ModuleManager.h>

class IWorldActorRegistryModule final : public IModuleInterface
{
public:
    void StartupModule() override;
    void ShutdownModule() override;

    static IWorldActorRegistryModule & Get()
    {
        return FModuleManager::LoadModuleChecked< IWorldActorRegistryModule >( "WorldActorRegistry" );
    }

    static bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded( "WorldActorRegistry" );
    }
};
