// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x006d4ac0
// Description: Constructor for the main game manager singleton. Initializes large sentinel-filled array (debug markers) and sets up multiple vtables for single/multiple inheritance.

// Known classes: GodfatherGameManager from EA EARS engine (The Godfather 2)

// Forward declarations for external functions
void __fastcall BaseConstructor1(void* this);  // FUN_004737b0
void __fastcall BaseConstructor2(void* this);  // FUN_00473750

// Global pointer to singleton instance
GodfatherGameManager* g_GameManager = nullptr; // DAT_0112a878

// External global data referenced (likely static initializers)
extern int _DAT_00d5780c;   // base health?
extern int DAT_00d5f00c;   // some config
extern int DAT_00e447a4;   // another config

// Vtable references (external)
extern void* PTR_LAB_00d5f3d0;  // vtable for base1
extern void* PTR_FUN_00d5f3f0;  // vtable for main class
extern void* PTR_LAB_00d5f3e0;  // vtable for base2?
extern void* PTR_LAB_00d5f3dc;
extern void* PTR_LAB_00d5f3d8;
extern void* PTR_LAB_00d5f3d4;  // vtable update after second base

class GodfatherGameManager {
public:
    // Vtable pointers embedded (offsets in dwords)
    // +0x00: main vtable (PTR_FUN_00d5f3f0)
    // +0x3C (0x0F): base2 vtable (PTR_LAB_00d5f3e0)
    // +0x48 (0x12): another base vtable (PTR_LAB_00d5f3dc)
    // +0x50 (0x14): another base vtable (PTR_LAB_00d5f3d8)
    // +0x58 (0x16): vtable pointer updated after second base (PTR_LAB_00d5f3d0 then PTR_LAB_00d5f3d4)

    // Data offsets (dword indices):
    // +0x28 (0xA0): some health/config value
    // +0x29 (0xA4): config value
    // +0x2A (0xA8): zero
    // +0x2B (0xAC): config value
    // +0x2D (0xB4) to +0x88 (0x88*4 = 0x220): 23 groups of 4 uint32 sentinel values (debug fill)

    // Constructor
    GodfatherGameManager() {
        BaseConstructor1(this);  // FUN_004737b0

        // Set initial vtable pointers
        *(void**)((uint8_t*)this + 0x58) = &PTR_LAB_00d5f3d0;      // param_1[0x16]
        *(void**)(this) = &PTR_FUN_00d5f3f0;                       // main vtable
        *(void**)((uint8_t*)this + 0x3C) = &PTR_LAB_00d5f3e0;      // param_1[0x0F]
        *(void**)((uint8_t*)this + 0x48) = &PTR_LAB_00d5f3dc;      // param_1[0x12]
        *(void**)((uint8_t*)this + 0x50) = &PTR_LAB_00d5f3d8;      // param_1[0x14]

        BaseConstructor2(this);  // FUN_00473750

        // Fill the sentinel block: 23 groups of (0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911)
        // Starting at offset 0xB4 (dword index 0x2D)
        uint32_t* sentinelStart = (uint32_t*)((uint8_t*)this + 0xB4);
        for (int i = 0; i < 23; ++i) {
            sentinelStart[i*4 + 0] = 0xBADBADBA;
            sentinelStart[i*4 + 1] = 0xBEEFBEEF;
            sentinelStart[i*4 + 2] = 0xEAC15A55;
            sentinelStart[i*4 + 3] = 0x91100911;
        }

        // Update vtable pointer at offset 0x58 again (possibly after constructing a derived class)
        *(void**)((uint8_t*)this + 0x58) = &PTR_LAB_00d5f3d4;      // param_1[0x16] reassigned

        BaseConstructor2(this);  // second call to FUN_00473750 (maybe another base)

        // Assign global config values
        uint32_t* configStart = (uint32_t*)((uint8_t*)this + 0xA0); // offset 0x28 in dwords
        configStart[0] = _DAT_00d5780c;    // param_1[0x28]
        configStart[1] = DAT_00d5f00c;     // param_1[0x29]
        configStart[2] = 0;                // param_1[0x2A]
        configStart[3] = DAT_00e447a4;     // param_1[0x2B]

        // Register this instance as global singleton
        g_GameManager = this;  // DAT_0112a878
    }
};