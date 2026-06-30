// FUNC_NAME: GodfatherGameManager::constructor

// Constructor for the GodfatherGameManager singleton.
// Called from main initialization at 0x007da1e0.
// Sets up vtable pointers and stores the instance globally.

#include <cstdint>

class GodfatherGameManager {
public:
    // Vtable pointers (offsets relative to this)
    // +0x00: primary vtable (PTR_FUN_00d5f32c)
    // +0x3C: vtable for interface A (PTR_LAB_00d5f31c)
    // +0x48: vtable for interface B (PTR_LAB_00d5f318)
    // +0x50: vtable for interface C (PTR_LAB_00d5f314)
    // +0x58: vtable for interface D (PTR_LAB_00d5f310)

    static GodfatherGameManager* s_instance; // DAT_0112a874

    // Base class constructor (likely EARSObject or similar)
    void __fastcall baseConstructor() {
        // Calls FUN_004737b0 (EARSObject::constructor or similar)
        // Inline assembly or external function call
        // For reconstruction, we assume it's a call to a base constructor
        // that initializes base class members.
    }

    // Constructor
    void __fastcall constructor() {
        baseConstructor();

        // Set vtable pointers
        // Note: The first assignment to offset 0x58 is overwritten,
        // likely a base class vtable that is replaced by the derived one.
        *(void**)((uintptr_t)this + 0x58) = (void*)0x00d5f2f0; // Base vtable D (overwritten)
        *(void**)((uintptr_t)this + 0x00) = (void*)0x00d5f32c; // Primary vtable
        *(void**)((uintptr_t)this + 0x3C) = (void*)0x00d5f31c; // Interface A
        *(void**)((uintptr_t)this + 0x48) = (void*)0x00d5f318; // Interface B
        *(void**)((uintptr_t)this + 0x50) = (void*)0x00d5f314; // Interface C
        *(void**)((uintptr_t)this + 0x58) = (void*)0x00d5f310; // Interface D (final)

        // Store global singleton pointer
        s_instance = this;
    }
};

// Global instance pointer
GodfatherGameManager* GodfatherGameManager::s_instance = nullptr;