// FUNC_NAME: ModuleManager::Initialize
int __thiscall ModuleManager::Initialize(ModuleManager *this)
{
    char alreadyInitialized;
    
    alreadyInitialized = FUN_00602e20();  // Check global initialization state
    if (alreadyInitialized != '\0') {
        return 0;                         // Already initialized, return failure
    }
    FUN_0090d080();                       // Perform debug/logging setup
    DAT_00e5672c = 3;                     // Set global module state to 3
    *(int *)(this + 0x60) = 0;            // Clear member at offset 0x60 (likely a pointer or flag)
    if ((DAT_01130590 & 1) == 0) {        // If one-time registration not done
        FUN_005c0d50(this + 0x14, &LAB_00931e00, 0); // Register callback with this+0x14 as context
        DAT_01130590 |= 1;                // Mark registration as done
    }
    return 1;                             // Success
}