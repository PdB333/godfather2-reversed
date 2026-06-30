// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x006cc2a0
// Destructor for an object with multiple inheritance (vtables at +0x0, +0x3C, +0x48, +0x50)
// and two subobjects at offsets +0x78 and +0x80 that are conditionally destroyed.

#include <cstddef>

// External helper functions and vtable pointers
extern void destroySubObject(void* ptr);          // FUN_004daf90
extern void baseClassDestructor();                // FUN_00473880
extern int PTR_FUN_00d5f134;
extern int PTR_LAB_00d5f124;
extern int PTR_LAB_00d5f120;
extern int PTR_LAB_00d5f11c;

class SomeClass {
public:
    // +0x00: primary vtable
    // +0x3C: secondary vtable (interface A)
    // +0x48: secondary vtable (interface B)
    // +0x50: secondary vtable (interface C)
    // +0x78: subobject A (owned, non-null implies initialized)
    // +0x80: subobject B (owned, non-null implies initialized)

    void __fastcall ~SomeClass();  // destructor defined below
};

void __fastcall SomeClass::~SomeClass() {
    // Restore base class vtables for safe destruction of derived parts
    *(int*)this = (int)&PTR_FUN_00d5f134;
    *(int*)((char*)this + 0x3C) = (int)&PTR_LAB_00d5f124;
    *(int*)((char*)this + 0x48) = (int)&PTR_LAB_00d5f120;
    *(int*)((char*)this + 0x50) = (int)&PTR_LAB_00d5f11c;

    // Destroy subobject at offset +0x80 if it exists
    if (*(int*)((char*)this + 0x80) != 0) {
        destroySubObject((void*)((char*)this + 0x80));
    }
    // Destroy subobject at offset +0x78 if it exists
    if (*(int*)((char*)this + 0x78) != 0) {
        destroySubObject((void*)((char*)this + 0x78));
    }

    // Chain to base class destructor
    baseClassDestructor();
}