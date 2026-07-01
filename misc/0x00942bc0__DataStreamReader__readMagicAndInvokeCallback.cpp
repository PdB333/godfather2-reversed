// FUNC_NAME: DataStreamReader::readMagicAndInvokeCallback
void __thiscall DataStreamReader::readMagicAndInvokeCallback(void* thisPtr, void (*callback)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
{
    // Magic constants used as a signature/header verification pattern
    uint32_t magic1 = 0xbadbadba;
    uint32_t magic2 = 0xbeefbeef;
    uint32_t magic3 = 0xeac15a55;
    uint32_t magic4 = 0x91100911;

    // Read first uint32 from the stream pointer stored at this+0x18
    uint32_t streamValue1 = **(uint32_t**)((uint8_t*)thisPtr + 0x18);
    // Advance the stream pointer by 4 bytes (size of uint32)
    *(uint32_t**)((uint8_t*)thisPtr + 0x18) = *(uint32_t**)((uint8_t*)thisPtr + 0x18) + 1;

    // Process the magic constants (likely hash, checksum, or decryption)
    // Parameters: address of magic array, size 16 bytes, count 4
    FUN_0049c470(&magic1, 0x10, 4);

    // Read second uint32 from the stream
    uint32_t streamValue2 = **(uint32_t**)((uint8_t*)thisPtr + 0x18);
    *(uint32_t**)((uint8_t*)thisPtr + 0x18) = *(uint32_t**)((uint8_t*)thisPtr + 0x18) + 1;

    // Invoke callback with the two stream values and the processed magic constants
    callback(streamValue1, magic1, magic2, magic3, magic4, streamValue2);
}