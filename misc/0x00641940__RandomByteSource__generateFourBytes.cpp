// FUNC_NAME: RandomByteSource::generateFourBytes
// Function at 0x00641940: Generates 4 bytes into a buffer (passed in EAX) if initialized,
// otherwise checks readiness and initializes if needed.
void __fastcall RandomByteSource::generateFourBytes(void* thisPtr, uint8_t* outBuffer) // this=ECX, outBuffer=EAX
{
    // Check initialization flag at offset +0xC
    if (*(int32_t*)((uint8_t*)thisPtr + 0xC) == 0)
    {
        // Check if the source is ready to be seeded/initialized
        int32_t ready = isReady(); // FUN_006385a0
        if (ready != 0)
        {
            initialize(); // FUN_00641890
        }
        // If not ready, fall through without writing any bytes
    }
    else
    {
        // Write 4 bytes in reverse order (little-endian fill)
        for (int32_t i = 3; i >= 0; i--)
        {
            outBuffer[i] = getNextByte(); // FUN_006418b0
        }
    }
}