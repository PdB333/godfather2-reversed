// FUNC_NAME: updateGlobalResourceBlock
void __cdecl updateGlobalResourceBlock(uint32_t* pData) // ESI pointer to source data block
{
    // Copy 16 dwords (64 bytes) from pData to global resource block at 0x01219bd0
    // This block likely contains material/shader parameters
    volatile uint32_t* gResourceBlock = (volatile uint32_t*)0x01219bd0;
    for (int i = 0; i < 16; i++)
    {
        gResourceBlock[i] = pData[i];
    }

    // Check if global resource manager is active (not pointing to sentinel 0x01219a70)
    if (DAT_012058e8 == &DAT_01219a70) // gResourceManager == sentinel
    {
        // Index into resource handle arrays (each entry 0x30 bytes)
        uint32_t index = DAT_01219b20; // Global index/ID
        // First resource handle at base + index*0x30 + 0x00
        uint32_t* resourceHandle1 = (uint32_t*)(&DAT_01219cd0 + index * 0x30);
        if (*resourceHandle1 != 0)
        {
            // Call function to assign first resource (likely texture or material)
            FUN_0060b020(DAT_01219a80, *resourceHandle1); // gResourceBase, handle
        }
        // Second resource handle at next dword offset
        uint32_t* resourceHandle2 = (uint32_t*)(&DAT_01219cd4 + index * 0x30);
        if (*resourceHandle2 != 0)
        {
            FUN_0060aea0(DAT_01219a80, *resourceHandle2);
        }
    }
}