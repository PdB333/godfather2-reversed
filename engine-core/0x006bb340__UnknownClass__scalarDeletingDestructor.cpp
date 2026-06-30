// FUNC_NAME: UnknownClass::scalarDeletingDestructor
int* __thiscall scalarDeletingDestructor(int* thisObj, unsigned char deletingFlags)
{
    // Check if the object was properly constructed (vtable pointer non-null)
    if (*thisObj != 0) {
        // Call the actual destructor
        FUN_004daf90(thisObj);
    }

    // If the deleting flag (bit 0) is set, free the memory
    if ((deletingFlags & 1) != 0) {
        FUN_009c8eb0(thisObj);
    }

    return thisObj;
}