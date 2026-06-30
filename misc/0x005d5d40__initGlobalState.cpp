// FUNC_NAME: initGlobalState
void initGlobalState(void)
{
    int sizeMultiplier = g_someGlobalMultiplier * 0x1c; // DAT_012056bc - possibly a count * struct size
    int* pVtableSlot = (int*)(g_pGlobalManager + 0x14); // DAT_01206880 - likely pointer to a manager object, +0x14 is vtable pointer field

    // Set the vtable pointer to point to a static vtable (PTR_FUN_01126cf8)
    *(void**)(g_pGlobalManager + 0x14) = (void*)&PTR_FUN_01126cf8;

    // Increment the pointer stored at that location by 4 (skip first entry? or adjust for derived class?)
    *pVtableSlot = *pVtableSlot + 4;

    // Call initialization routine with parameters: type=4, data pointer (base + offset), size 0x10, stride 0x1c
    FUN_005d7490(4, CONCAT44(sizeMultiplier, &g_someGlobalData), 0x10, 0x1c); // DAT_0119eac0 - likely a static data array
    return;
}