// FUNC_NAME: buildGhostUpdateChunksFromTree
void buildGhostUpdateChunksFromTree(void* packetBuffer, void* treeRoot) {
    // Global object with vtable at unaff_EDI, likely a game manager
    GlobalObject* global = (GlobalObject*)unaff_EDI;
    
    // Lock a mutex by hash (0x6fd313e)
    lockMutex(packetBuffer, 0x6fd313e);
    
    // Iterator state: either linked list or index-based with bitset
    // cStack_64 indicates mode: 0 = linked list, else = index with bitset
    // uStack_58 = current index, uStack_54 = total, iStack_60 = bitset base
    char mode = 0; // initialize; actually from stack variable cStack_64
    uint currentIndex = 0; // uStack_58
    uint totalCount = 0; // uStack_54
    int* bitset = 0; // iStack_60
    undefined4** nodePtr = 0; // ppuVar7
    undefined4* payloadPtr = 0; // puStack_5c
    undefined4 payloadData = 0; // uStack_48
    
    // Assume iteration set up from stack local variables
    // The loop condition depends on mode
    while (true) {
        bool done;
        if (mode == 0) {
            // Linked list: null-terminated relative offsets
            done = (*nodePtr == 0);
        } else {
            done = (currentIndex == totalCount);
        }
        if (done) break;
        
        // Determine the node pointer to read from
        undefined4** readingNode;
        if (mode == 0) {
            readingNode = nodePtr;
        } else {
            readingNode = &payloadPtr; // Actually it's puStack_50, which is the payload pointer
        }
        
        // Read the type/value from the node
        undefined4* typeValue;
        if (*(short*)((int)readingNode + 6) == 0x25e3) {
            // Short value at offset +4
            typeValue = (undefined4*)(uint)*(ushort*)(readingNode + 1);
        } else {
            // Pointer value at offset +4
            typeValue = readingNode[1];
        }
        
        // Switch on the type (0-5) to fill the array at packetBuffer+0x14
        int* chunkArray = (int*)((char*)packetBuffer + 0x14); // Array of structs of 12 bytes each
        int totalSlots = global->vtable->getTotalCount(); // vtable+0x220
        int startSlot = global->vtable->getStartIndex(0); // vtable+0x228 and pass 0
        
        switch ((int)typeValue) {
        case 0: // Fill slot's first field (offset 0)
            {
                undefined4* value = readingNode[2];
                int count = global->vtable->getStartIndex(0); // Actually uses same vcall as getStartIndex? But it's getTotalCount reused? Mist in decompile
                // Actually it calls getTotalCount (0x228) again? Let's extract from decompiled: case 0: uses uVar5 from (**(code **)(*unaff_EDI + 0x228))(0) for count
                int count = global->vtable->getTotalCount(0); // reuse of vtable+0x228? Actually it's the same call but result used for count
                byte idx = 0;
                if (count != 0) {
                    uint i = 0;
                    do {
                        idx++;
                        chunkArray[i * 3 + 0] = (int)value;
                        i = (uint)idx;
                    } while (i < count);
                }
            }
            break;
        case 1: // Fill from startSlot up to totalSlots, first field
            {
                undefined4* value = readingNode[2];
                int total = global->vtable->getTotalCount(0); // Actually vtable+0x228? Conflict: it calls 0x228 first then 0x220? In decompile: uVar3 = (**(code **)(*unaff_EDI + 0x220))(); uVar4 = (**(code **)(*unaff_EDI + 0x228))(0); uVar5 = uVar4 & 0xff; while(uVar5 < uVar3)...
                // So uVar3 is from 0x220 (maybe totalSlots), uVar4 from 0x228 (startSlot), uVar5 is startSlot & 0xff
                int totalSlots = global->vtable->getTotalCount();
                int start = global->vtable->getStartIndex(0);
                int i = start & 0xff;
                while (i < totalSlots) {
                    chunkArray[i * 3 + 0] = (int)value;
                    i = (byte)(start + 1);
                    start = i;
                }
            }
            break;
        case 2: // Fill second field (offset 4)
            {
                undefined4* value = readingNode[2];
                int count = global->vtable->getTotalCount(0);
                byte idx = 0;
                if (count != 0) {
                    uint i = 0;
                    do {
                        idx++;
                        chunkArray[i * 3 + 1] = (int)value;
                        i = (uint)idx;
                    } while (i < count);
                }
            }
            break;
        case 3: // Fill second field with range from startSlot to totalSlots
            {
                undefined4* value = readingNode[2];
                int totalSlots = global->vtable->getTotalCount();
                int start = global->vtable->getStartIndex(0);
                int i = start & 0xff;
                while (i < totalSlots) {
                    chunkArray[i * 3 + 1] = (int)value;
                    i = (byte)(start + 1);
                    start = i;
                }
            }
            break;
        case 4: // Fill third field (offset 8)
            {
                undefined4* value = readingNode[2];
                int count = global->vtable->getTotalCount(0);
                byte idx = 0;
                if (count != 0) {
                    uint i = 0;
                    do {
                        idx++;
                        chunkArray[i * 3 + 2] = (int)value;
                        i = (uint)idx;
                    } while (i < count);
                }
            }
            break;
        case 5: // Fill third field with range from startSlot to totalSlots
            {
                undefined4* value = readingNode[2];
                int totalSlots = global->vtable->getTotalCount();
                int start = global->vtable->getStartIndex(0);
                int i = start & 0xff;
                while (i < totalSlots) {
                    chunkArray[i * 3 + 2] = (int)value;
                    i = (byte)(start + 1);
                    start = i;
                }
            }
            break;
        }
        
        // Advance iterator
        if (mode == 0) {
            if ((int)currentIndex < 0) { // actually condition on (int)uStack_58 < 0 -> done? but code uses <0 to also update
                nodePtr = (undefined4**)((int)nodePtr + (int)*nodePtr);
                advanceIterator(); // FUN_0043b140
                nodePtr = (undefined4**)((int)nodePtr + (int)*nodePtr);
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex++;
                nodePtr = (undefined4**)((int)nodePtr + (int)*nodePtr);
                nodePtr = (undefined4**)((int)nodePtr + (int)*nodePtr);
            } else {
                nodePtr = (undefined4**)&DAT_01163cf8; // sentinel/end marker
            }
        } else {
            currentIndex++;
            if (currentIndex != totalCount) {
                // Update bitset iteration
                uint16_t idxShort = (short)currentIndex;
                if ((*(byte*)((currentIndex >> 3) + (int)bitset) & (1 << (currentIndex & 7))) == 0) {
                    payloadPtr = payloadPtr; // unchanged? Actually it sets payloadPtr to puStack_5c and then increment
                    payloadPtr = payloadPtr + 1;
                } else {
                    payloadPtr = 0;
                    payloadData = 0;
                }
            }
        }
    }
    return;
}