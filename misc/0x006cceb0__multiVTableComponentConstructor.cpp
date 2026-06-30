// FUNC_NAME: multiVTableComponentConstructor
// Function address: 0x006cceb0
// Role: Constructor for a class with multiple vtables (offsets 0, 0x3C, 0x48) and a base class call.
// Class size likely 0x50 bytes (80 bytes) based on deallocation argument.
// Calls base constructor at 0x46c640, and if allocFlag bit 0 is set, calls custom deallocation at 0x43b960.

extern void* PTR_FUN_00d5f100;   // Primary vtable at +0x00
extern void* PTR_LAB_00d5f0f0;   // Secondary vtable at +0x3C
extern void* PTR_LAB_00d5f0ec;   // Tertiary vtable at +0x48

void __cdecl baseClassConstructor(); // FUN_0046c640 - base class initialization
void __cdecl customDealloc(void* ptr, unsigned int size); // FUN_0043b960 - custom deallocation

class MultiVTableObject {
public:
    // +0x00: vtable pointer (primary)
    // +0x3C: vtable pointer for second base class interface
    // +0x48: vtable pointer for third base class interface
    // Size: 0x50 (80 bytes)

    __thiscall MultiVTableObject(unsigned char allocFlag) {
        // Set up vtables for multiple inheritance
        *(void**)this = &PTR_FUN_00d5f100;          // Set primary vtable at offset 0
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00d5f0f0; // Set secondary vtable at +0x3C
        *(void**)((char*)this + 0x48) = &PTR_LAB_00d5f0ec; // Set tertiary vtable at +0x48

        // Call base class constructor (likely initializes base portion)
        baseClassConstructor();

        // If allocation flag indicates memory was dynamically allocated (bit 0 set),
        // call a custom cleanup/deallocation function (e.g., for exception handling).
        if (allocFlag & 1) {
            customDealloc(this, 0x50); // Size matches class size
        }
    }
};