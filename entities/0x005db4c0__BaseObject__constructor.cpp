// FUNC_NAME: BaseObject::constructor
void __thiscall BaseObject::constructor(BaseObject *this)
{
    uint localVar1; // output parameter for pool registration
    uint localVar2; // output parameter for pool registration

    // Zero out member fields (offsets in bytes: +0x04 to +0x24)
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;
    this->field_0x20 = 0;
    this->field_0x24 = 0;

    // Set vtable pointer
    this->vtable = &BaseObject_vtable; // +0x00

    // Compute pool slot index from the object's address modulo a global pool size
    // Global pool table at g_globalPoolTable + 4 -> deref +8 gives the array size
    int poolIndex = ((uint)this) % *(uint *)(*(int *)(g_globalPoolTable + 4) + 8);

    // Register this object in the pool at the calculated index
    FUN_00423cf0(&localVar1, &localVar2, poolIndex);
}