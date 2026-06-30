// FUNC_NAME: getGlobalStatePointer
// Address: 0x0069d890 - Simple getter returning pointer to global data buffer at 0x01129fc0
// Likely provides access to a singleton or global static object (e.g., a memory pool, configuration, or engine state)
void* getGlobalStatePointer(void)
{
    return reinterpret_cast<void*>(0x01129fc0); // Returns fixed address &DAT_01129fc0
}