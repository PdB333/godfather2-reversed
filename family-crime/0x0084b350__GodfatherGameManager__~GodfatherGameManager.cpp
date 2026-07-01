// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
// Address: 0x0084b350 - Destructor for the main game manager singleton.
// Releases internal resources, deletes a sub-object at offset +0xC, clears global singleton pointer, and calls final cleanup.

void __fastcall GodfatherGameManager::~GodfatherGameManager(void)
{
    // Set first vtable pointer at +0x00 (main vtable)
    *(void**)this = (void*)&PTR_FUN_00d74d54;
    // Set second vtable pointer at +0x08 (e.g., interface vtable for multiple inheritance)
    *(void**)((char*)this + 8) = (void*)&PTR_LAB_00d74d50;

    // Release or deinitialize some internal resource (likely a global or static member)
    FUN_0049c7f0(&DAT_00d74d40);

    // If a sub-object exists at offset +0x0C, delete it
    if (*(void**)((char*)this + 12) != 0)
    {
        FUN_009c8f10(*(void**)((char*)this + 12));
    }

    // Switch second vtable to a “destroyed” state
    *(void**)((char*)this + 8) = (void*)&PTR_LAB_00d74d4c;

    // Clear the global singleton pointer (e.g., g_pGameManager)
    DAT_0112a668 = 0;

    // Final cleanup, possibly freeing memory or shutting down subsystems
    FUN_0049c640();
}