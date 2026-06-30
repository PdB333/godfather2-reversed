// FUNC_NAME: SomeClass::releaseChildResource
void __fastcall SomeClass::releaseChildResource(int thisPtr) {
    // +0x19c: pointer to a child resource (e.g., asset, object)
    if (*(int *)(thisPtr + 0x19c) != 0) {
        // Call function to release/deallocate the resource
        FUN_0094b0e0(*(int *)(thisPtr + 0x19c));
        // Clear pointer to avoid dangling reference
        *(int *)(thisPtr + 0x19c) = 0;
    }
}