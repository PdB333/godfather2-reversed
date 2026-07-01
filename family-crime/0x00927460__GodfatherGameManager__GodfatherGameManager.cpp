// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

// Address: 0x00927460 - Constructor for GodfatherGameManager singleton.
// Initializes base vtables, sets up overriding vtables, zeros many fields, and stores global pointer.
class GodfatherGameManager {
public:
    // Placeholder for internal fields (size >= 0x3D4 bytes)
    // Offsets based on decompilation:
    // +0x00: main vtable (void**)
    // +0x04: ? 
    // +0x10: secondary vtable (void**)
    // +0x4C: vtable/ptr (overridden)
    // +0x50: int32 (set to 1)
    // +0x54: int32 (set to 0)
    // +0x58: data ptr (overridden)
    // +0x3A0: byte[4] (zeroed)
    // +0x3A4: int32 (zeroed) (field_0x3A4) 
    // +0x3A8: int32 (zeroed)
    // +0x3AC: int32 (zeroed)
    // +0x3B0: int32 (zeroed)
    // +0x3B4: uint32 (set to global constant)
    // +0x3B8: uint32 (set to global constant)
    // +0x3BC: uint32 (set to global constant)
    // +0x3C0: uint32 (set to global constant)
    // +0x3C4: byte[4] (zeroed)
    // +0x3C8: byte (zeroed)
    // +0x3CC: int32 (zeroed)
    // +0x3D0: int32 (zeroed) (field_0x3D0)

    GodfatherGameManager(); // __thiscall
};

// Global instance pointer
extern GodfatherGameManager* g_pGameManager;
GodfatherGameManager* g_pGameManager = nullptr;

GodfatherGameManager::GodfatherGameManager() {
    // Base class initialization (static function, no this)
    // Likely sets up some global engine state (e.g., memory pools, allocators)
    someGlobalInitFunction(); // FUN_005bf9b0

    // Set initial vtables (base class)
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x4C) = &PTR_FUN_00e2f19c; // vtable
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x50) = 1;               // field_0x50
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x54) = 0;               // field_0x54
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x58) = &PTR_LAB_00d87940; // data ptr

    // Store this instance globally
    g_pGameManager = this;

    // Set main vtable and secondary vtable (derived class)
    *(void***)this = &PTR_FUN_00d87980;        // main vtable
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x10) = &PTR_LAB_00d87958; // secondary vtable

    // Override the earlier vtable/data pointers with derived class versions
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x4C) = &PTR_LAB_00d87948; // overridden vtable
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x58) = &PTR_LAB_00d87944; // overridden data ptr

    // Additional initialization (static function)
    someOtherInitFunction(); // FUN_00927a00

    // Zero a block of four 32-bit fields (0x3A4-0x3B0)
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3A4) = 0;
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3A8) = 0;
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3AC) = 0;
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3B0) = 0;

    // Zero a block at 0x3CC
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3CC) = 0;

    // Zero a 4-byte block at 0x3A0 (bytes)
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x3A0) = 0;

    // Zero a 4-byte block at 0x3C4 (bytes)
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x3C4) = 0;

    // Zero a single byte at 0x3C8
    *(reinterpret_cast<uint8_t*>(this) + 0x3C8) = 0;

    // Zero field at 0x3D0
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3D0) = 0;

    // Set four consecutive fields at 0x3B4-0x3C0 to a global constant (likely a sentinel or max value)
    uint32_t constant = DAT_00d5ccf8; // e.g., 0xFFFFFFFF or 0x7F800000
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3B4) = constant;
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3B8) = constant;
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3BC) = constant;
    *(uint32_t*)(reinterpret_cast<uint8_t*>(this) + 0x3C0) = constant;
}