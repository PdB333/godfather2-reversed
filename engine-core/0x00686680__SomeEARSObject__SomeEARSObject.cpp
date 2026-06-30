// FUNC_NAME: SomeEARSObject::SomeEARSObject

#include <cstdint>

// Reconstructed constructor for an EARS engine object with multiple vtables.
// Address: 0x00686680
// Calls base initializer at 0x008b2820 and optionally deletion registration via FUN_0043b960.
// The object layout:
//   +0x00: primary vtable pointer (PTR_FUN_00d5899c)
//   +0x3C: secondary vtable pointer (PTR_LAB_00d5898c)
//   +0x48: tertiary vtable pointer (PTR_LAB_00d58988)
// The base initializer likely sets up EARSObject common fields.

class SomeEARSObject {
public:
    void** vtable;     // +0x00
    // ... other fields up to offset 0x3C
    void** vtable2;    // +0x3C
    // ... fields up to offset 0x48
    void** vtable3;    // +0x48
    // ... rest of object

    // Constructor with heap flag. If (isHeapAllocated & 1) then register for deletion.
    // Typically called from operator new or placement new.
    // param_1 is this, param_2 is a byte flag (often 0 for stack, 1 for heap).
    static void __thiscall constructor(SomeEARSObject* this_, uint8_t isHeapAllocated) {
        // Set vtables
        this_->vtable = &PTR_FUN_00d5899c;   // primary vtable
        this_->vtable2 = &PTR_LAB_00d5898c;  // secondary vtable (likely interface)
        this_->vtable3 = &PTR_LAB_00d58988;  // tertiary vtable (another interface)

        // Call base class initializer (likely EARSObject::init or similar)
        // This function sets up basic fields, ref counting, etc.
        FUN_008b2820();

        // If the object was allocated on the heap, register it with the memory manager
        // for automatic cleanup or debug tracking.
        if (isHeapAllocated & 1) {
            FUN_0043b960(this_, 0x68);  // size = 0x68 bytes (104 bytes)
        }
    }
};

// External functions referenced:
void FUN_008b2820(); // Base initializer (likely EARSObject::init)
void FUN_0043b960(void* ptr, uint32_t size); // Heap registration (often operator delete or memory tracking)