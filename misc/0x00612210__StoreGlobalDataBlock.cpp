// FUNC_NAME: StoreGlobalDataBlock
void StoreGlobalDataBlock(uint32_t* data)
{
    // Global 64-byte buffer at 0x011f6970 (16 dwords) - stores a 4x4 matrix or similar data block
    // Global manager pointer at 0x012058e8
    extern uint32_t g_globalDataBuffer[16];
    extern void* g_dataManager;

    // Copy 16 dwords from input into the global buffer
    for (int i = 0; i < 16; i++)
    {
        g_globalDataBuffer[i] = data[i];
    }

    // If the manager exists and its notification flag at +0x50 is non-zero, send the data
    if (g_dataManager != nullptr && *(int*)((uint8_t*)g_dataManager + 0x50) != 0)
    {
        // Call notification function with manager fields and the global buffer
        // First arg: value from manager +0x10 (likely an object ID or handle)
        // Second arg: int from manager +0x50 (flag/count)
        // Third arg: pointer to the global data buffer
        NotifyDataUpdate(
            *(uint32_t*)((uint8_t*)g_dataManager + 0x10),
            *(int*)((uint8_t*)g_dataManager + 0x50),
            g_globalDataBuffer
        );
    }
}