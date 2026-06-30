// FUNC_NAME: EARSObject::EARSObject

struct EARSObject {
    void* vtable; // +0x00
};

struct BaseEARSObject : EARSObject {
    // base class fields follow
};

void __thiscall EARSObject::EARSObject(EARSObject* this)
{
    // Set vtable to base class vtable before calling base constructor
    this->vtable = (void*)0x00e327d8;
    // Call base constructor (address 0x0043e380)
    BaseEARSObject::BaseEARSObject((BaseEARSObject*)this);
    // Reset vtable to derived class vtable after base construction
    this->vtable = (void*)0x00e30ea0;
    return;
}