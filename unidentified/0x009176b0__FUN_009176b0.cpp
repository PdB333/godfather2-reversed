// FUNC_NAME: SomeClass::releaseResource
void __fastcall SomeClass::releaseResource(int *thisPtr) // +0x00: resource pointer, +0x04: refCount, +0x08: stateFlags
{
    // Reset refCount (or secondary handle)
    thisPtr[1] = 0;

    // Call release on the resource (e.g., decrement ref count, free)
    FUN_009c8f10(thisPtr[0]);

    // Clear resource pointer
    thisPtr[0] = 0;

    // Reset state flags
    thisPtr[2] = 0;
}