// Address: 0x0072c0d0 - Checks if ability ID 0xFA is unlocked or can be unlocked
// FUNC_NAME: GodfatherGameManager::isAbilityUnlocked

int __fastcall GodfatherGameManager::isAbilityUnlocked(int thisPtr)
{
    // Check bit 0 at offset +0x1b97 (flags for unlocked abilities)
    if ((*(byte*)(thisPtr + 0x1b97) & 1) == 0)
    {
        // Ability not yet unlocked; check if unlock requirements are met (e.g., reputation cost)
        char unlockCheckResult = FUN_0054f220(0xFA);
        if (unlockCheckResult == '\0')
        {
            return 0; // Cannot unlock yet
        }
    }
    return 1; // Ability is already unlocked or can be unlocked now
}