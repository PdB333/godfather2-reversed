// FUNC_NAME: EARSBaseObject::EARSBaseObject
// Function address: 0x00475790
// Role: Constructor for a base class with multiple interface vtables. Sets up six vtable pointers then calls a sub-constructor.
// If the flag (param_2) has bit 0 set, invokes a destructor-like function (likely for deallocation after placement new).

#include <cstddef>

class EARSBaseObject {
public:
    void *vtable;                          // +0x00: main vtable pointer
    // +0x04 through +0x38: unknown members (size 0x3C total before second vtable)
    void *vtable2;                         // +0x3C (offset 0x0F * 4)
    void *vtable3;                         // +0x48 (offset 0x12 * 4)
    void *vtable4;                         // +0x50 (offset 0x14 * 4)
    void *vtable5;                         // +0x54 (offset 0x15 * 4)
    void *vtable6;                         // +0x58 (offset 0x16 * 4)
    // ... additional members follow

    // Constructor: initializes vtables and calls a base constructor.
    // @param allocDeleteFlag: if bit0 set, triggers deallocation after construction.
    static void * __thiscall constructor(EARSBaseObject *this, byte allocDeleteFlag) {
        this->vtable  = &PTR_FUN_00e32be8;   // main vtable
        this->vtable2 = &PTR_LAB_00e32d34;   // secondary vtable #1
        this->vtable3 = &PTR_LAB_00e32d44;   // #2
        this->vtable4 = &PTR_LAB_00e32d48;   // #3
        this->vtable5 = &PTR_LAB_00e32d50;   // #4
        this->vtable6 = &PTR_LAB_00e32db0;   // #5

        // Call base class constructor (likely sets up more vtables or initializes fields)
        FUN_0046ea20();  // base constructor

        if (allocDeleteFlag & 1) {
            // Deallocate this object using a function pointer from global data.
            // The call is: (*(code **)(*(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
            // Meaning: DAT_01223410 + 0x2d4 points to a vtable-like structure,
            // offset 4 in that table is a destructor/delete function.
            void (*destructor)(void *, int) = 
                (void (*)(void *, int))(*((int **)(DAT_01223410 + 0x2d4))[1]); // [1] is offset 4 in a vtable (assuming 4-byte pointers)
            destructor(this, 0);
        }
        return this;
    }
};