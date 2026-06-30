// FUNC_NAME: StreamReader::readVariantArray
void StreamReader::readVariantArray(void* outputStruct) {
    // Context: reader object (in_EAX) with fields:
    // +0x00: memory allocator context (used for error reporting and allocation tracking)
    // +0x0C: flag indicating whether to read additional dword array (in_EAX[3])
    // +0x10: name string for error messages (in_EAX[4])
    int allocatedCount;  // local_8
    int* memoryTracker;  // for tracking allocation size

    // Read the count of variants
    allocatedCount = this->readInt();  // FUN_00641940
    if (allocatedCount < 0) {
        this->reportError("bad integer in %s", this->nameString);
    }

    int allocCtx = *(int*)this;  // *in_EAX
    unsigned int arraySize = allocatedCount * 8;
    if (arraySize == 0) {
        allocatedCount = 0;
    } else {
        if (arraySize > 0xfffffffc) {
            this->reportError("memory allocation error: block too big");
        }
        int* buffer = (int*)gAllocator(0, arraySize);  // DAT_012059dc
        if (buffer == 0) {
            if (allocCtx != 0) {
                this->handleAllocFailure();  // FUN_00635a80
                return;
            }
            allocatedCount = 0;
        } else {
            if (allocCtx != 0) {
                memoryTracker = (int*)(*(int*)(allocCtx + 0x10) + 0x24);
                *memoryTracker += arraySize;
            }
        }
    }
    *(int*)(outputStruct + 0x8) = buffer;
    *(int*)(outputStruct + 0x28) = allocatedCount;

    // Fill variant array
    for (int i = 0; i < allocatedCount; i++) {
        int* variant = (int*)(*(int*)(outputStruct + 0x8) + i * 8);
        unsigned int type = this->readByte();  // FUN_006418b0
        type &= 0xff;
        if (type == 0) {
            variant[0] = 0;
        } else if (type == 3) {
            variant[0] = 3;
            this->readInt();  // FUN_00641940 (consumes integer, maybe for alignment)
            variant[1] = this->stackValue;
        } else if (type == 4) {
            variant[0] = 4;
            variant[1] = this->readValue();  // FUN_00641a50
        } else {
            this->reportError("bad constant type (%d) in %s", type, this->nameString);
        }
    }

    // Conditional second array
    if (*(int*)(this + 0xC) != 0) {  // in_EAX[3]
        char* dest = ((char*)&allocatedCount + 3);
        int bytes = 4;
        do {
            *dest = this->readByte();  // FUN_006418b0
            dest--;
            bytes--;
        } while (bytes != 0);
        // Now allocatedCount holds the count for the second array (reused)
    }

    // Validate second count
    while (allocatedCount < 0) {
        this->reportError("bad integer in %s", this->nameString);
        // loop continues as local_8 is updated? Actually infinite loop if negative
    }

    // Allocate second array
    allocCtx = *(int*)this;
    arraySize = allocatedCount * 4;
    if (arraySize != 0) {
        if (arraySize > 0xfffffffc) {
            this->reportError("memory allocation error: block too big");
        }
        int* secondBuffer = (int*)gAllocator(0, arraySize);
        if (secondBuffer != 0) {
            if (allocCtx != 0) {
                memoryTracker = (int*)(*(int*)(allocCtx + 0x10) + 0x24);
                *memoryTracker += arraySize;
            }
            // Continue to fill
        } else {
            if (allocCtx != 0) {
                this->handleAllocFailure();
                return;
            }
            secondBuffer = 0;
        }
    } else {
        secondBuffer = 0;
    }
    *(int*)(outputStruct + 0x10) = secondBuffer;
    *(int*)(outputStruct + 0x34) = allocatedCount;

    // Read elements into second array
    for (int i = 0; i < allocatedCount; i++) {
        int value = this->readDword();  // FUN_00642070
        *(int*)(*(int*)(outputStruct + 0x10) + i * 4) = value;
    }
}