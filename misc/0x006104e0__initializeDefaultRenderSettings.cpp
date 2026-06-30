// FUNC_NAME: initializeDefaultRenderSettings
// Address: 0x006104e0
// Role: Allocates and initializes a small block of 8 uint32 values from globals.
// Likely sets default render or HUD color configuration (e.g., family color tints).
void initializeDefaultRenderSettings(void)
{
    // Allocate 0xD (13) bytes? Actually allocation size seems odd.
    // FUN_0060cd00 parameters: poolId=0xD, elementSize=4, count=0, flags=1, unknown=0
    // Returning pointer to block of memory (likely 32 bytes, 8 ints).
    uint32_t* pBuffer = (uint32_t*)FUN_0060cd00(0xD, 4, 0, 1, 0);
    uint32_t colorA = DAT_00e2eff4;  // primary color value
    uint32_t colorB = DAT_00e2b1a4;  // secondary color value

    if (pBuffer != nullptr)
    {
        pBuffer[0] = colorA;  // first entry
        pBuffer[1] = colorB;  // repeat four times
        pBuffer[2] = colorB;
        pBuffer[3] = colorB;
        pBuffer[4] = colorB;
        pBuffer[5] = colorA;  // then three times
        pBuffer[6] = colorA;
        pBuffer[7] = colorA;

        FUN_0060cde0();  // post-initialization step (e.g., commit or register)
    }
}