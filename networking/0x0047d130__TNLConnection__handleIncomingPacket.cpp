// FUNC_NAME: TNLConnection::handleIncomingPacket

void __thiscall TNLConnection::handleIncomingPacket(int this, int* msgTypePtr)
{
    char result;
    int typeId;
    uint32_t hashOut[2]; // local_c
    
    typeId = *msgTypePtr;
    
    if (typeId == gPingPacketType) // DAT_012069c4
    {
        handlePingPacket(); // FUN_0047d3c0
        return;
    }
    
    if (typeId == gDataPacketType) // DAT_0120e93c
    {
        // Check if any ghost manager slot is active (pointers at +0x88..+0x94)
        if ( (*(int*)(this + 0x88) != 0) || (*(int*)(this + 0x8c) != 0) ||
             (*(int*)(this + 0x90) != 0) || (*(int*)(this + 0x94) != 0) )
        {
            // Get object from first ghost manager slot (slot 0)
            int obj = getObjectFromManager(this + 0x88, 0); // FUN_00445ff0
            if (obj != 0)
            {
                // Check hash 0x38523fc3 on the object, output into hashOut
                result = checkObjectHash(obj, 0x38523fc3, hashOut); // FUN_00475660
                if (result != 0)
                {
                    processHashResult(hashOut[0]); // FUN_0044b210
                    *(byte*)(this + 0xa0) = 1; // Mark hash processed flag
                    setEvent(&gPingPacketType); // FUN_00408680 – trigger ping event?
                }
            }
        }
        
        // Check bit 0 at +0xa8 (some flag)
        if ((*(byte*)(this + 0xa8) & 1) != 0)
        {
            handleDefaultPacket(); // FUN_0047d290
        }
        
        setEvent(&gDataPacketType); // FUN_004086d0 – mark data packet handled
        return;
    }
    
    if (typeId == *(int*)(this + 0x18)) // Custom packet type stored at +0x18
    {
        handleDefaultPacket(); // FUN_0047d290
        return;
    }
    
    if (typeId == *(int*)(this + 0x20)) // Another custom type at +0x20
    {
        handleCustomPacket(); // FUN_0047d330
        return;
    }
    
    if (typeId == *(int*)(this + 0x28)) // Third custom type at +0x28
    {
        result = isGamePaused(); // FUN_004209a0 – maybe?
        if (result == 0)
        {
            int obj = getObjectFromManager(this + 0x88, 0);
            if (obj != 0)
            {
                result = checkObjectHash(obj, 0x38523fc3, hashOut);
                if (result != 0)
                {
                    processHashResult(hashOut[0]);
                    *(byte*)(this + 0xa0) = 1;
                    setEvent(&gPingPacketType);
                }
            }
        }
    }
    
    return;
}