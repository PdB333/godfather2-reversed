// FUNC_NAME: SomeClass::constructor
// Reconstructed constructor at 0x0086b1e0
// Sets vtable, then calls a virtual method on a subobject (+0x14)
// Based on the result, may call a static error handler
// Then calls a static init routine
// Finally, if param_2 & 1, calls a deallocation function

class SomeClass {
public:
    void* vtable;              // +0x00
    SomeSubObject* m_pSubObj;  // +0x14
    // ... other members
};

class SomeSubObject {
public:
    void* vtable;  // +0x00
    // ... other members
};

static void handleError(int code);       // FUN_0086b810
static void initStaticContext();         // FUN_0086aff0
static void destroyStaticDealloc(SomeClass* obj); // FUN_00624da0

void __thiscall SomeClass::constructor(byte flag) {
    this->vtable = (void*)&PTR_LAB_00d75d54; // set vtable pointer
    SomeSubObject* sub = this->m_pSubObj;

    // Call virtual method at offset 0x24 from subobject's vtable
    // (index 9, assuming 4-byte pointers)
    typedef int (__thiscall *SubMethod)(SomeSubObject*);
    SubMethod method = *(SubMethod*)(*(int*)sub + 0x24);
    if (method(sub) != 0) {
        handleError(0);
    }

    initStaticContext();

    if ((flag & 1) != 0) {
        destroyStaticDealloc(this);
    }

    return;
}