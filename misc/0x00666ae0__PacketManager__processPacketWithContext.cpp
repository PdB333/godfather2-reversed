// FUNC_NAME: PacketManager::processPacketWithContext

int PacketManager::processPacketWithContext(int* context, int buffer, int* packetInfo, int extraParam)
{
    int result;
    // Stack-based context for initializing stream processing
    struct StreamContext {
        int field0;       // +0x00: stream offset or status
        int field4;       // +0x04: buffer size (0x40 = 64)
        int field8;       // +0x08: current position/flag
        char data[20];    // +0x0C: temporary buffer
    } streamCtx;          // local_24 -> local_1c offsets: 0, 4, 8, then 0xC to 0x1F

    // Packet already finalized? Return error code.
    if (packetInfo[2] == 1)
    {
        return -3; // Already processed
    }

    // If buffer indicates first-time allocation (field +8 set to 1)
    if (*(int*)(buffer + 8) == 1)
    {
        void* allocated = _calloc(4, 0x40); // Allocate 256 bytes for metadata
        if (allocated == (void*)0x0)
        {
            return -2; // Out of memory
        }

        // Initialize stream context
        streamCtx.field0 = 0;
        streamCtx.field4 = 0x40; // 64 bytes space
        streamCtx.field8 = 0;

        result = FUN_00667910(packetInfo, &streamCtx); // Initialize packet stream from packetInfo
        if (result == 0)
        {
            result = FUN_006677b0(); // Set up stream internal state
            if (result == 0)
            {
                result = FUN_006657a0(); // Validate integrity or sequence
                if (result != 0)
                {
                    FUN_00665b80(&streamCtx, streamCtx.data, 0); // Clean up failed context
                    return result;
                }
                // Recursive call with context pointing to streamCtx, buffer to its temp data
                result = FUN_00666ae0(&streamCtx, streamCtx.data, packetInfo, extraParam);
                FUN_00665b80(&streamCtx, streamCtx.data, 0); // Final cleanup
                return result;
            }
        }
        FUN_00665b40(); // Rollback allocation or unlock
        return result;
    }

    // Normal path: check global state and timeouts
    result = FUN_00666800(); // Is there a pending packet?
    if (result == 0)
    {
        result = FUN_0066a440(); // Get retransmission timeout multiplier
        result = result * 2;
    }

    // Decide between two handlers based on packet state and pending flag
    if (((*packetInfo < 1) || ((*(byte*)packetInfo[3] & 1) == 0)) && (result == 0))
    {
        result = FUN_0066bc50(context, buffer, packetInfo, extraParam); // Handle early/unreliable packet
    }
    else
    {
        result = FUN_00666c30(context, buffer, packetInfo, extraParam, result); // Handle late/reliable packet
    }
    return result;
}