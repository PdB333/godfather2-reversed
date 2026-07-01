// FUNC_NAME: SomeClass::cleanup
void __fastcall SomeClass::cleanup(int thisPtr)
{
    // +0x20: pointer to some resource (e.g., audio stream, animation)
    if (*(int *)(thisPtr + 0x20) != 0) {
        FUN_009e7530(*(int *)(thisPtr + 0x20)); // likely operator delete or release
        FUN_009f01a0(); // likely global cleanup or shutdown
    }
    // +0x4: pointer to first sub-object (e.g., component)
    if (*(int *)(thisPtr + 4) != 0) {
        FUN_009c8f10(*(int *)(thisPtr + 4)); // release sub-object
    }
    // +0x8: pointer to second sub-object
    if (*(int *)(thisPtr + 8) != 0) {
        FUN_009c8f10(*(int *)(thisPtr + 8)); // release sub-object
    }
}