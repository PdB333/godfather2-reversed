// FUNC_NAME: UnknownClass::constructor
// Address: 0x00906090

class UnknownClass {
public:
    // Vtable pointers (multiple inheritance)
    void* vtable0;                // +0x00
    char pad_0x04[0x0E * 4];     // +0x04 to +0x38 (padding)
    void* vtable1;                // +0x3C (offset 0x0F)
    void* vtable2;                // +0x48 (offset 0x12)
    void* vtable3;                // +0x50 (offset 0x14)
    // Sub-object at +0x58 (offset 0x16)
    char subObject[0x08];         // +0x58 (size unknown, but likely 8 bytes)

    // Constructor function (matches __thiscall returning this)
    __thiscall UnknownClass* constructor(byte flags);
};

// Sub-object type with constructor and init methods
struct SubObject {
    void __thiscall constructor();   // FUN_004086d0
    void __thiscall init();         // FUN_00408310
};

// Constructor implementation
__thiscall UnknownClass* UnknownClass::constructor(byte flags) {
    // Set vtable pointers for base classes
    vtable0 = (void*)0x00d826c8;
    vtable1 = (void*)0x00d826b8;
    vtable2 = (void*)0x00d826b4;
    vtable3 = (void*)0x00d826b0;

    // Construct sub-object at offset 0x58
    SubObject* sub = reinterpret_cast<SubObject*>(&subObject);
    sub->constructor();   // FUN_004086d0
    sub->init();          // FUN_00408310

    // Override last vtable pointer
    vtable3 = (void*)0x00e32854;

    // Global initialization
    FUN_0046c640(); // EA::someGlobalInit() or similar

    // Handle heap allocation flag
    if ((flags & 1) != 0) {
        FUN_0043b960(static_cast<void*>(this), 0x60); // operator delete(this, size)
    }

    return this;
}