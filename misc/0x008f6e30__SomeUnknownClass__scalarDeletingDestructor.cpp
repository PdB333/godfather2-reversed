// FUNC_NAME: SomeUnknownClass::scalarDeletingDestructor
int* __thiscall SomeUnknownClass::scalarDeletingDestructor(int* thisPtr, byte flags)
{
    if (*thisPtr != 0) {
        releaseResource(*thisPtr);
    }
    if ((flags & 1) != 0) {
        operatorDelete(thisPtr);
    }
    return thisPtr;
}