// FUNC_NAME: cleanupRefCountedObject
void __fastcall cleanupRefCountedObject(int* param_1)
{
    // Check if there's a secondary object at offset +0x10
    if (param_1[4] != 0) {
        // Release the secondary object (likely a custom deallocator)
        FUN_004daf90(param_1 + 4);
    }
    // Check if primary object pointer at offset +0x0 is valid
    if (*param_1 != 0) {
        // Call the destructor/releaser function stored at offset +0x0C
        (*(void (__fastcall*)(int))param_1[3])(*param_1);
    }
}