// FUNC_NAME: EARSObject::baseConstructor
// Address: 0x00598de0
// Role: Sets the vtable pointer for the base object (constructor stub)

class EARSObject {
public:
    void* vtable; // +0x00 (vtable pointer)
};

void __thiscall EARSObject::baseConstructor() {
    // Assign the vtable pointer to the constant address 0x00e3b030.
    // This is called during construction of objects derived from EARSObject.
    this->vtable = (void*)0x00e3b030;
}