// FUNC_NAME: getObjectFlagsAndStatus
uint32_t __fastcall getObjectFlagsAndStatus(void* thisPtr)
{
    // Extract a pointer from this+0x0C (likely a data block or network object state).
    // Offset +0x0C: pointer to a data object (e.g., NetObject or SimObjectDataBlock)
    uint32_t* pDataBlock = *(uint32_t**)((char*)thisPtr + 0x0C);

    uint32_t rawValue;
    if (pDataBlock != nullptr)
    {
        // Read a 32-bit field at offset +0x30 from that object (e.g., flags or status word).
        // Offset +0x30: packed bitfield containing status/priority flags
        uint32_t packedField = *(uint32_t*)((char*)pDataBlock + 0x30);
        rawValue = packedField >> 1;   // Shift right to extract lower bits, bit0 indicates special state

        if ((rawValue & 1) != 0)
        {
            // Construct a return value with bit24 set to 1 and lower 24 bits from packedField>>9.
            // This likely indicates a "high priority" or "special status" with additional data.
            return (*pDataBlock >> 9) & 0x00FFFFFF | 0x01000000;
        }
    }
    else
    {
        rawValue = 0;
    }

    // Return the value with the low byte cleared.
    return rawValue & 0xFFFFFF00;
}