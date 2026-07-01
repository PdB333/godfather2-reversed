// FUNC_NAME: EARS::UIManager::initializeWithData
void __fastcall UIManager::initializeWithData(int param_1)
{
    int *piVar1;
    
    // Call some initialization routine (likely rendering setup)
    FUN_005c1740();
    
    // Fetch vtable pointer from global and set it to PTR_LAB_00e5694c
    piVar1 = (int *)(DAT_01206880 + 0x14);  // +0x14 is likely the vtable pointer offset
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e5694c;
    
    // Increment the pointer and store param_1 (data handle?)
    *piVar1 = *piVar1 + 4;
    *(int *)*piVar1 = param_1;
    
    // Advance pointer again for next slot
    *piVar1 = *piVar1 + 4;
    
    // If global context exists (DAT_0112fe64), copy data at offset +0x50 from param_1 into it
    if (DAT_0112fe64 != 0) {
        // Copy 0x8000 bytes from param_1+0x50 to the global data area
        FUN_00408900(param_1 + 0x50, &DAT_0112fe64, 0x8000);
    }
    
    return;
}