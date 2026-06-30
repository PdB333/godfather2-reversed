// FUNC_NAME: StreamManager::readStreamChannel
uint __thiscall StreamManager::readStreamChannel(int channelID, char isBlocking, uint timeoutMs)
{
    // +0x4c: pointer to linked list of stream channels (StreamChannel)
    StreamChannel* pChannel = *(StreamChannel**)(this + 0x4c);
    
    // Search for channel with matching ID
    while (pChannel) {
        if (pChannel->channelID == channelID) goto found;
        pChannel = pChannel->next;
    }
    pChannel = nullptr;
    
found:
    if (!pChannel) {
        return 1; // Channel not found, return error
    }
    
    bool timedOut = false;
    LARGE_INTEGER startTime, currentTime;
    QueryPerformanceCounter(&startTime);
    uint startLow = startTime.LowPart;
    int startHigh = startTime.HighPart;
    
    if (!isBlocking) {
        goto processDeferred; // Non-blocking: skip the main read loop
    }
    
    // Main read loop with optional timeout
    do {
        do {
            // Check if current buffer is empty
            void* currentBuffer = pChannel->currentBuffer; // +0x33
            if (currentBuffer == nullptr) {
                // Try to get next buffer from the queue
                EnterCriticalSection(&pChannel->bufferCS); // +0x3a
                if (pChannel->pendingBuffers > 0) { // +0x39
                    pChannel->currentBuffer = *(void**)(pChannel->bufferArray + pChannel->bufferIndex * 4); // +0x36, +0x38
                    pChannel->bufferIndex++;
                    if (pChannel->bufferIndex > pChannel->bufferArraySize) { // +0x37
                        pChannel->bufferIndex = 0;
                    }
                    pChannel->pendingBuffers--;
                }
                LeaveCriticalSection(&pChannel->bufferCS);
                currentBuffer = pChannel->currentBuffer;
                if (currentBuffer == nullptr) {
                    goto processDeferred; // No data available
                }
            }
            
            // Process data unless channel is non-blocking (flag & 2)
            if ((pChannel->flags & 2) == 0) {
                do {
                    int bufferOffset = pChannel->bufferOffset; // +0x34
                    int* pBufData = (int*)(currentBuffer + 4) + bufferOffset;
                    if (!canReadMore(this)) {
                        return 8; // Read limit reached
                    }
                    int dataSize = *(int*)(pBufData + 1); // Assume size at offset 4
                    pChannel->bufferOffset += dataSize;
                    pChannel->totalBytesRead += dataSize;
                    *(int*)(this + 0x8C) += dataSize; // Manager total bytes
                    
                    QueryPerformanceCounter(&currentTime);
                    if (timeoutMs != 0xFFFFFFFF) {
                        int elapsed = currentTime.LowPart - startLow;
                        uint elapsedHigh = (currentTime.HighPart - startHigh) - (currentTime.LowPart < startLow);
                        // Compute elapsed time in ms using frequency conversion
                        uint msElapsed = (uint)(((longlong)elapsedHigh << 32 | elapsed) * _DAT_01163ed0); // frequency scale factor
                        if (msElapsed > timeoutMs) {
                            timedOut = true;
                            break;
                        }
                    }
                } while (pChannel->bufferOffset < 0x20000); // 128KB buffer limit?
            }
            
            // Check if buffer is full or non-blocking
            if (pChannel->bufferOffset >= 0x20000 || (pChannel->flags & 2) != 0) {
                // Release current buffer (decrement refcount)
                int* pBuf = (int*)currentBuffer;
                (*pBuf)--;
                if (*pBuf == 0) {
                    // Free buffer to the free list
                    EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x28));
                    int freeIndex = *(int*)(this + 0x24);
                    int freeSize = *(int*)(this + 0x1C);
                    if (freeIndex < freeSize) {
                        int* freeList = *(int**)(this + 0x18);
                        int offset = freeIndex;
                        *(int*)(this + 0x24) = freeIndex + 1;
                        if (freeSize <= offset) {
                            offset -= freeSize;
                        }
                        freeList[offset] = (int)pBuf;
                    }
                    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x28));
                    pChannel->bufferFreed = true;
                } else {
                    pChannel->bufferFreed = false;
                }
                pChannel->currentBuffer = nullptr;
                pChannel->bufferOffset = 0;
                
                // If buffer was freed and manager is in a state, trigger callback
                if (pChannel->bufferFreed && *(int*)(this + 0x48) != 0) {
                    if (*(int*)(*(int*)(this + 0x48) + 0xB0) == 2 &&
                        (*(byte*)(*(int*)(this + 0x48) + 0xA8) & 2) == 0) {
                        notifyReadComplete(); // FUN_004d1ab0
                    }
                }
                
                QueryPerformanceCounter(&currentTime);
            }
        } while (timeoutMs == 0xFFFFFFFF); // Loop if no timeout
        
        // Check timeout
        int elapsed = currentTime.LowPart - startLow;
        uint elapsedHigh = (currentTime.HighPart - startHigh) - (currentTime.LowPart < startLow);
        uint msElapsed = (uint)(((longlong)elapsedHigh << 32 | elapsed) * _DAT_01163ed0);
    } while (msElapsed < timeoutMs);
    
    timedOut = true;
    
