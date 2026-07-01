// FUNC_NAME: SomeClass::constructor
// Address: 0x008e6e20
// Constructor for a class with vtable at +0x00, two additional vtable-like pointers at +0x3C and +0x48,
// and a sub-object at +0x50 (size 0x14?).
// Total object size: 0x8C (140 bytes).

#include <cstddef>

class SomeClass {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Unknown data at offsets 0x04 to 0x38 (0x3C - 4 = 0x38 bytes)
    // Possibly member variables or padding.

    // Pointer at offset 0x3C (0xF * 4)
    void* ptrAt0x3C;

    // Pointer at offset 0x48 (0x12 * 4)
    void* ptrAt0x48;

    // Sub-object at offset 0x50 (0x14 * 4)
    // This sub-object is initialized by FUN_004086d0 and FUN_00408310.
    // Likely a base class or member object.
    // Size unknown, but likely 0x14 bytes? (0x64 - 0x50 = 0x14)
    // Actually offset 0x14 in param_1 array means byte offset 0x50.
    // The sub-object might be of type SubObject.
    // We'll represent it as a placeholder.
    struct SubObject {
        // Members...
    } subObject; // at offset 0x50

    // Constructor
    // param_2: flags (bit 0 indicates whether to call operator delete)
    SomeClass(byte flags) {
        // Set vtable pointer
        vtable = (void*)0x00d80554;

        // Set additional vtable-like pointers
        ptrAt0x3C = (void*)0x00d80544;
        ptrAt0x48 = (void*)0x00d80540;

        // Initialize sub-object at offset 0x50
        // FUN_004086d0 is likely a constructor for SubObject
        FUN_004086d0(&subObject);
        // FUN_00408310 might be another initialization step
        FUN_00408310(&subObject);

        // Global initialization call
        FUN_0046c640();

        // If bit 0 of flags is set, call operator delete with size 0x8C
        if ((flags & 1) != 0) {
            // FUN_0043b960 is likely operator delete(void*, size_t)
            FUN_0043b960(this, 0x8C);
        }
    }
};

// Note: The actual function names (FUN_004086d0, etc.) are placeholders.
// In the real codebase, these would be identified and renamed accordingly.