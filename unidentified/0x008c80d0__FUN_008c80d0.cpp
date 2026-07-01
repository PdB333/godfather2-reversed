// FUNC_NAME: SomeClass::setSomePointer
void __thiscall SomeClass::setSomePointer(int thisPtr, int param2)
{
    // +0x18: pointer field
    *(int *)(thisPtr + 0x18) = param2;
    
    // Call some function on param2 (likely a reference count or initialization)
    FUN_00790d30(param2);
    
    // +0x10: another pointer field
    if (*(int *)(thisPtr + 0x10) != 0) {
        // +0x58: check if the object at +0x10 has a matching pointer
        if (*(int *)(*(int *)(thisPtr + 0x10) + 0x58) == param2) {
            FUN_008feb40(); // Handle case where pointer matches
            return;
        }
        FUN_008febb0(); // Handle case where pointer doesn't match
    }
    return;
}