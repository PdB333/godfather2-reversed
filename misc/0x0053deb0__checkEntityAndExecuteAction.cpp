// FUNC_NAME: checkEntityAndExecuteAction
void __cdecl checkEntityAndExecuteAction(void)
{
    // Global index (e.g., gCurrentEntityIndex)
    // Global array of structs (size 0x1b each) at gEntityArray
    // Global pointer passed as first argument to the callee (e.g., gSimManager)

    // Check if the first field (pointer) of the indexed struct is non-null
    if (*(int*)((char*)&gEntityArray + gCurrentEntityIndex * 0x1b) != 0)
    {
        int local_unused1 = 0; // Possibly part of a struct/alignment
        int local_unused2 = 0;
        int local_unused3 = 0;
        char outputBuffer[4]; // Output parameter (e.g., position or handle)

        // Call with global context, the entity pointer, and output buffer
        FUN_0060add0(gSomeGlobal, *(int*)((char*)&gEntityArray + gCurrentEntityIndex * 0x1b), outputBuffer);
    }
}