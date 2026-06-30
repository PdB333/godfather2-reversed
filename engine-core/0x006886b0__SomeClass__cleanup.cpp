// FUNC_NAME: SomeClass::cleanup
void __thiscall SomeClass::cleanup(int thisPtr)
{
    // Offset +0x140: pointer to a resource (likely an allocated object or handle)
    int* pSomeResource = (int*)(thisPtr + 0x140);
    if (*pSomeResource != 0) {
        // Release the resource (e.g., delete object, free memory, close handle)
        releaseResource(pSomeResource);
    }
    // Perform global shutdown/cleanup routine
    shutdownSystem();
    return;
}