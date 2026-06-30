// FUNC_NAME: SomeClass::cleanupRecursive
void __fastcall cleanupRecursive(int thisPtr)
{
    // Offset +0x20: pointer to child object (may be null)
    int* childPtr = *(int**)(thisPtr + 0x20);
    if (childPtr != nullptr) {
        // Recursively clean up the child subtree
        cleanupRecursive(childPtr);
        // Free the child's memory (likely operator delete or custom deallocator)
        FUN_009c8eb0(childPtr);
    }
}