// FUNC_NAME: PointerHolder::releasePointer
void __fastcall PointerHolder::releasePointer(int* thisPtr)
{
    // Check if the pointer stored at offset 0 is non-null
    if (*thisPtr != 0) {
        // Call the actual deallocation/cleanup routine
        deallocateResource(); // FUN_004deb80
    }
}