// FUNC_NAME: InputControllerSlot::InputControllerSlot (or similar) at 0x008227b0
// Reconstruction of a constructor for a controller slot (0x44 bytes size, matching XInput slot size)
// The parameter param_2 indicates whether the object is heap-allocated (bit 0 set)

class InputControllerSlot {
public:
    // Constructor
    // param_2: 0 if in-place construction, 1 if heap-allocated (sets vtable delete hook)
    InputControllerSlot(byte isHeapAllocated) {
        // Base class constructor (likely SimObject or some base)
        FUN_008220e0();  // Assumed base constructor (calls vtable setup)

        // If heap-allocated, set up the custom memory deallocation
        // The vtable has a function at offset 4 that stores the allocation size (0x44)
        if (isHeapAllocated & 1) {
            int* vtable = (int*)FUN_009c8f80();  // Get vtable pointer
            // Call the second entry of vtable (often used for custom delete with size)
            ((void(__thiscall*)(InputControllerSlot*, uint))(*vtable + 4))(this, 0x44);
        }
    }

    // Destructor would be virtual; vtable set by base constructor
};

// Note: The actual class name is uncertain. It could be XInputController, ControllerSlot, or related.
// The size 0x44 matches the per-slot size in the input system (16 slots).