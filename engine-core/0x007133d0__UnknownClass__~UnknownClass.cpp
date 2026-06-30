// FUNC_NAME: UnknownClass::~UnknownClass
void __fastcall UnknownClass::~UnknownClass(UnknownClass* thisPtr)
{
    // If the member at offset +4 (thisPtr[1]) is non-null, deallocate it.
    if (thisPtr->memberPtr != 0) {
        // Custom deallocation function (likely operator delete or a memory manager)
        FUN_004daf90(thisPtr->memberPtr);
    }
    // Set the vtable pointer to a sentinel or base vtable stored at global address 0x00e2f0c0
    thisPtr->vtablePtr = (VTableType*)&PTR_LAB_00e2f0c0;
}