// FUNC_NAME: GodfatherGameManager::initializeSubsystems
void GodfatherGameManager::initializeSubsystems(void* param1, void* param2, void* param3, void* param4,
                                                 void* param5, void* param6, void* param7, void* param8,
                                                 void* param9, void* param10)
{
    int* singletonPtr = DAT_01129930; // Global singleton pointer to GodfatherGameManager instance
    // Copy value at +0x1DC to +0x1D8 (likely a pointer or flag update)
    *(int*)(singletonPtr + 0x1D8) = *(int*)(DAT_01129930 + 0x1DC);

    // Call subsystem initialization functions with provided parameters
    FUN_0095cb00(param1);          // Initialize subsystem A
    FUN_0095cb90(param8);          // Initialize subsystem B (param8 used)
    FUN_0095fa40(param2);          // Initialize subsystem C
    FUN_0095f980(param3);          // Initialize subsystem D
    FUN_0095f9e0(param4);          // Initialize subsystem E
    FUN_0095c310(param5);          // Initialize subsystem F
    FUN_0095fa80(param6);          // Initialize subsystem G
    FUN_0095f8b0(param7, 0);       // Initialize subsystem H (with extra flag 0)
    FUN_0095cda0(param9);          // Initialize subsystem I
    FUN_0095ccf0(param10);         // Initialize subsystem J
    return;
}