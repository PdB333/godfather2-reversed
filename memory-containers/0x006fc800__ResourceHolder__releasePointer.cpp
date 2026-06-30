// FUNC_NAME: ResourceHolder::releasePointer
// Function at 0x006fc800: Releasing a pointer member (likely destructor-like cleanup)
void __fastcall ResourceHolder::releasePointer(int* thisPtr)
{
    // Check if the first member (pointer at offset 0x00) is non-null
    if (*thisPtr != 0)
    {
        // Call the cleanup function (likely deallocation or destructive release)
        // FUN_004daf90 takes the address of the pointer
        FUN_004daf90(thisPtr);
        // Set the pointer to null after release
        *thisPtr = 0;
    }
}