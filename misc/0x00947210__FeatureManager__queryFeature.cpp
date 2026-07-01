// FUNC_NAME: FeatureManager::queryFeature
// Address: 0x00947210
// Role: Checks if a specific feature (identified by hash 0xf4636937) is enabled via a singleton manager.
//        Returns the feature hash if enabled, otherwise 0.

uint FeatureManager::queryFeature()
{
    FeatureManager* manager = (FeatureManager*)GetFeatureManagerSingleton(); // FUN_00946cc0
    if (manager != nullptr)
    {
        uint featureHash = 0xf4636937;
        int result = 0;
        bool isEnabled = (manager->vftable->isFeatureEnabled)(featureHash, &result); // vtable+0x10
        if (isEnabled)
            return featureHash;
    }
    return 0;
}