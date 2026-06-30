// FUNC_NAME: ReliablePacketWindow::reset
void __fastcall ReliablePacketWindow::reset(int thisPtr)
{
    // Fields at +0x04 and +0x0c are likely sequence counters or timestamps (uint64)
    *(uint64_t*)(thisPtr + 0x04) = 0;
    *(uint64_t*)(thisPtr + 0x0c) = 0;

    // Array of 30 packet delivery records (each 8 bytes) at +0x18
    // Each record might be a (uint32 packetId, uint32 status) pair
    uint32_t* records = (uint32_t*)(thisPtr + 0x18);
    for (int i = 0; i < 30; i++)
    {
        records[0] = 0;
        records[1] = 0;
        records += 2;
    }
}