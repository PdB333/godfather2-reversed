// FUNC_NAME: GodfatherGameManager::GodfatherGameManager()  // 0x00905660
// Constructor for the singleton GodfatherGameManager.
// Initializes base classes, sets vtable pointers, zeroes fields, and assigns the global instance.

class GodfatherGameManager : public SomeBaseClass1, public SomeBaseClass2 {
public:
    // VTable pointers at offsets 0x0 and 0x208 (0x82 * 4)

    // Base class constructor call (FUN_004c26c0) – likely initializes base at offset 0x208
    GodfatherGameManager() __thiscall {
        // Call base class constructor (sets vtable at 0x208 to base2 vtable)
        // This is FUN_004c26c0 (assumed)
        SomeBaseClass2::SomeBaseClass2(); // Base with vtable at +0x208

        // Set temporary vtable at +0x208 (base2 vtable) – overwritten later
        *(void**)((char*)this + 0x208) = &PTR_LAB_00e2f530; // initial base vtable

        // Store global singleton pointer
        g_pGodfatherGameManager = this; // DAT_012233bc

        // Zero fields at offsets 0x20C, 0x210, 0x214 (0x83–0x85)
        *(int*)((char*)this + 0x20C) = 0; // field_0x20C
        *(int*)((char*)this + 0x210) = 0; // field_0x210
        *(int*)((char*)this + 0x214) = 0; // field_0x214

        // Set main vtable at offset 0x0 (for primary base)
        *(void**)this = &PTR_FUN_00d82630; // vtable for derived primary base

        // Override vtable at +0x208 with derived version
        *(void**)((char*)this + 0x208) = &PTR_LAB_00d8262c; // derived vtable for base2

        // Zero fields at offsets 0x218, 0x21C, 0x220 (0x86–0x88)
        *(int*)((char*)this + 0x218) = 0; // field_0x218
        *(int*)((char*)this + 0x21C) = 0; // field_0x21C
        *(int*)((char*)this + 0x220) = 0; // field_0x220
    }

    // External global pointer (set by constructor)
    static GodfatherGameManager* g_pGodfatherGameManager; // DAT_012233bc
};

// Static definition
GodfatherGameManager* GodfatherGameManager::g_pGodfatherGameManager = nullptr;