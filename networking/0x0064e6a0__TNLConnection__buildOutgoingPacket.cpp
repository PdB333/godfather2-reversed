// FUNC_NAME: TNLConnection::buildOutgoingPacket
void __thiscall TNLConnection::buildOutgoingPacket(int thisPtr, BitStream* bitStream, int* outFreeListHead)
{
    // thisPtr: +0x66 = mDebugFlag (byte)
    // +0x75 = mReliableNotifyHead (NotifyNode*)
    // +0x73 = mGhostNotifyHead
    // +0x7b = mSomeCounter (int)
    // +0x7d = mDebugLogTag (byte)

    int reliableListHead = *(int*)(thisPtr + 0x75);
    int ghostListHead = *(int*)(thisPtr + 0x73);
    NotifyNode* freeListPrev = nullptr;
    NotifyNode* freeListCurr = nullptr;
    NotifyNode* freeList = nullptr;

    // Debug logging if flag set
    if (*(char*)(thisPtr + 0x66) != 0) {
        int debugConst = -0xff24553;
        debugLog(0x20, &debugConst);
    }

    // Process reliable notify list
    int currentReliableNode = reliableListHead;
    while (currentReliableNode != 0) {
        if (bitStream->mWritePosBytes * 8 < bitStream->mMaxBitPosition) {
            // Check if we have room for a bit in the bitfield
            if (bitStream->mBitPosition + 1 > bitStream->mMaxBitPosition) {
                int newSizeBytes = (bitStream->mMaxBitPosition + 8) / 8 + 1500; // 0x5dc
                if (bitStream->mAllocatedSizeBytes < newSizeBytes) {
                    if (bitStream->mAllowRealloc != 0) {
                        bitStream->mAllocatedSizeBytes = newSizeBytes;
                        bitStream->mBuffer = realloc(bitStream->mBuffer, newSizeBytes);
                        bitStream->mWritePosBytes = newSizeBytes * 8;
                        bitStream->mMaxBitPosition = newSizeBytes * 8;
                    } else {
                        bitStream->mAllocatedSizeBytes = newSizeBytes;
                    }
                    bitStream->mOverflowFlag = 1;
                }
            } else {
                // Set bit at current position
                setBit(bitStream, bitStream->mBitPosition, 1);
                bitStream->mBitPosition++;
            }
        } else {
            break;
        }

        int savedBitPos = bitStream->mBitPosition;
        if (*(char*)(thisPtr + 0x66) != 0) {
            bitStream->mBitPosition += 16; // skip debug padding?
        }

        // Get the notify object and write its data
        NotifyNode* node = (NotifyNode*)currentReliableNode;
        int* vtable = *(int**)node;
        int typeIndex = (*this->vtable[0x50/4])();  // some type id
        int* typeData = (int*)(*(vtable[0])()) + 0x10 + typeIndex * 4;
        int data = *typeData;
        debugLog(*(char*)(thisPtr + 0x7d), &data);
        (*(void (**)(void*, BitStream*))(vtable[0] + 0xc))(thisPtr, bitStream);

        if (*(char*)(thisPtr + 0x66) != 0) {
            int restoredPos = bitStream->mBitPosition;
            bitStream->mBitPosition = savedBitPos;
            int savedEnd = restoredPos;
            debugLog(0x10, &savedEnd);
            bitStream->mBitPosition = restoredPos;
        }

        // Check if we need to stop because of overflow or full bitfield
        if (bitStream->mOverflowFlag != 0 ||
            (bitStream->mMaxBitPosition - bitStream->mBitPosition) < 128) {
            bitStream->mBitPosition = savedBitPos - 1;
            bitStream->mOverflowFlag = 0;
            break;
        }

        // Move node from reliable list to free list
        currentReliableNode = *(int*)(node + 2); // next
        *(int*)(node + 2) = 0;
        if (freeListPrev != nullptr) {
            freeListCurr->next = node;
        } else {
            freeList = node;
        }
        freeListPrev = freeList;
        freeListCurr = node;

        // Update head of reliable list
        *(int*)(thisPtr + 0x75) = currentReliableNode;
    }

    // End-of-packet handling for reliable notifies
    if (bitStream->mBitPosition + 1 <= bitStream->mMaxBitPosition || checkHasRoom(bitStream)) {
        clearBit(bitStream, bitStream->mBitPosition);
        bitStream->mBitPosition++;
    }

    // Process ghost notify list (similar but with different check)
    int ghostList = ghostListHead;
    int somePrev = -2;
    int savedGhostBitPos = 0;
    while (ghostList != 0) {
        int bitPos = bitStream->mBitPosition;
        if (bitStream->mWritePosBytes * 8 < bitPos) break;

        NotifyNode* ghostNode = (NotifyNode*)ghostList;
        if (*(int*)(thisPtr + 0x7b) + 126 < ghostNode->someData) break; // +0x7e

        if (bitPos + 1 > bitStream->mMaxBitPosition) {
            int newSize = (bitStream->mMaxBitPosition + 8) / 8 + 1500;
            if (bitStream->mAllocatedSizeBytes < newSize) {
                if (bitStream->mAllowRealloc) {
                    bitStream->mAllocatedSizeBytes = newSize;
                    bitStream->mBuffer = realloc(bitStream->mBuffer, newSize);
                    bitStream->mWritePosBytes = newSize * 8;
                    bitStream->mMaxBitPosition = newSize * 8;
                } else {
                    bitStream->mAllocatedSizeBytes = newSize;
                }
                bitStream->mOverflowFlag = 1;
            }
        } else {
            setBit(bitStream, bitPos, 1);
            bitStream->mBitPosition++;
        }

        char isSame = (ghostNode->someData == somePrev + 1) ? 1 : 0;
        somePrev = (somePrev & 0x00ffffff) | (isSame << 24);
        // Actually the decompiled code uses CONCAT31, so we approximate:
        // somePrev = (somePrev & 0x00ffffff) | (isSame << 24);

        if (bitStream->mBitPosition + 1 > bitStream->mMaxBitPosition) {
            newSize = (bitStream->mMaxBitPosition + 8) / 8 + 1500;
            if (bitStream->mAllocatedSizeBytes < newSize) {
                if (bitStream->mAllowRealloc) {
                    bitStream->mAllocatedSizeBytes = newSize;
                    bitStream->mBuffer = realloc(bitStream->mBuffer, newSize);
                    bitStream->mWritePosBytes = newSize * 8;
                    bitStream->mMaxBitPosition = newSize * 8;
                } else {
                    bitStream->mAllocatedSizeBytes = newSize;
                }
                bitStream->mOverflowFlag = 1;
            }
        } else {
            setBit(bitStream, bitStream->mBitPosition, (isSame != 0) ? 1 : 0);
            // The decompiled: if cVar6==0 then clear else set
            bitStream->mBitPosition++;
        }

        int nextParam = ghostNode->someData;
        if (*(char*)(thisPtr + 0x66) != 0) {
            bitStream->mBitPosition += 16;
        }

        int posBeforeWrite = bitStream->mBitPosition;
        int* vtable2 = *(int**)ghostNode;
        int typeIdx = (*this->vtable[0x50/4])();
        int* typeData2 = (int*)(*(vtable2[0])()) + 0x10 + typeIdx * 4;
        int data2 = *typeData2;
        debugLog(*(char*)(thisPtr + 0x7d), &data2);
        (*(void (**)(void*, BitStream*))(*vtable2 + 0xc))(thisPtr, bitStream);

        int posAfterWrite = bitStream->mBitPosition;
        int* vtableObj = *(int**)ghostNode;
        int* objPtr = *(int**)vtableObj[0]; // get object?
        if (objPtr != nullptr) {
            *(int*)(objPtr + 0x68) += 1; // statistics
            *(int*)(objPtr + 0x60) += (posAfterWrite - posBeforeWrite);
        }

        if (*(char*)(thisPtr + 0x66) != 0) {
            int savedPos2 = bitStream->mBitPosition;
            bitStream->mBitPosition = posBeforeWrite - 16;
            posBeforeWrite = savedPos2;
            debugLog(0x10, &posBeforeWrite);
            bitStream->mBitPosition = savedPos2;
        }

        savedGhostBitPos = bitPos;
        if (bitStream->mMaxBitPosition - bitStream->mBitPosition < 128) {
            bitStream->mBitPosition = savedGhostBitPos;
            bitStream->mOverflowFlag = 0;
            break;
        }

        // Move node to free list
        ghostList = *(int*)(ghostNode + 2);
        *(int*)(ghostNode + 2) = 0;
        if (freeListPrev != nullptr) {
            freeListCurr->next = ghostNode;
        } else {
            freeList = ghostNode;
        }
        freeListPrev = freeList;
        freeListCurr = ghostNode;

        *(int*)(thisPtr + 0x73) = ghostList;
    }

    // Free list processing: call a virtual on each freed node
    for (NotifyNode* node = freeList; node != nullptr; node = node->next) {
        (*(void (**)(void*))(*(int*)node + 0x1c))(thisPtr);
    }

    *outFreeListHead = freeList;

    // Final bit clearing for end-of-packet marker
    if (bitStream->mBitPosition + 1 <= bitStream->mMaxBitPosition) {
        clearBit(bitStream, bitStream->mBitPosition);
        bitStream->mBitPosition++;
        return;
    }
    int newSize = (bitStream->mMaxBitPosition + 8) / 8 + 1500;
    if (bitStream->mAllocatedSizeBytes < newSize) {
        if (bitStream->mAllowRealloc) {
            bitStream->mAllocatedSizeBytes = newSize;
            bitStream->mBuffer = realloc(bitStream->mBuffer, newSize);
            bitStream->mWritePosBytes = newSize * 8;
            bitStream->mMaxBitPosition = newSize * 8;
        } else {
            bitStream->mAllocatedSizeBytes = newSize;
        }
        bitStream->mOverflowFlag = 1;
    }
}

// Helper functions (assumed from other decompilation)
static void setBit(BitStream* bs, int bitPos, int value) {
    int byteIndex = bitPos >> 3;
    int bitShift = bitPos & 7;
    if (value) {
        bs->mBuffer[byteIndex] |= (1 << bitShift);
    } else {
        bs->mBuffer[byteIndex] &= ~(1 << bitShift);
    }
}

static void clearBit(BitStream* bs, int bitPos) {
    setBit(bs, bitPos, 0);
}

static int checkHasRoom(BitStream* bs) {
    // stub from FUN_0064b7c0
    return 0;
}

static void debugLog(int tag, void* data) {
    // stub from FUN_0064b810
}