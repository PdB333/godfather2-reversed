// FUNC_NAME: getGlobalInstance
// Function at 0x0069f080: Returns a global 4-byte value (likely a pointer to a singleton or manager).
// Role: Simple getter for a global variable (DAT_00e50bc4).
extern void* g_pGlobalInstance; // 0x00e50bc4

void* getGlobalInstance(void)
{
    return g_pGlobalInstance;
}