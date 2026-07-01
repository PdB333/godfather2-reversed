// FUNC_NAME: SomeClass::SomeClass
// Address: 0x008ab500
// Role: Constructor for a class with multiple inheritance (two vtable pointers)
// Calls base constructor at 0x004bc3f0, sets vtable pointers at offsets 0x00 and 0x10,
// and optionally calls a cleanup/destructor function at 0x009c8eb0 if param_2 & 1 is set.

class SomeClass : public BaseClass {
public:
    // Vtable pointers (offset 0x00 and 0x10)
    void** vtable1;  // +0x00
    void** vtable2;  // +0x10

    // Constructor: param_2 is a flag (bit 0 indicates whether to call cleanup)
    __thiscall SomeClass(byte param_2) {
        // Call base class constructor
        BaseClass::BaseClass();

        // Set vtable pointers
        this->vtable1 = &PTR_LAB_00e317cc;  // +0x00
        this->vtable2 = &PTR_LAB_00e35c24;  // +0x10

        // If the low bit of param_2 is set, call cleanup function (likely destructor or deallocation)
        if ((param_2 & 1) != 0) {
            FUN_009c8eb0(this);  // Cleanup function (e.g., operator delete or destructor)
        }
    }
};