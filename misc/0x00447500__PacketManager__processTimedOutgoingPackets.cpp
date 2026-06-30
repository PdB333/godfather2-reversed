// FUNC_NAME: PacketManager::processTimedOutgoingPackets
void PacketManager::processTimedOutgoingPackets(uint32_t timeoutLow, uint32_t timeoutHigh)
{
    LARGE_INTEGER startTick;
    LARGE_INTEGER currentTick;
    LARGE_INTEGER perfCounter;
    
    QueryPerformanceCounter(&startTick);
    
    // Convert timeout from 64-bit value to seconds using QPC frequency
    uint64_t timeoutRaw = ((uint64_t)timeoutHigh << 32) | timeoutLow;
    float timeoutSeconds = (float)(-(double)(timeoutRaw & 0x7FFFFFFFFFFFFFFF) * g_qpcToSeconds);  // negative? Might be a bug in decompiler
    
    QueryPerformanceCounter(&currentTick);
    
    // Calculate elapsed ticks since last update (stored at +0x30)
    uint64_t elapsedTicks = __allmul(currentTick.LowPart - *(uint32_t*)(this + 0x30),
                                     (currentTick.HighPart - *(int32_t*)(this + 0x34)) -
                                     (currentTick.LowPart < *(uint32_t*)(this + 0x30)),
                                     1000, 0);
    uint64_t frequency = ((uint64_t)g_qpcHigh << 32) | g_qpcLow;
    uint32_t ticks = __aulldiv(elapsedTicks, frequency);  // ticks in milliseconds?
    
    // Convert to some internal time unit
    int64_t internalTime = (int64_t)(-(double)(frequency & 0x7FFFFFFFFFFFFFFF) / g_floatThreshold);
    float fTemp = (float)(int)internalTime;
    if ((int)internalTime < 0) {
        fTemp += g_floatRound;
    }
    int64_t adjustedTime = (int64_t)(fTemp * g_qpcToSeconds + g_floatOffset);
    int32_t timeDelta = (int32_t)adjustedTime;
    
    PacketNode* node = *(PacketNode**)(this + 0x90);
    while (node != nullptr) {
        uint32_t packetId = node->id;  // +0x2C? Actually node+0x2C is 0xB elements? Wait, node[0xB] means at offset 0x2C (0xB*4)
        
        // Look up in hash table (global + 0x50 is bucket array, +0x54 is num buckets)
        uint32_t bucketIndex = packetId % *(uint32_t*)(g_global + 0x54);
        HashEntry* entry = *(HashEntry**)(*(int32_t*)(g_global + 0x50) + bucketIndex * 4);
        while (entry != nullptr) {
            if (entry->key == packetId) {
                break;
            }
            entry = entry->next;  // +0x08
        }
        
        int32_t foundStatus;
        if (entry != nullptr && entry->object != nullptr) {
            foundStatus = *(int32_t*)(entry->object + 0x2C);
        } else {
            foundStatus = PACKET_NOT_FOUND_SENTINEL;  // -0x1E98FD1
        }
        
        int32_t state = *(&foundStatus);  // iVar4 = foundStatus
        
        int32_t loopStart = node->startIndex;   // +0x18 (6*4)
        int32_t loopEnd = node->endIndex;       // +0x1C (7*4)
        uint32_t currentTime = ticks + timeDelta - node->sendTimestamp;  // +0x0C (3*4)
        uint32_t maxTime = *(uint32_t*)(this + 0x38);
        
        *(uint32_t*)(this + 0x44) = packetId;
        FUN_00446f80(this, packetId, state == 0);
        *(uint32_t*)(this + 0x44) = 0;
        
        int32_t i = loopStart;
        while (i != loopEnd) {
            QueryPerformanceCounter(&perfCounter);
            int32_t elapsedLow = perfCounter.LowPart - startTick.LowPart;
            uint32_t elapsedHigh = (perfCounter.HighPart - startTick.HighPart) - (perfCounter.LowPart < startTick.LowPart);
            uint64_t elapsedRaw = ((uint64_t)elapsedHigh << 32) | (uint32_t)elapsedLow;
            float elapsedSeconds = (float)(-(double)(elapsedRaw & 0x7FFFFFFFFFFFFFFF) * g_qpcToSeconds);
            
            if ((double)timeoutSeconds < elapsedSeconds || (currentTime >= maxTime)) {
                break;
            }
            
            *(uint32_t*)(this + 0x44) = packetId;
            FUN_00446f80(this, packetId, state == 0);
            *(uint32_t*)(this + 0x44) = 0;
            
            i++;
        }
        
        node->endIndex = i;
        if (i != loopEnd) {
            return;  // Timeout or limit hit, exit early
        }
        
        // Check retransmit flag
        if ((node->flags & 0x40) != 0) {
            FUN_00445ab0(this, packetId);
            node->flags &= ~0x40;
        }
        
        // Remove node from current list and move to free list
        PacketNode* prev = node->prev;   // +0x04
        PacketNode* next = node->next;   // +0x00
        
        if (prev == nullptr) {
            *(PacketNode**)(this + 0x90) = next;  // Update head
            if (next != nullptr) {
                next->prev = nullptr;
            }
        } else {
            prev->next = next;
            if (next != nullptr) {
                next->prev = prev;
            } else {
                // Update tail? Actually code sets (this+0x94) to prev if next is null
                *(PacketNode**)(this + 0x94) = prev;
                if (prev != nullptr) {
                    prev->next = 0;  // Wait, code does *prev = 0? Let me re-check
                }
            }
        }
        
        // Insert into free list (at this+0xA0/0xA4)
        node->prev = *(PacketNode**)(this + 0xA4);
        if (*(PacketNode**)(this + 0xA4) == nullptr) {
            *(PacketNode**)(this + 0xA0) = node;  // Free list head
        } else {
            (*(PacketNode**)(this + 0xA4))->next = node;  // Actually code does **(this+0xA4) = node; means set next of current tail
        }
        *(PacketNode**)(this + 0xA4) = node;  // Update free list tail
        
        if ((node->flags & 0x20) != 0) {
            *(int32_t*)(g_global + 0x9C) = *(int32_t*)(g_global + 0x9C) - 1;
            node->flags &= ~0x20;
        }
        
        node = *(PacketNode**)(this + 0x90);  // Continue with next head
    }
}