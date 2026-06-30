// FUNC_NAME: GameManager::initializeTableArrays
void __thiscall GameManager::initializeTableArrays(GameManager *this) // fastcall omitted, treat param_1 as this
{
    int *pModuleId1; // offset: this+0x17C
    int *pModuleId2; // offset: this+0x190
    // Global static array of pointers (3-pointer stride); size likely determined by loop end address
    void **ppTable = &PTR_PTR_01128494;

    pModuleId1 = (int *)((char *)this + 0x17C);
    pModuleId2 = (int *)((char *)this + 0x190);

    // Iterate over a table of modules (or plugin entries, each entry 12 bytes)
    while ((int)ppTable < (int)0x1128584) // end address of static table (likely defined by symbol size)
    {
        int id1;
        int id2;

        if (*ppTable == nullptr) {
            id1 = 0;
        } else {
            id1 = FUN_0060a2e0(*ppTable); // get some ID/handle from module pointer
        }
        *pModuleId1 = id1;

        id2 = FUN_0060a380(); // get another ID (global?)
        *pModuleId2 = id2;

        ppTable += 3; // advance by 12 bytes (three pointers)
        pModuleId1++;
        pModuleId2++;
    }

    // Clear various flags/counters after table initialization
    *(int *)((char *)this + 0xA4) = 0;
    *(int *)((char *)this + 0xC0) = 0;
    *(int *)((char *)this + 0xF0) = 0;
    *(int *)((char *)this + 0xFC) = 0;
    *(int *)((char *)this + 0x104) = 0;
    *(int *)((char *)this + 0x10C) = 0;
    *(int *)((char *)this + 0x114) = 0;
    *(int *)((char *)this + 0x11C) = 0;
    *(int *)((char *)this + 0x120) = 0;
    *(int *)((char *)this + 0x12C) = 0; // 300 decimal
    *(int *)((char *)this + 0x1E0) = 0;
    *(int *)((char *)this + 0x1E4) = 0;
}