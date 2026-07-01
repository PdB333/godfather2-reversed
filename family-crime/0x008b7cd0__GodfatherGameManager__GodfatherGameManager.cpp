// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x008b7cd0
// Role: Constructor for the GodfatherGameManager singleton. Sets vtable pointers, stores global instance, calls base initialization and registration.

// Known class: GodfatherGameManager (EARS::Modules::GodfatherGameManager)
// Offsets: +0x00 = vtable pointer (derived class)
//          +0x04 = second vtable pointer (likely from multiple inheritance or secondary interface)

// Global pointer to the singleton instance
extern GodfatherGameManager* g_pGodfatherGameManager; // DAT_011299cc

// Forward declarations of helper functions
void __fastcall baseConstructor(void* this); // FUN_008b7ca0
void __fastcall registerWithHash(uint hash, void* obj, int param); // FUN_00463980

// Vtable symbols (from data section)
extern void* g_vtableGodfatherGameManager; // PTR_FUN_00d7b3a4
extern void* g_vtableSecondary;            // PTR_LAB_00d7b3a0
extern void* g_vtableBase;                 // PTR_LAB_00d7b39c (unused after overwrite)

void* __fastcall GodfatherGameManager::GodfatherGameManager(void* this)
{
    // Set base vtable (overwritten later, but kept for consistency)
    *(void**)((int)this + 4) = &g_vtableBase; // +0x04

    // Store global singleton pointer
    g_pGodfatherGameManager = this;

    // Set derived class vtable
    *(void**)this = &g_vtableGodfatherGameManager; // +0x00

    // Set secondary vtable (overwrites previous base vtable)
    *(void**)((int)this + 4) = &g_vtableSecondary; // +0x04

    // Call base class initialization
    baseConstructor(this);

    // Register this instance with a hash (likely for event system or manager lookup)
    registerWithHash(0x8d946a1b, this, 7);

    return this;
}