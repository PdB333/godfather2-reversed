// FUNC_NAME: SomeClass::Destructor
void __fastcall SomeClass::Destructor(int thisPtr)
{
    // local buffer, possibly for stack alignment or temporary storage
    char localBuf[8];

    // Call internal cleanup function with various parameters derived from this pointer
    // The third argument: **(int**)(thisPtr + 0x4)  -- double dereference of member at +0x4
    // The fifth argument: *(int**)(thisPtr + 0x4)   -- single dereference
    FUN_00695e30(localBuf, thisPtr, **(int**)(thisPtr + 0x4), thisPtr, *(int**)(thisPtr + 0x4));

    // Deallocate the memory pointed to by the member at offset +0x4
    FUN_009c8eb0(*(void**)(thisPtr + 0x4));

    // Reset both pointer members to null
    *(int*)(thisPtr + 0x4) = 0;  // +0x4: formerly allocated memory pointer
    *(int*)(thisPtr + 0x8) = 0;  // +0x8: second pointer (e.g., handle or other resource)

    return;
}