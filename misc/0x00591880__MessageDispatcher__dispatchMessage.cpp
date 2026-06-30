// FUNC_NAME: MessageDispatcher::dispatchMessage
void __thiscall MessageDispatcher::dispatchMessage(void* thisPtr, byte* packetData, int param_3)
{
    // packetData[0] low 6 bits: message type (0-35)
    int type = packetData[0] & 0x3f;
    if (type < 0x23) // 35 types
    {
        // Jump table at 0x0103b0e0 for message handlers
        void (**handlerTable)(void*, byte*, int) = (void (**)(void*, byte*, int))0x0103b0e0;
        if (handlerTable[type] != nullptr)
        {
            handlerTable[type](thisPtr, packetData, param_3);
        }
    }

    // packetData[1] signed char: number of sub-packets
    char subCount = (char)packetData[1];
    if (subCount > 0)
    {
        // Each sub-packet pointer starts at offset 0xC (12 bytes)
        uint* subPacketPtrs = (uint*)(packetData + 0xC);
        for (int i = 0; i < subCount; i++)
        {
            // Recursively process each sub-packet
            dispatchMessage(thisPtr, (byte*)subPacketPtrs[i], param_3);
        }
    }
}