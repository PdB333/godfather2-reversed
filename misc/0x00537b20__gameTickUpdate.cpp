// FUNC_NAME: gameTickUpdate
void __cdecl gameTickUpdate(void)
{
    // Call processing function with two arguments:
    //   g_pManagerA - pointer to some manager object (0x121a390)
    //   *(uint32_t*)(g_pManagerB + 0x4) - value at offset 4 from another manager pointer (0x121b638)
    managerProcessFunction(g_pManagerA, *(uint32_t*)(g_pManagerB + 4));
}