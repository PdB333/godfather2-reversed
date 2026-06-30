// FUNC_NAME: SomeClass::releasePointer
void __thiscall SomeClass::releasePointer(int *pResource)
{
    // Check if the resource handle is non-zero
    if (*pResource != 0) {
        // Release the underlying resource (likely a handle or pointer)
        releaseResource(pResource);
        // Invalidate the handle to prevent double release
        *pResource = 0;
    }
}