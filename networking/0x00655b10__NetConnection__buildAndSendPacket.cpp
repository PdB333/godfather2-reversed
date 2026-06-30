// FUNC_NAME: NetConnection::buildAndSendPacket
// Function address: 0x00655b10
// Role: Constructs and sends a reliable (or not) packet with data from param2.
// Uses a stream/writer pattern: allocates buffer, writes header, checks conditions,
// may release previously acquired object references.
// Offsets used:
//   +0x30: uint* pChunkPointer (maybe pointer to chunk list)
//   +0x34: uint* pRemoteRef (pointer to remote connection or another packet)
//   +0x38: uint sequenceNumber
//   +0x44: uint payloadLow
//   +0x48: uint payloadHigh
//   +0x5c: char* sendBuffer (start of direct send buffer)
//   +0x68: char isConnected (flag)

void __thiscall NetConnection::buildAndSendPacket(int this, uint data, char isReliable, char isGuaranteed, uint eaxParam)
{
    int *piVar1;
    int *piVar2;
    char tempFlag;
    uint uVar4;
    uint dataTemp;
    
    // Local buffer for packet assembly (1024 bytes)
    char packetBuffer[1024];
    
    int bitLength = 0;
    char flag1 = 0;
    char flag2 = 0;
    uint tmp1 = 0;
    uint tmp2 = 0;
    uint bufferSize = 0x400;
    char temp8 = 1;
    uint *ptrArray = &PTR_LAB_00e42f38; // some static table pointer
    
    // Step 1: Write an 8-byte marker (temp8 = 1)
    writeToStream(8, &temp8);
    
    // Step 2: Write 0x40 bytes from eaxParam (likely a chunk ID or handle)
    writeToStream(0x40, eaxParam);
    
    // Step 3: Build packet header (result stored in dataTemp)
    dataTemp = buildPacketHeader(this, data, eaxParam);
    writeToStream(0x20, &dataTemp);
    
    // Step 4: Read two more fields from this
    dataTemp = *(uint *)(this + 0x44);
    tmp2 = *(uint *)(this + 0x48);
    tmp1 = *(uint *)(this + 0x38);
    writeToStream(0x40, &dataTemp);
    
    // Step 5: Write sequence number
    dataTemp = tmp1;
    uint seqFlags = writeToStream(0x20, &dataTemp);
    
    // Determine send mode: if not connected or not reliable / chunk empty -> force 0x100 flag
    if ((*(char *)(this + 0x68) == '\0') && ((isReliable == '\0') || (*(int *)(this + 0x30) == 0)))
    {
        seqFlags = seqFlags & 0xffffff00;
    }
    else
    {
        seqFlags = 1;
    }
    
    // Check if we should proceed with sending
    char shouldSend = checkCondition(seqFlags);
    if (shouldSend != '\0')
    {
        // Determine whether to use reference counting
        if ((isGuaranteed == '\0') || (*(int *)(this + 0x34) == 0))
        {
            dataTemp = 0;
        }
        else
        {
            dataTemp = 1;
        }
        
        char useRef = checkCondition(dataTemp);
        if (useRef == '\0')
        {
            // Path: release a previously acquired chunk via reference counting
            piVar2 = *(int **)(*(int *)(this + 0x30) + 0x18);
            if (piVar2 != (int *)0x0)
            {
                piVar2[2] = piVar2[2] + 1; // increment reference (temporary)
            }
            releaseRef(piVar2);
            if (piVar2 != (int *)0x0)
            {
                piVar1 = piVar2 + 2;
                *piVar1 = *piVar1 - 1; // decrement reference
                if (*piVar1 == 0)
                {
                    // Destroy object via vtable
                    (**(code **)(*piVar2 + 8))(piVar2);
                }
            }
        }
        else
        {
            // Path: release the remote reference directly
            releaseRef(*(uint *)(this + 0x34));
        }
    }
    
    // Copy the assembled packet from stack buffer to object's send buffer
    copyToSendBuffer(this + 0x5c, packetBuffer, (bitLength + 7) >> 3, 0);
    
    // Finalize/flush the send
    flushSendBuffer();
}