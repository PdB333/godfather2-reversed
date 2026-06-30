// TNLConnection::processReliableQueue (0x00432480)
void TNLConnection::processReliableQueue()
{
    // FS segment: thread-local global data pointer
    int* pGlobalData = *(int**)(__readfsdword(0x2C) + 0x2c);
    bool bHasPendingGhost = false;
    
    // start a new packet (serialization buffer setup)
    beginPacket();
    
    // Determine if reliable sending is active:
    // bit at +0x1095 = mEnableReliableSend, +0x39f8 = mConnectionState (0=disconnected,1=connected)
    // +0x1096 = mReliableActive (set below)
    bool bNewSendActive = false;
    if (*(char*)(this + 0x1095) == '\0' && *(int*)(this + 0x39f8) != 1)
    {
        // check if we can initiate sending (some condition from FUN_00431db0)
        if (canStartSend()) // FUN_00431db0
        {
            bNewSendActive = true;
        }
    }
    *(char*)(this + 0x1096) = (char)bNewSendActive;
    
    uint8_t mask = getCurrentTimeMask(); // FUN_004aa860
    int passIndex = 0; // local_2c: 0=first,1=second,2=third pass
    
    do {
        uint seq;
        // decide which sequence number to use based on packet flags (bit 4 of mPacketFlags at +0x3af8)
        if ((*(uint*)(this + 0x3af8) >> 4 & 1) == 0) {
            seq = 0xFFFFFFFF;
        } else {
            seq = getPacketSequence(this, this + 0x28, this + 0x38, 1); // FUN_0042cd20
        }
        
        bool skipPass = false;
        if (passIndex == 1) {
            if (seq > 0x30) skipPass = true; // wait for sequence
        } else {
            // second condition: if not first pass and seq > 0x30 -> skip
            if (passIndex != 0 && seq > 0x30) skipPass = true;
        }
        
        if (!skipPass)
        {
            // get another sequence (opposite source)
            if ((*(uint*)(this + 0x3af8) >> 4 & 1) == 0) {
                seq = getPacketSequence(this, this + 0x28, this + 0x38, 1);
            } else {
                seq = 0xFFFFFFFF;
            }
            
            bool skipPass2 = false;
            if (passIndex != 0) {
                if (seq > 0x30) skipPass2 = true;
            } else {
                // first pass always proceeds
            }
            
            if (!skipPass2)
            {
                setSendState(passIndex != 0); // FUN_004317f0
                
                // Iterate over reliable packet list (array of pointers at +0x3a74, count at +0x3af4)
                int* pList = (int*)(this + 0x3a74);
                int listSize = *(int*)(this + 0x3af4);
                int* pEnd = pList + listSize;
                int* pCurrent = pList;
                undefined** previousVtable = nullptr;
                
                if (pList != pEnd)
                {
                    do {
                        undefined** ppObjectVtable = (undefined**)*pCurrent;
                        
                        // check if reliable sending active and object allows send
                        bool allowSend = true;
                        if (*(char*)(this + 0x1096) != '\0')
                        {
                            char result = (**(code**)(*ppObjectVtable + 0x44))(); // checkSendAllowed
                            if (result == '\0') allowSend = false;
                        }
                        
                        if (allowSend)
                        {
                            undefined** ppEffectiveVtable = ppObjectVtable;
                            // Determine effective vtable (some objects need substitution)
                            if (*(char*)(this + 0x1095) == '\0')
                            {
                                // Normal mode: check if onlySendReliable flag is set
                                if (*(char*)(this + 0x1094) != '\0')
                                {
                                    char sendFlag = (**(code**)(*ppObjectVtable + 0x3c))(); // getSendReliableOnly
                                    if (sendFlag != '\0')
                                    {
                                        // Use a different vtable (the "reliable-only" path)
                                        ppEffectiveVtable = (undefined**)(**(code**)(*ppObjectVtable + 0x48))(); // getReliableOnlyVtable
                                    }
                                }
                            }
                            else
                            {
                                // Special handling for move packets (two types)
                                if (ppObjectVtable == &PTR_PTR_0110b3a0 || ppObjectVtable == &PTR_PTR_0110b3bc)
                                {
                                    int condition = *(int*)(pGlobalData + 0x34); // some global state index
                                    if ( (*(int*)0xf15a4c == 0) || (*(int*)0xf15a4c == 1) ) // DAT_00f15a4c
                                    {
                                        ppEffectiveVtable = &PTR_PTR_0110b3f4;
                                    }
                                    else
                                    {
                                        ppEffectiveVtable = &PTR_PTR_0110b3d8;
                                    }
                                }
                                else if (ppObjectVtable == &PTR_PTR_0110b26c || ppObjectVtable == &PTR_PTR_0110b2b4)
                                {
                                    ppEffectiveVtable = &PTR_PTR_0110b290;
                                }
                                else if (ppObjectVtable == &PTR_PTR_0110b2fc || ppObjectVtable == &PTR_PTR_0110b344)
                                {
                                    ppEffectiveVtable = &PTR_PTR_0110b320;
                                }
                                else if (ppObjectVtable == &PTR_PTR_0110b490)
                                {
                                    // Count child objects of a ghost
                                    int childCount = 0;
                                    int childPtr = *(int*)(passIndex * 4 + 0x110b4a0);
                                    if (childPtr != 0)
                                    {
                                        do {
                                            childPtr = *(int*)(childPtr + 0x10);
                                            childCount++;
                                        } while (childPtr != 0);
                                        if (childCount == 1)
                                        {
                                            bHasPendingGhost = true;
                                            ppEffectiveVtable = &PTR_PTR_0110b4ac;
                                        }
                                    }
                                }
                            }
                            
                            // If connection state is connected (1), get the effective vtable's send function
                            if (*(int*)(this + 0x39f8) == 1) // mConnectionState == connected
                            {
                                ppEffectiveVtable = (undefined**)(**(code**)(*ppEffectiveVtable + 0x4c))(); // getSendData
                            }
                            
                            // Begin serialization into buffers (+0x1120, +0x10e0) using the effective vtable
                            (**(code**)(*ppEffectiveVtable + 8))(this + 0x1120, this + 0x10e0, *(int*)(this + 0x39f8) == 0);
                            
                            // Iterate over linked list of packet data starting from ppObjectVtable[passIndex+4] (each link has +0x10)
                            for (undefined* puVar3 = ppObjectVtable[passIndex + 4]; puVar3 != nullptr; puVar3 = *(undefined**)(puVar3 + 0x10))
                            {
                                // Check flags on the packet data (+0x38):
                                // bit 1: something, bit 2: time mask
                                if ((((puVar3[0x38] & 2) == 0) &&
                                     ((byte)puVar3[0x38] >> 2 & mask & 0xf) == mask) &&
                                    // Validate through vtable +0x14
                                    (char) (**(code**)(*ppEffectiveVtable + 0x14))(puVar3) != '\0')
                                {
                                    // Get global bit from another source
                                    uint globalValue = *(uint*)(*(int*)(pGlobalData + 8) + 0x7c + *(int*)(puVar3 + 0x18));
                                    byte requiredBit = (**(code**)(*ppEffectiveVtable + 0x40))(); // getRequiredBit
                                    if (((globalValue >> 0xb) & 1) == requiredBit)
                                    {
                                        // Find matching entry in global database (max 3 entries)
                                        int id = 0;
                                        uint dataId = 0;
                                        undefined* dataPtr = nullptr;
                                        if (*(char*)(this + 0x1094) == '\0')
                                        {
                                            int* pDatabase = (int*)(DAT_012233b0 + 0x30); // some global table
                                            do {
                                                if ((undefined*)*pDatabase == puVar3)
                                                {
                                                    dataId = *(uint*)(&DAT_01163834 + id * 0x84);
                                                    dataPtr = &DAT_01163650 + id * 0x210;
                                                    break;
                                                }
                                                id++;
                                                pDatabase++;
                                            } while (id < 3);
                                        }
                                        char foundInDatabase = (dataPtr != nullptr) ? '\x01' : '\0';
                                        
                                        // Check vtable +0x3c for send flag
                                        char sendFlag = (**(code**)(*ppEffectiveVtable + 0x3c))();
                                        if (foundInDatabase == sendFlag)
                                        {
                                            // Attempt to serialize packet data into buffer +0x1160
                                            char serializeResult = (**(code**)(*ppEffectiveVtable + 0x24))(puVar3, this + 0x1160);
                                            if (serializeResult == '\0')
                                            {
                                                // Destroy old buffer
                                                (**(code**)(*ppEffectiveVtable + 0x20))(puVar3);
                                                // Write serialized data into +0x10d0 (response buffer)
                                                char responseResult = (**(code**)(*ppEffectiveVtable + 0x28))(puVar3, this + 0x10d0);
                                                if (responseResult == '\0')
                                                {
                                                    // If vtable changed, call begin/end pairs
                                                    if (previousVtable != ppEffectiveVtable)
                                                    {
                                                        if (previousVtable != nullptr)
                                                        {
                                                            (**(code**)(*previousVtable + 0x10))(); // end vtable
                                                        }
                                                        (**(code**)(*ppEffectiveVtable + 0xc))(); // begin vtable
                                                        previousVtable = ppEffectiveVtable;
                                                    }
                                                    // Queue the reliable packet (dataId, dataPtr, type=0)
                                                    queueReliablePacket(this, dataId, dataPtr, 0); // FUN_00430790
                                                }
                                                else if ((puVar3[0x38] & 1) != 0)
                                                {
                                                    // Store in pending reliable array (+0x88, count at +0x1088)
                                                    int pendingCount = *(int*)(this + 0x1088);
                                                    if (pendingCount < 0x100)
                                                    {
                                                        int* pEntry = (int*)(this + 0x88 + pendingCount * 0x10);
                                                        pEntry[0] = (int)puVar3;
                                                        pEntry[1] = dataId;
                                                        pEntry[2] = (int)ppEffectiveVtable;
                                                        pEntry[3] = (int)dataPtr;
                                                        *(int*)(this + 0x1088) = pendingCount + 1;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        pCurrent++;
                    } while (pCurrent != pEnd);
                    
                    // Finalize vtable if any was active
                    if (previousVtable != nullptr)
                    {
                        (**(code**)(*previousVtable + 0x10))(); // end vtable
                    }
                }
                
                // Process pending reliable array (postponed packets)
                int pendingCount = *(int*)(this + 0x1088);
                if (pendingCount != 0)
                {
                    int* pPending = (int*)(this + 0x88);
                    previousVtable = nullptr;
                    if (pPending != pPending + pendingCount * 4) // careful: array of 16-byte entries
                    {
                        // Actually iterate by 16 bytes (4 ints)
                        for (int* pIter = pPending; pIter != pPending + pendingCount * 4; pIter += 4)
                        {
                            undefined** ppVtable = (undefined**)pIter[2]; // vtable from entry
                            if (ppVtable != previousVtable)
                            {
                                if (previousVtable != nullptr)
                                {
                                    char flag = (**(code**)((int)*previousVtable + 0x44))();
                                    if (flag != '\0')
                                    {
                                        (**(code**)((int)*previousVtable + 0x1c))(); // finalize?
                                    }
                                    (**(code**)((int)*previousVtable + 0x10))(); // end vtable
                                }
                                // Begin new vtable with serialization
                                (**(code**)(*ppVtable + 8))(this + 0x1120, this + 0x10e0, *(int*)(this + 0x39f8) == 0);
                                (**(code**)(*ppVtable + 0xc))(); // begin vtable
                                // Check if we need to call start/prepare
                                char initFlag = (**(code**)(*ppVtable + 0x44))();
                                previousVtable = ppVtable;
                                if (initFlag != '\0')
                                {
                                    (**(code**)(*ppVtable + 0x18))(); // start/prepare
                                }
                            }
                            // Queue reliable packet with type=1
                            queueReliablePacket(this, *(undefined4*)(pIter + 1), *(undefined4*)(pIter + 3), 1); // FUN_00430790
                        }
                        // Finalize last vtable
                        if (previousVtable != nullptr)
                        {
                            char flag = (**(code**)((int)*previousVtable + 0x44))();
                            if (flag != '\0')
                            {
                                (**(code**)((int)*previousVtable + 0x1c))();
                            }
                            (**(code**)((int)*previousVtable + 0x10))();
                        }
                    }
                    flushPendingPackets(); // FUN_00434300
                }
            }
        }
        
        passIndex++;
        if (passIndex > 2)
        {
            // All passes done
            if (*(char*)(this + 0x1096) != '\0')
            {
                // Adjust global bandwidth parameters (throttle)
                if (DAT_012058d0 < 7) DAT_012058d0 = 7;
                if (7 < DAT_00f15988) DAT_00f15988 = 7;
                _DAT_011f39f4 = 0;
                if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
                if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
                _DAT_011f3a30 = 1;
                
                // Use a global vtable (PTR_PTR_0110b57c) to finalize sending
                (**(code**)(PTR_PTR_0110b57c + 8))(this + 0x1120, this + 0x10e0, *(int*)(this + 0x39f8) == 0);
                (**(code**)(PTR_PTR_0110b57c + 0xc))(); // begin
                (**(code**)(PTR_PTR_0110b57c + 0x18))(); // prepare
                (**(code**)(PTR_PTR_0110b57c + 0x20))(0); // setSome
                (**(code**)(PTR_PTR_0110b57c + 0x2c))(0,0,0); // setParams
                (**(code**)(PTR_PTR_0110b57c + 0x34))(); // update
                (**(code**)(PTR_PTR_0110b57c + 0x1c))(); // finalize
                (**(code**)(PTR_PTR_0110b57c + 0x10))(); // end
                
                freeReliableData(*(undefined4*)(this + 0x108c)); // FUN_00412f90
                
                // Restore bandwidth limits
                if (DAT_012058d0 < 7) DAT_012058d0 = 7;
                if (7 < DAT_00f15988) DAT_00f15988 = 7;
                _DAT_011f39f4 = 1;
            }
            if (*(char*)(this + 0x1095) != '\0' && !bHasPendingGhost)
            {
                finalizeSend(this + 0x1120); // FUN_00431c30
            }
            setSendState(1); // FUN_004317f0
            return;
        }
    } while (true);
}