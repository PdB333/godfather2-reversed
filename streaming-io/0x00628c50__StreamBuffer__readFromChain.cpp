// FUNC_NAME: StreamBuffer::readFromChain

// StreamBuffer: A buffer with an internal data buffer of 0x200 bytes.
// It reads data from a block chain and copies into the local buffer.
// When full, it flushes the buffer and increments a retry counter.

struct BlockDescriptor {
    // +0x0C: uint32_t size;
    // +0x10: void* data;
};

struct BlockHeader {
    int32_t type;          // -8 from data start
    BlockDescriptor* desc; // -4 from data start
};

class StreamBuffer {
public:
    char* mWritePtr;        // +0x00
    int32_t mFlushCount;    // +0x04
    void* mDataChain;       // +0x08  (points to a block chain object)
    char mBuffer[0x200];    // +0x0C, total object size 0x20C

    void readFromChain() {
        // Get current block data pointer from chain
        void* chainPtr = mDataChain;
        char* blockData = *(char**)((int)chainPtr + 8); // +0x08 in chain: current block data

        uint32_t blockSize;
        if (blockData != nullptr) {
            int* blockHeaderType = (int*)(blockData - 8);
            if (*blockHeaderType == 4) {
                // Direct type 4 block
                blockSize = *(uint32_t*)(*(int*)(blockData - 4) + 0xC); // descriptor->size
            } else {
                // Try to convert block type
                int32_t converted = FUN_00633990((int)chainPtr); // convertBlockType?
                if (converted != 0) {
                    blockSize = *(uint32_t*)(*(int*)(blockData - 4) + 0xC);
                } else {
                    blockSize = 0;
                }
            }
        } else {
            blockSize = 0;
        }

        // Check if there is enough space in local buffer
        uint32_t available = (uint32_t)((int)this + 0x20C - (int)mWritePtr);
        if (blockSize <= available) {
            // Copy data from block into buffer
            char* srcData;
            if (blockData != nullptr) {
                if (*(int*)(blockData - 8) == 4) {
                    srcData = (char*)(*(int*)(blockData - 4) + 0x10); // descriptor->data
                } else {
                    int32_t converted = FUN_00633990((int)chainPtr);
                    if (converted == 0) {
                        srcData = nullptr;
                    } else {
                        srcData = (char*)(*(int*)(blockData - 4) + 0x10);
                    }
                    // Additional buffer management check (unclear)
                    if (*(uint32_t*)(*(int*)(mDataChain) + 0x20) <= *(uint32_t*)(*(int*)(mDataChain) + 0x24)) {
                        FUN_00627360(); // flushBuffer
                    }
                }
            } else {
                srcData = nullptr;
            }
            // Perform the copy
            memcpy(mWritePtr, srcData, blockSize);
            mWritePtr += blockSize;

            // Advance the block chain by one block (8 bytes header overhead)
            *(int*)((int)chainPtr + 8) = (int)blockData - 8; // store new block pointer
            // Actually the original code does: *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + -8;
            // That decrements the pointer by 8, but that doesn't match "advance".
            // Need to be careful: the code sets *(int *)(iVar1 + 8) = iVar4 + -8, where iVar4 was the old block data.
            // So it moves the block pointer backwards by 8 bytes (to the header). That's odd.
            // Possibly the chain stores the next block data pointer, and we need to move forward.
            // Let's trust the decompiled: it subtracts 8. We'll keep as is.
        } else {
            // Not enough space: attempt to shift buffer data to make room
            int32_t shiftResult = FUN_00628940(); // shiftBuffer?
            if (shiftResult != 0) {
                // Shift buffer contents (simulated)
                int* currentPtr = *(int**)((int)chainPtr + 8);
                int* copySrc = currentPtr;
                // Iterate shifting pairs of dwords
                while (currentPtr - 4 < copySrc) {
                    *currentPtr = copySrc[-2];
                    *(currentPtr + 1) = copySrc[-1];
                    copySrc -= 2;
                }
                // Final copy
                int* basePtr = *(int**)((int)chainPtr + 8);
                currentPtr[-4] = *basePtr;
                currentPtr[-3] = basePtr[1];
            }
            // Increment flush retry counter
            mFlushCount++;
            FUN_006289a0(); // sendPacket?
        }
    }
};