// FUNC_NAME: PlayerController::initCrewComponent
int __fastcall PlayerController::initCrewComponent(int thisPtr)
{
    // Check if crew component pointer at +0x160 is valid
    if (*(int*)(thisPtr + 0x160) != 0)
    {
        // Allocate two sub-objects (likely weapon/skills)
        int* pSubObj1 = (int*)__alloc();   // FUN_00471610
        int* pSubObj2 = (int*)__alloc();
        if (pSubObj1 && pSubObj2)
        {
            // Stack descriptor for registration
            Descriptor desc;
            desc.pFuncTable = &g_FuncTableRef;          // PTR_FUN_00d813b0
            desc.globalData = g_GlobalData;              // DAT_00d813c8
            desc.flag1 = 1;                              // local_4
            desc.flag2 = 0;                              // local_3
            desc.field_0x4 = 0;                          // local_30..local_28 etc.
            // ... remaining fields zeroed

            // Link sub-objects: pSubObj1+0x30, pSubObj2+0x20, 0
            FUN_008f8430(pSubObj1 + 0x30 / sizeof(int), pSubObj2 + 0x20 / sizeof(int), 0);
            // Register descriptor with subsystem
            FUN_005fcf80(pSubObj1 + 0x30 / sizeof(int), &desc, g_RegistrationKey);
        }
    }
    return 0;   // Always returns 0 (success)
}