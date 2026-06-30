// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject* this, EARSObject** parentHandle)
// this in ESI, parentHandle in EAX (pointer to handle of parent object)
{
    int* parentObject;
    int* globalDefault; // from DAT_00e2b1a4

    globalDefault = (int*)DAT_00e2b1a4; // likely a "null" or default handle

    // Set vtable pointer (offset 0x00)
    this->vtable = &PTR_FUN_00e37930;

    // Initialize fields
    this->field_04 = 0;          // offset 0x04
    this->field_10 = globalDefault; // offset 0x10
    this->field_14 = globalDefault; // offset 0x14
    this->field_18 = globalDefault; // offset 0x18
    this->field_1C = globalDefault; // offset 0x1C
    this->field_20 = 0;          // offset 0x20
    this->field_24 = 0;          // offset 0x24
    this->field_28 = 0;          // offset 0x28
    this->field_2C = globalDefault; // offset 0x2C
    this->field_30 = globalDefault; // offset 0x30
    this->field_34 = globalDefault; // offset 0x34
    this->field_38 = 0;          // offset 0x38

    // Dereference parentHandle to get the parent object pointer
    parentObject = (int*)*parentHandle;
    if (parentObject != 0) {
        // Increment reference count at offset 0x04 of parent object
        *(int*)((char*)parentObject + 4) += 1;
    }

    // Call initialization function with parent object
    FUN_00509350(parentObject);
}