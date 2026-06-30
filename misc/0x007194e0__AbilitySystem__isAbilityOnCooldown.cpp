// FUNC_NAME: AbilitySystem::isAbilityOnCooldown
bool __thiscall AbilitySystem::isAbilityOnCooldown(float requiredCooldown)
{
    // Buffer for ability identifier (unused after call, possibly for hashing)
    char identifier[12];
    // Elapsed time since last use (in seconds)
    float elapsedTime = 0.0f;
    // Resource/flags associated with the ability (e.g., ammo count, cooldown mask)
    unsigned int resourceFlags = 0;

    // Query cooldown state from the engine
    char success = FUN_00717620(identifier, &resourceFlags, &elapsedTime); // getAbilityCooldownData

    // Return true if the ability is still on cooldown or resource is insufficient
    // Condition: inner call succeeded AND required cooldown not yet elapsed AND resource flags below threshold
    if (success != '\0' && elapsedTime < requiredCooldown &&
        (float)(resourceFlags & DAT_00e44680) < DAT_00d61ab8) // DAT_00d61ab8: max resource, DAT_00e44680: resource mask
    {
        return true; // Ability is blocked (on cooldown or low resource)
    }
    return false; // Ability is ready
}