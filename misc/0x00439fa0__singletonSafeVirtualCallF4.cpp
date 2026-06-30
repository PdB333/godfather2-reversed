// FUNC_NAME: singletonSafeVirtualCallF4
int __cdecl singletonSafeVirtualCallF4(void)
{
    // Global pointer to a singleton manager (likely from EA EARS engine)
    // DAT_01223510 is a pointer to an object whose vtable has a method at offset 0xF4
    EARSManager* manager = (EARSManager*)DAT_01223510;  // +0x00: pointer to manager instance

    if (manager != nullptr)
    {
        // Call virtual method at vtable offset 0xF4 (0xF4 / 4 = 61st virtual function)
        // This method presumably performs some update or action and returns a result code
        int result = manager->vtableMethodF4();
        return result;
    }

    // If manager doesn't exist, return 1 (presumably meaning "no action needed" or "success")
    return 1;
}