// FUNC_NAME: NetConnection::buildAckPacket

uint32 NetConnection::buildAckPacket()
{
    // this is passed as param_1 (int*)
    // +0x08: output buffer write pointer (pointer to current write position, increments by 8 after write)
    // +0x0C: input packet buffer structure (contains read pointer and type/data)
    // +0x10: connection state structure (+0x20: sentSequence, +0x24: expectedAckSequence)

    int* inputPtr = *(int**)(this + 0x0C) + 8;  // input buffer read pointer (offset +8 within input struct)
    uint32 ackId = g_constantAckId;              // DAT_00e2b1a4, some global constant

    uint32 inputType;  // local_18 initially 0
    uint32 extraction; // local_14, used for hash/ID extraction

    // First check: if current input read pointer is not valid or type is not 3 or type 4 without extraction
    if ( (*(int**)(this + 8) > inputPtr) || (inputPtr == nullptr) ||
         ((*inputPtr != 3) && ((*inputPtr != 4) || (extraction = FUN_00636850(&inputType), extraction == 0))) )
    {
        goto LAB_00438ff3;
    }

    // If the first check passed, reload input pointer (it might have been advanced by the extraction)
    inputPtr = *(int**)(this + 0x0C) + 8;
    if ( (inputPtr < *(int**)(this + 8)) && (inputPtr != nullptr) )
    {
        if (*inputPtr != 3)
        {
            if ((*inputPtr != 4) || (extraction = FUN_00636850(&inputType), extraction == 0))
            {
                goto LAB_00438fea;
            }
            // type 4: prepare a local struct { type=3, data=extractedValue }
            int localData[2]; // local_10 and local_c
            localData[0] = 3;
            localData[1] = inputType;  // local_14
            inputPtr = localData;
        }
        ackId = inputPtr[1]; // get the ack ID from the packet
    }
    else
    {
        LAB_00438fea:
        ackId = 0;
    }

LAB_00438ff3:
    // Check another field at +0x10 from input buffer for additional ack processing
    inputPtr = *(int**)(this + 0x0C) + 0x10;
    if ( (inputPtr < *(int**)(this + 8)) && (inputPtr != nullptr) &&
         ( (*inputPtr == 4 || *inputPtr == 3)) &&
         ( (inputPtr < *(int**)(this + 8) && (inputPtr != nullptr) && (*inputPtr != 4)) &&
           (FUN_00633990(this) != 0) &&
           (*(uint32*)(*(int*)(this + 0x10) + 0x20) <= *(uint32*)(*(int*)(this + 0x10) + 0x24)) ) )
    {
        FUN_00627360(); // some overflow/debug callback
    }

    // Main packet processing: check the primary input buffer pointer
    inputPtr = *(int**)(this + 0x0C);
    if ( (inputPtr < *(int**)(this + 8)) && (inputPtr != nullptr) &&
         ( (*inputPtr == 4 || *inputPtr == 3) &&
           (inputPtr < *(int**)(this + 8) && (inputPtr != nullptr)) ) )
    {
        uint32 newAck = 0;
        if (*inputPtr == 4)
        {
            newAck = inputPtr[1] + 0x10; // some offset
        }
        else
        {
            uint32 seqResult = FUN_00633990(this);
            if (seqResult != 0)
            {
                newAck = inputPtr[1] + 0x10;
            }
            else
            {
                newAck = 0;
            }
            if (*(uint32*)(*(int*)(this + 0x10) + 0x20) <= *(uint32*)(*(int*)(this + 0x10) + 0x24))
            {
                FUN_00627360();
            }
        }
        if (newAck != 0)
        {
            ackId = FUN_00438bb0(ackId); // convert/update ackId
        }
    }

    // Write response packet to output buffer
    uint32* outputPtr = *(uint32**)(this + 8);
    *outputPtr = 2;          // packet type = 2 (ack)
    outputPtr[1] = ackId;    // ack data
    *(int*)(this + 8) += 8;  // advance output write pointer by 8 bytes

    return 1; // success
}