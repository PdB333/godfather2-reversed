// FUNC_NAME: SimNpc::constructor
undefined4* __thiscall SimNpc::constructor(SimNpc* this, int creationFlags)
{
    undefined4 uVar1;
    
    if (creationFlags == 0) {
        uVar1 = 0;
    }
    else {
        uVar1 = FUN_00481610(); // likely memory allocation or resource init
    }
    FUN_0064d390(1,1); // debug/logging call
    this->vtable = &PTR_LAB_00e317dc; // base class vtable (e.g., Entity)
    this->field_0x18 = 0; // offset +0x18: some flag
    FUN_00454a10(uVar1); // base class initializer
    this->field_0x24 = 2; // offset +0x24: type identifier (e.g., NPC type 2)
    this->vtable = &PTR_LAB_00d7e134; // derived class vtable (SimNpc)
    this->innerVtable = &PTR_LAB_00d7e088; // offset +0x28: second vtable for multiple inheritance
    this->callbackFunc = &LAB_008db4b0; // offset +0x30: function pointer (event handler?)
    this->field_0x34 = 0; // offset +0x34: null/zero
    this->subObjectPtr = &this->innerVtable; // offset +0x14: pointer to sub-object (e.g., second base)
    return this;
}