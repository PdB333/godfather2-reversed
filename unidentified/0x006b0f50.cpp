// FUN_NAME: UnknownClass::getObjectData
// Address: 0x006b0f50
// Returns a pointer at offset 0x40 from the resolved object.
// If resolution fails, returns NULL.
void* __thiscall UnknownClass::getObjectData(void* param_1)
{
    void* resolved = FUN_006b0ee0(param_1); // resolves param_1 to a base object
    if (resolved != 0) {
        return *(void**)((char*)resolved + 0x40); // +0x40: pointer to data block
    }
    return 0;
}