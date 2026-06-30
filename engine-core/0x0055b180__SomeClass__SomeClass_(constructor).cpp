// FUNC_NAME: SomeClass::SomeClass (constructor)
// Function address: 0x0055b180
// Thought to be a constructor that calls an initialization function and optionally
// invokes a virtual function (likely destructor at vtable index 1) based on a flag.
// The virtual function pointer is obtained from a global: *(int**)(DAT_01223410 + 0x2d4) + 4.
// This pattern is typical of EA EARS engine constructors that handle both construction
// and copy/placement semantics.

#include <cstdint>

// Forward declaration of the initialization function; known address 0x0055b1d0
void SOMECLASS_init(SomeClass* this_ptr);

class SomeClass {
public:
    // Constructor: param2 is a byte flag (e.g., flags for copy or placement)
    __thiscall SomeClass(uint8_t flags) {
        // Call the underlying initialization routine
        SOMECLASS_init(this);

        // If the lowest bit is set, invoke a virtual function at vtable slot 1
        // (commonly the scalar deleting destructor with argument 0)
        if (flags & 1) {
            // Use a global vtable pointer stored at DAT_01223410 + 0x2d4
            // The function pointer is at offset 4 (i.e., index 1)
            // Typical signature: void (__thiscall*)(void*, int)
            typedef void (__thiscall *VirtFunc)(void*, int);
            VirtFunc vf = *reinterpret_cast<VirtFunc*>(
                *reinterpret_cast<int**>(DAT_01223410 + 0x2d4) + 1
            );
            vf(this, 0);
        }
    }

private:
    // Virtual table pointer, etc. (layout unknown)
};

// Static declaration for the global reference (address 0x01223410)
// This likely holds a pointer to a class or vtable for SomeClass.
// The offset 0x2d4 within that data yields the actual vtable pointer.
extern uintptr_t DAT_01223410;