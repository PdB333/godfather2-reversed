// FUNC_NAME: Debug::writeToLogBuffer
void __fastcall Debug::writeToLogBuffer(void* this_ptr, uint32_t inputData)
{
    char resultChar;            // +0x00: temporary 1-byte buffer
    uint32_t resultBuffer;      // +0x04: temporary 4-byte buffer

    // Delegate to the underlying low-level buffer write routine
    FUN_005f0560(inputData, &resultChar, resultBuffer);
}