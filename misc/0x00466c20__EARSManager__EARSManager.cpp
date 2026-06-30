// FUNC_NAME: EARSManager::EARSManager
// 0x00466c20: Constructor for the core EARS engine singleton manager.
// Sets up virtual table pointers (likely due to multiple inheritance or virtual base)
// and stores the instance globally in g_pEARSManager.

#include <cstdint>

// Forward declaration of base class constructor (live at 0x0043e2e0)
extern void BaseObject_constructor(void* thisPtr);

// Vtable symbols (pointers to vtable arrays)
extern void* PTR_FUN_00e31e98;  // vtable for primary base (offset +0x00)
extern void* PTR_LAB_00e31ea4;  // vtable for secondary base (offset +0x04)
extern void* PTR_LAB_00e31ea8;  // temporary vtable pointer (overwritten)

// Global singleton pointer
extern EARSManager* g_pEARSManager;

class EARSManager {
public:
    void* vtable1;  // +0x00: Primary vtable pointer
    void* vtable2;  // +0x04: Secondary vtable pointer (for multiple inheritance)

    // Constructor
    EARSManager() __fastcall;  // __fastcall to match ECX=this, EDX=unused
};

// Implementation matching the decompiled code
EARSManager* __fastcall EARSManager::EARSManager() {
    // Step 1: Set secondary vtable to temporary value (will be overwritten)
    this->vtable2 = &PTR_LAB_00e31ea8;

    // Step 2: Set primary vtable
    this->vtable1 = &PTR_FUN_00e31e98;

    // Step 3: Set secondary vtable to final derived class vtable
    this->vtable2 = &PTR_LAB_00e31ea4;

    // Step 4: Store this instance globally
    g_pEARSManager = this;

    // Step 5: Call base class constructor (likely sets up its own vtable)
    BaseObject_constructor(this);

    // Return this pointer (standard for constructors)
    return this;
}