processDeferred:
    // Non-blocking or blocking path
    do {
        // If channel is non-blocking and has a deferred callback, execute it
        if ((pChannel->flags & 2) != 0 && pChannel->deferredPtr != 0) {
            (**(code**)(**(int**)(this + 0x94) + 8))(pChannel->deferredPtr);
            pChannel->deferredPtr = 0;
        }
        
        // If non-blocking and not timed out, process pending buffers
        if (isBlocking == 0 && !timedOut) {
            do {
                do {
                    while (true) {
                        void* pendingItem = pChannel->pendingList; // +0x44
                        if (pendingItem == nullptr) goto cleanup;
                        if (pChannel->pendingTail == pendingItem) {
                            pChannel->pendingTail = nullptr;
                        }
                        pChannel->pendingList = *(void**)pendingItem;
                        if (pChannel->pendingList == nullptr) goto cleanup;
                        uint* refCount = (uint*)(*(int*)(pendingItem + 4));
                        if ((pChannel->flags & 2) == 0) break;
                        if (refCount != nullptr) {
                            if (*refCount < 2) {
                                (**(code**)(**(int**)(this + 0x94) + 8))(refCount);
                            } else {
                                (*refCount)--;
                            }
                            *(int*)(pendingItem + 4) = 0;
                        }
                        // Add pendingItem to manager's free list
                        *(void**)pendingItem = *(void**)(this + 0x10);
                        if (*(int*)(this + 0x10) == 0) {
                            *(void**)(this + 0x14) = pendingItem;
                        }
                        *(void**)(this + 0x10) = pendingItem;
                    }
                    // Call release on the data
                    (**(code**)(**(int**)(this + 0x94) + 0x10))(refCount);
                    refCount = (uint*)(*(int*)(pendingItem + 4));
                    if (refCount != nullptr) {
                        if (*refCount < 2) {
                            (**(code**)(**(int**)(this + 0x94) + 8))(refCount);
                        } else {
                            (*refCount)--;
                        }
                        *(int*)(pendingItem + 4) = 0;
                    }
                    *(void**)pendingItem = *(void**)(this + 0x10);
                    if (*(int*)(this + 0x10) == 0) {
                        *(void**)(this + 0x14) = pendingItem;
                    }
                    *(void**)(this + 0x10) = pendingItem;
                    QueryPerformanceCounter(&currentTime);
                } while (timeoutMs == 0xFFFFFFFF);
                int elapsed = currentTime.LowPart - startLow;
                uint elapsedHigh = (currentTime.HighPart - startHigh) - (currentTime.LowPart < startLow);
                uint msElapsed = (uint)(((longlong)elapsedHigh << 32 | elapsed) * _DAT_01163ed0);
            } while (msElapsed < timeoutMs);
        }
        
cleanup:
        // Handle channel state transitions
        if (pChannel->state == 2 && (pChannel->flags & 2) != 0) {
            handleStateTwo(); // FUN_004d1a30
        }
        
        if (pChannel->state < 0 || pChannel->state == 6) {
            if (pChannel->currentBuffer == 0 && 
                pChannel->unknown32 == 0 &&
                pChannel->deferredPtr == 0 &&
                pChannel->pendingList == 0 &&
                pChannel->pendingBuffers == 0 &&
                pChannel->totalBytesRead == pChannel->totalBytesExpected) {
                // Channel is idle, recycle it
                if (isBlocking != 0) {
                    return 0; // In blocking mode, return success? Wait, local_74 is returned, which might be 0.
                }
                // Non-blocking: add channel to recycling list
                recycleChannel(this); // FUN_004d1820
                EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x68));
                addToFreeChannelList(this, pChannel); // FUN_004d1ea0
                LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x68));
                return 0;
            }
            goto checkHasWork;
        } else {
            // Non-idle state
            if (pChannel->currentBuffer != 0 || pChannel->pendingBuffers != 0) {
                goto hasWork;
            }
        }
        
        int pendingList = pChannel->pendingList;
        if (timeoutMs != 0xFFFFFFFF) {
            QueryPerformanceCounter(&currentTime);
            int elapsed = currentTime.LowPart - startLow;
            uint elapsedHigh = (currentTime.HighPart - startHigh) - (currentTime.LowPart < startLow);
            uint msElapsed = (uint)(((longlong)elapsedHigh << 32 | elapsed) * _DAT_01163ed0);
            if ((float)(int)timeoutMs <= -((float)msElapsed)) {
                continue; // Should not happen? But original logic is confusing.
            }
        }
        
        if (hasWork || !isBlocking) {
            // Return with status flags
            uint status = 0;
            if (hasWork) {
                status |= 2;
            }
            if (pendingList) {
                status |= 4;
            }
            return status;
        }
    } while (true);
}

// Helper functions (assumed external)
bool canReadMore(void* manager); // FUN_004d0db0
void notifyReadComplete(); // FUN_004d1ab0
void handleStateTwo(); // FUN_004d1a30
void recycleChannel(void* manager); // FUN_004d1820
void addToFreeChannelList(void* manager, void* channel); // FUN_004d1ea0

// Placeholder for frequency conversion factor
extern float _DAT_01163ed0; // Performance counter frequency scale
}