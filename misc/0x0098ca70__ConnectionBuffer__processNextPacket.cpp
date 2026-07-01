// FUNC_NAME: ConnectionBuffer::processNextPacket
void __thiscall ConnectionBuffer::processNextPacket(void* this_ptr, uint32_t param2)
{
    uint32_t currentWritePos;
    int result[3]; // Array of 3 ints used as output structure
    void (*callback)(int); // Function pointer, initialized by called functions

    FUN_004d3bc0(param2); // Likely locks mutex or enters critical section
    FUN_004d5570(); // Possibly checks connection state or updates timers

    currentWritePos = *(uint32_t *)((char *)this_ptr + 0x244); // +0x244: current write index into packet buffer
    if (currentWritePos < *(uint32_t *)((char *)this_ptr + 0x248)) // +0x248: maximum write index (buffer size)
    {
        // Space available in buffer: increment write index by 16 bytes (one packet slot)
        *(uint32_t *)((char *)this_ptr + 0x244) = currentWritePos + 0x10;
        if (currentWritePos != 0)
        {
            FUN_004d3b50(result); // Probably copies packet data from buffer to result structure
        }
    }
    else
    {
        // Buffer full: handle overflow or flush
        FUN_0098c2b0(currentWritePos, result); // Possibly sends queued packets or drops old
    }

    if (result[0] != 0)
    {
        callback(result[0]); // Execute callback with the first element of result
    }
    return;
}