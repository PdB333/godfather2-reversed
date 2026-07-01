// FUNC_NAME: ResourceHolder::releaseAndDelete
int* __thiscall ResourceHolder::releaseAndDelete(int* thisPtr, byte deleteFlag)
{
    // If the managed resource pointer (at offset 0x00) is non-null,
    // call the release function stored at offset 0x0C (thisPtr[3]).
    if (*thisPtr != 0) {
        (*(void (__cdecl*)(int*))*)(thisPtr[3]))(*thisPtr);
    }

    // If the delete flag's lowest bit is set, deallocate this object.
    if ((deleteFlag & 1) != 0) {
        operatorDelete(thisPtr);  // FUN_009c8eb0
    }

    return thisPtr;
}