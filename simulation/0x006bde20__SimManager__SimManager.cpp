// FUNC_NAME: SimManager::SimManager
void __thiscall SimManager::SimManager(void* thisPtr)
{
    // Set vtable at object base (+0x00)
    *(DWORD*)thisPtr = &PTR_FUN_00d5eaec;
    // Set function table at offset +0x3C (0xF * 4)
    *(DWORD*)((BYTE*)thisPtr + 0x3C) = &PTR_LAB_00d5eadc;
    // Set function table at offset +0x48 (0x12 * 4)
    *(DWORD*)((BYTE*)thisPtr + 0x48) = &PTR_LAB_00d5ead8;
    // Initialize sub-object at offset +0x20 (likely embedded member)
    void* subObj = (void*)((BYTE*)thisPtr + 0x20);
    FUN_004086d0(subObj);  // sub-object constructor or init
    FUN_00408310(subObj);  // sub-object finalize
    // Global singleton/manager initialization
    FUN_006bcd70();
}