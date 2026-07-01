// FUNC_NAME: EARSObject::EARSObject
// Address: 0x008eb2d0 - Constructor for EARSObject, calls internal init and returns this pointer.

void* __fastcall EARSObject::EARSObject(void* thisPointer)
{
    // Call internal initialization function (address 0x008ea610)
    FUN_008ea610();
    return thisPointer;
}