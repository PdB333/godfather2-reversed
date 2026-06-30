// FUNC_NAME: BitStreamContext::initializeBuffer
int BitStreamContext::initializeBuffer(int numBits, int* data, BitStreamOutput* output) {
    uint* tempPtr;
    int result;
    void* allocatedMemory;
    byte bitOffset;
    uint current, next;
    long long contextPtr;

    if (numBits < 1) {
        // Reset path: call some backend reset, clear output structure
        result = resetContext(); // FUN_00665ce0
        if (output != nullptr) {
            output->flags = 0;             // offset +0 (4 bytes)
            output->bufferOffset = 0;      // offset +4 (4 bytes)
            memset(output->dataBuffer, 0, output->bufferSize * 4); // offset +0xC points to buffer, offset+4 is count
        }
        return result;
    }

    // Allocate 64-byte context structure
    allocatedMemory = calloc(4, 0x40); // 4*64 = 256? Actually calloc(4,0x40) allocates 4*64=256 bytes? But size is 0x40 -> 64, so calloc(4,64) allocates 4*64=256 bytes? Wait, calloc(4,0x40) = 4*64 = 256 bytes. That seems large. Possibly it's calloc(1,0x40) but Ghidra shows 4,0x40. Might be a parameter order issue. Assuming it's calloc(num,size), so 4*64=256. Hmm.
    // Let's keep as is.
    if (allocatedMemory == nullptr) {
        return -2; // memory allocation failure
    }

    contextPtr = ((uint64_t)allocatedMemory) << 32; // store pointer in high 32 bits of 64-bit value

    // Condition: output is null or some validation function succeeds, and resetContext succeeds
    if ((output == nullptr || (result = validateBuffer(numBits)) == 0) && // FUN_00668920
        (result = resetContext()) == 0) {

        // If numBits > 27, allocate additional tables
        if (numBits > 27) {
            allocateBitTables(numBits / 28); // FUN_0066a4d0
        }

        // Process bit packing if numBits not evenly divisible by 28
        if (numBits % 28 != 0) {
            int count = *data; // first value of data is count of elements?
            bitOffset = (byte)(numBits % 28);
            uint mask = (1 << (bitOffset & 0x1f)) - 1;
            uint* currentPtr = (uint*)(data[3] - 4 + count * 4); // point to end of buffer
            current = 0;
            while (count > 0) {
                count--;
                next = current << (28 - bitOffset); // shift previous leftover
                current = *currentPtr & mask;
                *currentPtr = (*currentPtr >> bitOffset) | next;
                currentPtr--;
            }
        }

        beginCriticalSection(); // FUN_00665b10
        if (output != nullptr) {
            output->context = 0x4000000000; // some magic constant
            output->memoryHandle = contextPtr; // store the allocated pointer with shift
        }
        endCriticalSection(); // FUN_00665b40
        return 0;
    } else {
        endCriticalSection(); // FUN_00665b40
        return result; // return error code
    }
}