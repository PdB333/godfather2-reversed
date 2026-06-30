// FUNC_NAME: UnknownClass::constructor
// Function address: 0x006b7790 (constructor for some class)
// Sets up vtables and calls base or member constructors, conditionally frees memory if param_2 & 1

class UnknownClass {
public:
    // Vtable pointer at offset 0
    // Additional vtable pointers at offsets 0x3C and 0x48

    // Constructor
    // param_2: bit 0 indicates whether to call a memory deallocation (e.g., on allocation failure?)
    __thiscall UnknownClass(byte param_2) {
        // Set primary vtable
        *this = &PTR_FUN_00d5e558;  // +0x00: Primary vtable

        // Set secondary vtable at offset 0x3C
        *(void**)((int)this + 0x3C) = &PTR_LAB_00d5e548;  // +0x3C: Secondary vtable

        // Set another vtable at offset 0x48
        *(void**)((int)this + 0x48) = &PTR_LAB_00d5e544;  // +0x48: Another vtable

        // Call base class or global initialization
        FUN_004086d0(&DAT_0120e93c);  // Likely singleton or static initializer

        // Another initialization call
        FUN_0046c640();  // Possibly increments reference count or similar

        // If param_2 bit 0 set, call memory deallocation with size 0xB0
        if ((param_2 & 1) != 0) {
            // This might be operator delete(this, 0xB0) or custom dealloc
            FUN_0043b960(this, 0xB0);
        }

        return this;
    }
};