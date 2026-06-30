// FUNC_NAME: GodfatherGameManager::getGameSpeedMultiplier
int __fastcall GodfatherGameManager::getGameSpeedMultiplier(int this)
{
    char buffer[4]; // Stack buffer for string conversion
    float speedValue = 0.0f;
    uint convertedString;

    // Convert global string at 0xe3f95c to some form (e.g., lower case) into buffer
    convertedString = FUN_004dafd0(g_configStringGlobal, buffer);
    // Evaluate condition based on converted string
    if (FUN_005e9d90(convertedString, buffer) != 0)
    {
        // Ensure this->m_pGameSpeedManager is valid (offset 0x580)
        if (*(int *)(this + 0x580) != 0)
        {
            // Lock some mutex/critical section
            FUN_00c9eac0();
            // Retrieve float variable with index 2
            FUN_00c9cd00(2, &speedValue);
            // Unlock mutex
            FUN_00c9eae0();
        }
    }
    // Return scaled speed value (multiply by global factor, truncate to int)
    return (int)(speedValue * g_gameSpeedMultiplier);
}