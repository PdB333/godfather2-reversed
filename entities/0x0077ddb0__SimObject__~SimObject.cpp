// FUNC_NAME: SimObject::~SimObject
void __thiscall SimObject::~SimObject(SimObject* this)
{
    int* pData;
    int pParent;

    // If the pointer at offset +0x14 is non-null, compute a related object pointer by subtracting 0x48
    // This is typical for obtaining the containing object from an embedded member pointer
    if (this->field_0x14 == 0) {
        pParent = 0;
    } else {
        pParent = this->field_0x14 - 0x48;
    }
    // Call destructor on the parent or base object
    FUN_0077dd10(pParent);
    pData = &this->field_0x4C;
    // Clear linked list pointers (next/prev) at offsets +0x00 and +0x28
    this->field_0x00 = 0;
    this->field_0x28 = 0;
    // Free dynamically allocated data at offset +0x4C
    if (*pData != 0) {
        FUN_004daf90(pData);
        *pData = 0;
    }
    // Global cleanup (e.g., remove from manager list)
    FUN_0077d880();
    // Clear another pointer at offset +0x48
    this->field_0x48 = 0;
    return;
}