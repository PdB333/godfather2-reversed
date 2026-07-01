// Xbox PDB: EARS_Modules_HitMissionManager_HitMissionManager
// FUNC_NAME: RandomIntelManager::RandomIntelManager
class RandomIntelManager {
public:
    // +0x00: vtable pointer (set to &PTR_FUN_00d816bc)
    // +0x04: unknown (set to 1)
    // +0x08: unknown (set to 0)
    // +0x0C: RTTI or class descriptor pointer (set then overwritten)
    // +0x10 through +0x20: five zeroed fields
    // +0x24: end of structure
    
    RandomIntelManager();
};

// Global pointer to singleton instance
extern RandomIntelManager* g_randomIntelManager; // DAT_011299c8

RandomIntelManager::RandomIntelManager() {
    // Initialize unknown fields
    *(int*)(this + 4) = 1;   // version or flag
    *(int*)(this + 8) = 0;   // unknown

    // Set temporary vtable or RTTI (first assignment)
    *(void**)(this + 12) = (void*)&PTR_LAB_00d816b4;

    // Set main vtable
    *(void**)this = (void*)&PTR_FUN_00d816bc;

    // Overwrite offset +12 with final RTTI pointer
    *(void**)(this + 12) = (void*)&PTR_LAB_00d816b8;

    // Zero out fields at offsets 16-32 (0x10-0x20)
    *(int*)(this + 16) = 0;
    *(int*)(this + 20) = 0;
    *(int*)(this + 24) = 0;
    *(int*)(this + 28) = 0;
    *(int*)(this + 32) = 0;

    // Register message "iMsgRevealRandomIntel"
    extern int g_msgRevealRandomIntel; // DAT_0112ff08
    MessageSystem::registerMessage(&g_msgRevealRandomIntel, "iMsgRevealRandomIntel");

    // If message ID is non-zero, register this object as handler with flag 0x8000
    if (g_msgRevealRandomIntel != 0) {
        MessageSystem::registerHandler(this, &g_msgRevealRandomIntel, 0x8000);
    }

    // Register other intel messages (IDs stored in globals, handlers not registered here)
    extern int g_msgRandomIntelRevealed; // DAT_0112ff00
    MessageSystem::registerMessage(&g_msgRandomIntelRevealed, "iMsgRandomIntelRevealed");

    extern int g_msgNoIntelToReveal; // DAT_0112fef4
    MessageSystem::registerMessage(&g_msgNoIntelToReveal, "iMsgNoIntelToReveal");
}