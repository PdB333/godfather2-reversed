// FUNC_NAME: SomeClass::Constructor
// Address: 0x007ee020
// __thiscall constructor, param_2 flag indicates whether memory was allocated by operator new (1) or not (0)
// VTable set to PTR_FUN_00d70000, then calls base/init functions

class SomeClass {
public:
    void** vtable; // +0x00 vtable pointer
    int field_4;   // +0x04
    int field_8;   // +0x08
    int field_C;   // +0x0C
    int field_10;  // +0x10
    int field_14;  // +0x14
    int field_18;  // +0x18
    void* field_1C; // +0x1C - passed to FUN_009c8f10
    // ... other fields

    void* operator new(size_t size);
    void operator delete(void* ptr);
};

// External functions called
void __cdecl FUN_004086d0(void* globalData); // likely increment/decrement global reference, &DAT_012069c4
void __cdecl FUN_009c8f10(void* ptr);        // some initialization on field at +0x1C
void __cdecl FUN_004083d0(void);             // some static initialization

// This function is the constructor
SomeClass* __thiscall SomeClass::Constructor(SomeClass* this, byte flag) {
    // Set vtable
    this->vtable = &PTR_FUN_00d70000;

    // Call some global reference function
    FUN_004086d0(&DAT_012069c4);

    // Initialize subobject at offset +0x1C
    FUN_009c8f10(this->field_1C);

    // Perform other initialization
    FUN_004083d0();

    // If the flag indicates memory was allocated by operator new (bit 0),
    // then the caller expects that if construction fails, we must delete.
    // Here we always succeed, so this is a no-op (but might be a placeholder).
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this); // likely operator delete or destructor
    }

    return this;
}