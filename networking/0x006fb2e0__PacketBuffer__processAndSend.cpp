// FUNC_NAME: PacketBuffer::processAndSend
void __fastcall PacketBuffer::processAndSend(void* thisPtr)
{
    uint8_t buffer[4];
    uint32_t extraData;

    // Check if the count at offset 0x18 exceeds the threshold (15)
    if (*(uint32_t*)((uint8_t*)thisPtr + 0x18) > 0xF)
    {
        // Copy the 4-byte value at offset 0x10 into the temporary variable
        extraData = *(uint32_t*)((uint8_t*)thisPtr + 0x10);
        // Append the extra data to the output buffer (likely packing into buffer)
        appendDataToBuffer(buffer, &extraData);   // FUN_006fb160
    }
    // Flush/send the buffer (even if no data was appended)
    flushBuffer(buffer);                          // FUN_006fb0f0
}