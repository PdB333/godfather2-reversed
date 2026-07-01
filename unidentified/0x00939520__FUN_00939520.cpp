// FUNC_NAME: SomeComponent::copyManagerData
void __fastcall SomeComponent::copyManagerData(void* thisPtr)
{
    // Call to global singleton accessor (likely returns a manager instance pointer, e.g., PlayerManager, InputManager, etc.)
    int iVar1 = getGlobalPointer(); // FUN_007351c0
    if (iVar1 != 0) {
        // Re-fetch the singleton pointer (same accessor)
        iVar1 = getGlobalPointer(); // FUN_007351c0
        // Copy a 4-byte value from offset +0xc4 of the singleton to offset +0x70 of this object
        *(int *)((char *)thisPtr + 0x70) = *(int *)((char *)iVar1 + 0xc4);
    }
    return;
}