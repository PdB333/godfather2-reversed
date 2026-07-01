// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x009831f0
// Role: Constructor for the GodfatherGameManager singleton. Initializes vtable pointers, zeros fields, and stores the global singleton reference.

#include <cstdint>

struct GodfatherGameManager;
extern void __thiscall BaseConstructor(GodfatherGameManager* this); // 0x005bf9b0 (SimManager or Manager)
extern GodfatherGameManager* g_pGameManager; // DAT_0112982c

// Vtable pointers from the data section
void* const VTABLE_PRIMARY   = (void*)0x00d86000;   // PTR_FUN_00d86000
void* const VTABLE_SECONDARY = (void*)0x00d85fdc;   // PTR_LAB_00d85fdc
void* const VTABLE_OVERRIDE  = (void*)0x00d85fd8;   // PTR_LAB_00d85fd8 (also used initially via PTR_LAB_00d85d84 which points to same)

__thiscall GodfatherGameManager::GodfatherGameManager() {
    // Call base class constructor (likely SimManager or generic Manager)
    BaseConstructor(this);

    // Set vtable at offset +0x4C to the initial ptable (PTR_LAB_00d85d84)
    *(void**)((uint32_t)this + 0x4C) = VTABLE_OVERRIDE;

    // Store this instance in the global singleton pointer
    g_pGameManager = this;

    // Zero out four uint32 fields at offsets 0x68, 0x6C, 0x70, 0x74
    *(uint32_t*)((uint32_t)this + 0x68) = 0;
    *(uint32_t*)((uint32_t)this + 0x6C) = 0;
    *(uint32_t*)((uint32_t)this + 0x70) = 0;
    *(uint32_t*)((uint32_t)this + 0x74) = 0;

    // Set the primary vtable pointer (offset +0x00)
    *(void**)this = VTABLE_PRIMARY;

    // Set the secondary vtable pointer (offset +0x10)
    *(void**)((uint32_t)this + 0x10) = VTABLE_SECONDARY;

    // Override vtable at offset +0x4C again (now using PTR_LAB_00d85fd8)
    *(void**)((uint32_t)this + 0x4C) = VTABLE_OVERRIDE;

    // Zero out another four uint32 fields at offsets 0x78, 0x7C, 0x80, 0x84
    *(uint32_t*)((uint32_t)this + 0x78) = 0;
    *(uint32_t*)((uint32_t)this + 0x7C) = 0;
    *(uint32_t*)((uint32_t)this + 0x80) = 0;
    *(uint32_t*)((uint32_t)this + 0x84) = 0;

    // Zero out uint32 at offset +0x8C
    *(uint32_t*)((uint32_t)this + 0x8C) = 0;

    // Clear two bytes at offsets 0x91 and 0x92
    *(uint8_t*)((uint32_t)this + 0x91) = 0;
    *(uint8_t*)((uint32_t)this + 0x92) = 0;

    // Set two byte flags at offsets 0x88 and 0x90 to 1
    *(uint8_t*)((uint32_t)this + 0x88) = 1;
    *(uint8_t*)((uint32_t)this + 0x90) = 1;

    // Set the integer at offset +0x08 to 3
    *(uint32_t*)((uint32_t)this + 0x08) = 3;

    // Zero out three 8-byte blocks at offsets 0x50, 0x58, 0x60
    *(uint64_t*)((uint32_t)this + 0x50) = 0;
    *(uint64_t*)((uint32_t)this + 0x58) = 0;
    *(uint64_t*)((uint32_t)this + 0x60) = 0;

    // Return this (implicit)
}