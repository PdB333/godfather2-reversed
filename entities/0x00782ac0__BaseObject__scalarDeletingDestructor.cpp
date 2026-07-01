// FUNC_NAME: BaseObject::scalarDeletingDestructor

int* BaseObject::scalarDeletingDestructor(int* thisPtr, byte flags)
{
    // If the object's vtable pointer is non-null, call the actual destructor
    if (*thisPtr != 0) {
        BaseObject::destructor(thisPtr); // FUN_004daf90
    }
    // If the low bit of flags is set, free the memory (operator delete)
    if ((flags & 1) != 0) {
        operatorDelete(thisPtr); // FUN_009c8eb0
    }
    return thisPtr;
}