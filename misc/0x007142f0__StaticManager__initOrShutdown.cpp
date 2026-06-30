// FUNC_NAME: StaticManager::initOrShutdown
void __fastcall StaticManager::initOrShutdown(void* thisPtr)
{
    // Check initialization flag at offset +0x0C (bit 0)
    if ((*(uint8_t*)((int)thisPtr + 0x0C) & 1) == 0)
    {
        // Not initialized: acquire global resources (e.g., semaphores)
        SystemAcquireSemaphore(&g_semaphoreA);
        SystemAcquireSemaphore(&g_semaphoreB);
    }
    else
    {
        // Already initialized: release global resources
        SystemReleaseSemaphore(&g_semaphoreA);
        SystemReleaseSemaphore(&g_semaphoreB);
    }
}