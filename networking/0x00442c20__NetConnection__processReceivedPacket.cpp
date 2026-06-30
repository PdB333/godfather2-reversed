// FUNC_NAME: NetConnection::processReceivedPacket

int __thiscall NetConnection::processReceivedPacket(void* thisPtr, PacketData* packet) // param_1 = this, param_2 = packet
{
    char allowProcessing;
    int payload;
    int* slotPtr;

    // Check packet magic number (negative constant -0xC0DEFFC = 0xF3F21004)
    if (packet->magic == -0xC0DEFFC)
    {
        // Copy payload field and validate extra data
        packet->result = packet->payload; // +0x1c = +0x14
        int extra = packet->extra; // +0x18
        if (FUN_004a30d0(extra) == 0) // validatePacketData(extra)?
        {
            packet->result = 0;
            return 0;
        }
    }
    else
    {
        payload = packet->payload; // +0x14
        packet->result = payload; // +0x1c

        allowProcessing = FUN_004a3800(); // isPacketProcessingAllowed()?
        if (allowProcessing == '\0')
        {
            packet->result = 0;
        }
        else
        {
            slotPtr = (int*)FUN_00443620(thisPtr + 0x68); // getPacketSlot()?
            if (slotPtr != (int*)0x0)
            {
                *slotPtr = payload;
                return payload;
            }
        }
        payload = 0;
    }
    return payload;
}