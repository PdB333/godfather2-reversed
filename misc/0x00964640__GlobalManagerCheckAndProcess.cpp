// FUNC_NAME: GlobalManagerCheckAndProcess
void GlobalManagerCheckAndProcess(void* arg1, void* arg2)
{
    // Global pointer to a manager singleton (DAT_01223484)
    // Check if manager exists and its +0x0C field is non-zero
    if ((g_pGlobalManager != 0) && (*(int*)(g_pGlobalManager + 0x0C) != 0))
    {
        // Stack structure for table initialization
        struct TableInitContext {
            void** tablePtr;    // +0x00: pointer to global function table (PTR_LAB_00d79770)
            int tableSize;      // +0x04: number of entries (6)
            int field0;         // +0x08: zeroed
            int field1;         // +0x0C: zeroed
            int field2;         // +0x10: zeroed
        } context;

        context.tablePtr = &PTR_LAB_00d79770;  // Global table of function pointers
        context.tableSize = 6;
        context.field0 = 0;
        context.field1 = 0;
        context.field2 = 0;

        // Initialize or process arg2 (likely an object)
        FUN_008b5c70(arg2);

        // Fill or use the table context
        FUN_008a2f80(&context);

        // Cleanup or finalize
        FUN_008b5cb0();
    }
}