// FUN_NAME: Connection::buildResponsePacket
bool __thiscall Connection::buildResponsePacket(int this, uint32_t* packetBuffer, int commandType, uint32_t extraParam)
{
    uint32_t* buf = packetBuffer;                // puVar2
    byte flags[8];                               // local_c
    uint32_t stackValue;                         // uStack_4 (uninitialized, but used later)
    
    // Query global state (e.g., isConnectionReady?)
    checkNetworkFlags(flags, 0x800);             // FUN_004af8c0
    
    if ((flags[0] & 1) != 0) {
        // Generate sequence number or token
        uint32_t sequence = generateSequenceNumber();  // FUN_005565f0
        
        // Temporarily clear packetBuffer pointer for virtual call?
        packetBuffer = nullptr;                  // param_2 = 0
        // Call virtual function on the object pointed to by the first element of the packet buffer
        // This function likely fills packetBuffer with initial data from the object
        (*(code**)(**(int**)buf + 0x98))(&packetBuffer, sequence); // vtable+0x98
        
        // Get pointer at offset 0x10 from this object
        int somePtr = *(int*)(this + 0x10);      // iVar1
        buf[8] = somePtr;                        // packetBuffer[8] (offset 0x20)
        
        // If some flag at somePtr+4 is non-zero, increment counter at somePtr+6
        if (*(short*)(somePtr + 4) != 0) {
            *(short*)(somePtr + 6) = *(short*)(somePtr + 6) + 1;
        }
        
        buf[9] = stackValue;                     // uStack_4 (value from stack, possibly set by virtual call)
        return true;
    }
    
    // Handle different command types
    if (commandType == 3) {
        handleCommandType3(this);                 // FUN_00558520
        return true;
    }
    if (commandType == 4) {
        handleCommandType4(buf, this, extraParam); // FUN_005585a0
        return true;
    }
    if (commandType == 2) {
        handleCommandType2(buf, this, extraParam); // FUN_00558660
        return true;
    }
    return false;
}