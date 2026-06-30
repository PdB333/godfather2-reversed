// FUN_004558f0: EARSObject::EARSObject(bool deleteOnAlloc)
// Constructor for a class with a virtual function table. Pattern suggests virtual inheritance (with VBTable pointer at +12).
// Sets global initialized flag to 0.

class EARSObject {
public:
    // Vtable pointer at +0x00
    // +0x04: unknown
    // +0x08: base class vtable pointer (or VBTable?)
    // +0x0C: another pointer (possibly to a virtual base table, used for delegated constructor call)

    void* vtable;
    // ... other members
};

// Global variable: indicates whether engine has been initialized
int g_EngineInitialized; // DAT_01223450 (set to 0 in constructor)

// Forward declarations
void __cdecl sub_49C640();   // FUN_0049c640 – likely base class initializer
void __cdecl sub_9C8EB0(EARSObject* obj); // FUN_009c8eb0 – likely operator delete

// Constructor: if deleteOnAlloc is true (bit 0 of param_2), calls operator delete on failure (unusual – could be a placement new with cleanup)
// Returns pointer to constructed object (this, passed in ECX)
void* __thiscall EARSObject::EARSObject(EARSObject* this, bool deleteOnAlloc) {
    // Set vtable pointer for this class (derived vtable)
    this->vtable = (void*)0x00e31970;  // PTR_FUN_00e31970

    // Set base class vtable pointer (at +8)
    *(void**)((char*)this + 8) = (void*)0x00e3197c; // PTR_LAB_00e3197c

    // Call a virtual function through the VBTable (at +0xC) offset 0xC
    // This is typical for calling a base constructor in virtual inheritance.
    // The VBTable pointer must be set before this call.
    void* vbTable = *(void**)((char*)this + 0xC);
    typedef void (__thiscall *BaseConstructorFunc)(void*);
    BaseConstructorFunc baseCtor = (BaseConstructorFunc)(*(void**)((int*)vbTable + 3)); // +0xC / 4 = 3
    baseCtor(this);

    // Update base class vtable pointer to a different vtable (derived's base part)
    *(void**)((char*)this + 8) = (void*)0x00e31980; // PTR_LAB_00e31980

    // Reset global engine initialization flag
    g_EngineInitialized = 0;

    // Call additional initialization function
    sub_49C640();

    // If deleteOnAlloc is set (bit 0 of flag), deallocate the object
    if (deleteOnAlloc) {
        sub_9C8EB0(this);
    }

    return this;
}