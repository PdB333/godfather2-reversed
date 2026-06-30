// FUNC_NAME: PointerHolder::release
void __fastcall PointerHolder::release(int thisPtr)
{
    // Check if the pointer at +0x8 is non-null
    if (*(int**)(thisPtr + 8) != 0)
    {
        // Clear the first field of the pointed-to object (likely a reference count or back link)
        **(int**)(thisPtr + 8) = 0;
        // Nullify the pointer itself
        *(int*)(thisPtr + 8) = 0;
    }
}