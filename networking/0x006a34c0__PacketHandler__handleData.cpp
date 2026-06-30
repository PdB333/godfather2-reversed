// FUNC_NAME: PacketHandler::handleData
void __thiscall PacketHandler::handleData(int thisPtr, short* data, int memberPointer)
{
    int state = *(int*)(thisPtr + 0x34); // m_state, -1 means disabled

    if (state < 0)
        return;

    if (memberPointer == (int)(thisPtr + 0x28)) // m_ackMarker
    {
        // Acknowledge packet – increment sequence number
        g_packetAckCounter++; // DAT_0112a0e0 – likely a global counter
        *(int*)(thisPtr + 0x34) = state + 1; // advance state
        return;
    }

    if (memberPointer == (int)(thisPtr + 8)) // m_smallDataMarker
    {
        if (data != nullptr && state != 0)
        {
            // Copy 0x20 bytes of small data into the small data buffer
            // The buffer is located in an inner structure pointed by thisPtr+0x30
            char* dest = (char*)(*(int*)(*(int*)(thisPtr + 0x30) + 4) + 8); // inner offset +8
            memcpy(dest, data, 0x20); // FUN_006a2660 – size 32 bytes
            return;
        }
    }
    else if (memberPointer == (int)(thisPtr + 0x10)) // m_largeDataMarker
    {
        if (data != nullptr && state != 0)
        {
            // Copy 0x200 bytes of large data into the large data buffer
            char* dest = (char*)(*(int*)(*(int*)(thisPtr + 0x30) + 4) + 0x48); // inner offset +0x48
            memcpy(dest, data, 0x200); // FUN_006a2690 – size 512 bytes
            return;
        }
    }
    else if (memberPointer == (int)(thisPtr + 0x18)) // m_flagMarker
    {
        if (data != nullptr && state != 0)
        {
            // Set a flag based on first short of data
            // If first short == 0x31 ('1'), set byte to 1; else 0
            char* flagDest = (char*)(*(int*)(*(int*)(thisPtr + 0x30) + 4) + 0x458);
            *flagDest = (*data == 0x31) ? 1 : 0;
            return;
        }
    }
    else if (memberPointer == (int)(thisPtr + 0x20)) // m_commandMarker
    {
        if (data != nullptr && state != 0)
        {
            // Process a command from the data
            processCommand(data); // FUN_006a2380
            return;
        }
    }
    else if (memberPointer == (int)thisPtr) // m_selfMarker (zero offset)
    {
        // Reset state to disabled
        *(int*)(thisPtr + 0x34) = -1;
    }

    return;
}