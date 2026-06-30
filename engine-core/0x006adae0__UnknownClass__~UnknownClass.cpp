// FUNC_NAME: UnknownClass::~UnknownClass
// Destructor for an unknown class at address 0x006adae0.
// The object has a vtable pointer at offset 0, and an embedded sub-object at offset 8.
// If the sub-object pointer is non-null, its destructor (FUN_004daf90) is called.
// Then the vtable is set to the global pointer at 0x00e2f0c0.
// If the destroyFlag (param_2 & 1) is set, operator delete (FUN_009c8eb0) is called.

class UnknownClass {
public:
    void* vtable;                     // +0x00
    // ... other members ...
    EmbeddedObject* subObjAtOffset8;  // +0x08 (assumed pointer, but could be embedded object)
    // ...
};

// Forward declaration of the sub-object's destructor
void __thiscall EmbeddedObjectDestructor(void* thisPtr); // FUN_004daf90

// Forward declaration of operator delete (possibly global)
void __fastcall OperatorDelete(void* ptr); // FUN_009c8eb0 (likely __fastcall with ECX? we assume)

__thiscall UnknownClass::~UnknownClass(UnknownClass* this, byte destroyFlag) {
    if (this->subObjAtOffset8 != 0) {
        EmbeddedObjectDestructor(this->subObjAtOffset8); // destroy embedded sub-object
    }
    // Set vtable to the class's default vtable (likely for the base class)
    this->vtable = (void*)0x00e2f0c0;
    if ((destroyFlag & 1) != 0) {
        // Free memory if the destroy flag indicates heap allocation
        OperatorDelete(this);
    }
    return this;
}