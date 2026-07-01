// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Constructor for the game manager singleton. Sets up multiple interface vtables and resets global state.
void __fastcall GodfatherGameManager::GodfatherGameManager(void* this)
{
    // +0x00: Primary vtable pointer
    *(DWORD*)this = (DWORD)&PTR_FUN_00d8bed8;
    // +0x10: Secondary interface vtable (offset 4 * 4)
    *((DWORD*)this + 4) = (DWORD)&PTR_LAB_00d8beb0;
    // +0x4C: Tertiary interface vtable (offset 0x13 * 4)
    *((DWORD*)this + 0x13) = (DWORD)&PTR_LAB_00d8beac;

    // +0x5C: Optional child object pointer (offset 0x17 * 4)
    if (*((DWORD*)this + 0x17) != 0) {
        // Release previous child if present
        FUN_009c8f10(*((DWORD*)this + 0x17));
    }

    // Update tertiary vtable after possible child release
    *((DWORD*)this + 0x13) = (DWORD)&PTR_LAB_00d8bea8;

    // Reset global initialization flag
    DAT_01130594 = 0;

    // Initialize engine subsystems
    FUN_005c16e0();
}