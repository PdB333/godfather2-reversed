// FUNC_NAME: cleanupPair
// Address: 0x009643f0
// Releases two associated resources and processes a static table.
void __cdecl cleanupPair(void* objectA, void* objectB)
{
    // Global manager pointer (likely a singleton or module state)
    if ((g_manager != 0) && (*(int*)(g_manager + 0xC) != 0)) // +0xC: initialization flag
    {
        // Static table used for processing (likely array of function pointers or descriptors)
        void** table = reinterpret_cast<void**>(&s_pairTable);
        int count = 2;

        releaseResource(objectA);
        releaseResource(objectB);

        processTableWithCount(&table, count);
    }
}