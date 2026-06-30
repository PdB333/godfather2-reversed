// FUNC_NAME: BaseObject::constructor

struct BaseObject;

void __thiscall baseInit(int param_2); // FUN_0046c590

BaseObject* __thiscall BaseObject::constructor(BaseObject* this, int param_2)
{
    baseInit(param_2); // call base class constructor
    this->vtable = &PTR_FUN_00e333b8; // +0x00
    this->field_0x3c = &PTR_LAB_00e333d4; // +0x3c, possibly type descriptor or secondary vtable
    this->field_0x48 = &PTR_LAB_00e333e4; // +0x48
    this->field_0x50 = 0; // +0x50
    *(unsigned short*)((uint)this + 0x54) = 0; // +0x54
    *(unsigned short*)((uint)this + 0x56) = 0; // +0x56
    this->field_0x58 = 0; // +0x58
    this->field_0x5c = 0; // +0x5c
    return this;
}