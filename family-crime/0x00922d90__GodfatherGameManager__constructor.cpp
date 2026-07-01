// FUNC_NAME: GodfatherGameManager::constructor

// Class constructor for GodfatherGameManager (global singleton at 0x0113001c).
// Sets up vtable pointers (dual inheritance: base class at offset 0, second interface at offset 4),
// initializes a field at +0x08 to 0, then registers the instance with the EARS runtime using a
// hash identifier (likely 0xc914145c corresponds to "GodfatherGameManager").

class GodfatherGameManager {
public:
    void* vtable0;         // +0x00: base class vtable (PTR_FUN_00d866a4)
    void* vtable4;         // +0x04: second vtable (PTR_LAB_00d86694)
    int field_8;           // +0x08: some flag/counter (initialized to 0)

    GodfatherGameManager(void* param_1) {
        // Global pointer stored for singleton access
        GodfatherGameManager* instance = reinterpret_cast<GodfatherGameManager*>(param_1);
        DAT_0113001c = instance;

        // Set vtable pointers
        instance->vtable4 = &PTR_LAB_00e30fe0;      // temporarily set, then overwritten below
        instance->vtable0 = &PTR_FUN_00d866a4;      // base class vtable
        instance->vtable4 = &PTR_LAB_00d86694;     // final second vtable

        // Initialize field +0x08
        instance->field_8 = 0;

        // Register this instance with the EARS runtime (size 7? likely a small structure)
        // FUN_00463980 is probably a registration function that takes a hash, a pointer, and a size
        FUN_00463980(0xc914145c, &instance->vtable4, 7);
    }
};

// Global variable (likely defined elsewhere)
extern GodfatherGameManager* DAT_0113001c;