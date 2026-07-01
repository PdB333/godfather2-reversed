// FUNC_NAME: TNLConnection::checkPendingPacketEntry

void __thiscall TNLConnection::checkPendingPacketEntry(int *this, int *entry)
{
    int *pDataBuffer1 = entry + 0x1f; // +0x7C: first data buffer pointer
    if (*pDataBuffer1 != 0 && *pDataBuffer1 != 0x48) // 0x48 = PACKET_TYPE_RELIABLE or similar
    {
        int *pDataBuffer2 = entry + 0x21; // +0x84: second data buffer pointer
        if (*pDataBuffer2 != 0)
        {
            char compareResult = FUN_0081b6b0(*pDataBuffer2, entry, 0x12); // compare buffer with header
            if (compareResult != '\0')
            {
                entry[0x2c] = DAT_01205224; // +0xB0: set timeout/expiration to max
                return;
            }
            // calculate time since last update from a table indexed by entry[0] (slot id)
            uint timeSinceUpdate = *(uint *)(*(int *)(this + 0x24) + 0xc + entry[0] * 0x1c);
            if ((0 < (int)timeSinceUpdate) && (timeSinceUpdate < (uint)(DAT_01205224 - entry[0x2c])))
            {
                if (*pDataBuffer1 != 0)
                {
                    FUN_004daf90(pDataBuffer1); // free buffer
                    *pDataBuffer1 = 0;
                }
                if (*pDataBuffer2 != 0)
                {
                    FUN_004daf90(pDataBuffer2);
                    *pDataBuffer2 = 0;
                }
            }
        }
    }
    return;
}