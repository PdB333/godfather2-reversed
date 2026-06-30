// FUNC_NAME: BaseObject::BaseObject
void __thiscall BaseObject::BaseObject(void) {
    // Initialize members (offsets in bytes from this)
    // +0x10: field4
    this->field4 = 0;
    // +0x14: field5
    this->field5 = 0;
    // +0x04: field1
    this->field1 = 0;
    // +0x08: field2
    this->field2 = 0;
    // +0x0C: field3
    this->field3 = 0;
    // +0x18: field6
    this->field6 = 0;
    // +0x1C: field7
    this->field7 = 0;
    // +0x00: vtable pointer
    this->vtable = (void**)(&PTR_FUN_00e3f0b4);
    // +0x20: field8
    this->field8 = 0;
    // +0x24: field9
    this->field9 = 0;

    // Compute an index based on this pointer (likely for seeding or allocation)
    uint modulo = (uint)this % *(uint *)(*(int *)(DAT_01223398 + 4) + 8);
    FUN_00423cf0(&localVar1, &localVar2, modulo);
    return;
}