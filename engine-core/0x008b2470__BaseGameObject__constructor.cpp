// FUNC_NAME: BaseGameObject::constructor
// Address: 0x008b2470
// Role: Constructor that initializes vtable pointers and calls a base initialization function.

// Reconstructed C++ code
BaseGameObject* __thiscall BaseGameObject::constructor(BaseGameObject* this, uint32_t initParam)
{
    // Call base class constructor or initialization function with initParam
    ::baseConstructor(initParam);

    // Set primary vtable pointer (offset +0x00)
    this->vftable = &PTR_FUN_00d7ac74;

    // Set secondary vtable pointer for interface A (offset +0x3C)
    this->interfaceAVtable = &PTR_LAB_00d7ac64;

    // Set secondary vtable pointer for interface B (offset +0x48)
    this->interfaceBVtable = &PTR_LAB_00d7ac60;

    return this;
}