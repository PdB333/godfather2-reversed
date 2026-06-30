// FUNC_NAME: GameObject::constructor
// Address: 0x006cfbd0
// This is a constructor for a class derived from EARSObject or similar.
// Sets vtable at offset 0, a secondary table at offset 8, and optionally allocates memory
// via a custom allocator if the placement flag (param_2 bit 0) is set.

// Assuming class size: 0xB0 (176 bytes) based on allocation call.

class GameObject {
public:
    // vtable pointer at +0x00
    void* m_vtable;
    // Unknown pointer at +0x08 (could be secondary vtable, event handler, or linked list node)
    void* m_secondaryTable;

    // Constructor: param_1 = this, param_2 = flags (bit 0 indicates allocation via custom heap)
    // Returns the constructed object pointer.
    __thiscall GameObject(void* param_1, byte param_2) {
        // Set primary vtable
        *param_1 = &PTR_FUN_00d5f1f0;   // +0x00
        // Set secondary table pointer at offset 8
        param_1[2] = &PTR_LAB_00d5f1e8; // +0x08

        // Global debug/logging check (likely read a debug flag)
        if (FUN_0089c630() != 0) {
            // Print/log message with level 7 (maybe verbose constructor trace)
            FUN_006915c0(7);
        }

        // Call base class constructor (may set additional vtable or fields)
        FUN_00473a60();

        // If the placement flag (bit 0) is set, allocate memory for this object using the global allocator.
        if ((param_2 & 1) != 0) {
            // Get the memory allocator object
            int* allocator = (int*)FUN_009c8f80();
            // Call allocator's member function at vtable+4 (typically "allocate" or "construct")
            // Arguments: destination (this) and size (0xB0)
            (**(code**)(*allocator + 4))(param_1, 0xB0);
        }

        return param_1;
    }
};

// Note: The actual class name may differ (e.g., Player, Sentient, Npc, etc.)
// The function sets two table pointers (vtable at +0, second at +8) which could indicate multiple inheritance
// or a separate interface pointer. The allocation call suggests a custom memory management system.