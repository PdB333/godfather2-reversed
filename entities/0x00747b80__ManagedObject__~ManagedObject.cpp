// FUNC_NAME: ManagedObject::~ManagedObject
void __thiscall ManagedObject::~ManagedObject(ManagedObject* this) {
    // Offset +0x00: vtable pointer, set to base vtable (DAT_00d5ccf8)
    this->vtable = DAT_00d5ccf8;
    // Offset +0x04: some flag set to 0
    this->someFlag = 0;

    // Offset +0x08: pointer to resource 1 (piVar1 = &this->resource1)
    int* pResource1 = &this->resource1;
    if (*pResource1 != 0) {
        // Release resource 1 (likely free or delete)
        FUN_004daf90(pResource1);
        *pResource1 = 0;
    }

    // Offset +0x14: some integer set to 0
    this->field_20 = 0;

    // Offset +0x10: pointer to resource 2
    FUN_009c8f10(this->resource2);
    this->resource2 = 0;

    // Offset +0x18: another integer set to 0
    this->field_24 = 0;
}