// FUNC_NAME: GhostManager::unpackGhostData
bool GhostManager::unpackGhostData(GhostPacketContext* context) {
    int* inputBuffer = context->buffer;            // param_1
    int  baseOffset = *inputBuffer;                // original pointer to raw data
    int  readOffset = inputBuffer[4];              // current read position in raw data
    int  totalSize = inputBuffer[?];               // total size? Not stored, computed from inputBuffer[?]
    int  itemCount = 0;
    int  maxIndex  = 0;

    // First pass: read item sizes and compute max index
    {
        int currentOffset = readOffset;
        int endOffset = totalSize; // Actually derived from previous reads
        int temp;

        // The original code had a loop reading 4-byte sizes, building maxIndex
        while (currentOffset < endOffset) {
            // Read a 4-byte value (size of a chunk)
            temp = *(int*)((char*)baseOffset + currentOffset);
            currentOffset += 4;

            // Update max index (the size is actually an index? or a length?)
            if (maxIndex < temp) {
                maxIndex = temp;
            }

            // Read a 4-byte value that is the next chunk offset relative to currentOffset-8? Actually reads 4 bytes as offset from currentOffset
            int nextOffset = *(int*)((char*)baseOffset + currentOffset);
            currentOffset = nextOffset; // next chunk starts here
            itemCount++;
        }
    }

    // Ensure capacity for the first array (index -> ???) stored at +0x1c (data) and +0x24 (capacity)
    int* self = (int*)context->self; // piVar3[7] points to some object
    if (self[0x24] < itemCount + 1) {
        self[0x1c] = growArray(self[0x1c], &self[0x24]); // FUN_005d1a40
    }
    self[0x20] = itemCount + 1; // count for first array

    // Ensure capacity for second array (index -> data) at +0x10 (data) and +0x18 (capacity)
    if (self[0x18] < maxIndex + 1) {
        self[0x10] = resizeArray(self[0x10], maxIndex + 1, 4, &self[0x14], &self[0x18]); // FUN_005c27a0
    }
    self[0x14] = maxIndex + 1; // count for second array

    // Reset second array count to 0 (??? possibly for reinitialization)
    self[0x14] = 0;

    // Reset first array count to 0
    self[0x20] = 0;

    // Second pass: read per-index data
    int currentOffset = readOffset;
    int endOffset = ...; // unknown, derived from buffer size
    int index = 0;
    int dataOffset = 0; // offset into the second array's data storage

    while (currentOffset < endOffset) {
        // Read index for this entry
        int idx = *(int*)((char*)baseOffset + currentOffset);
        currentOffset += 4;

        // Read size of this entry's data (minus 8? Actually size = (nextOffset - currentOffset)?? 
        int size = *(int*)((char*)baseOffset + currentOffset) - 8; // The original reads a 4-byte value and subtracts 8
        currentOffset += 4;

        // Update max index if needed
        if (dataCount < idx) {
            dataCount = idx; // local_18
        }

        // Store the entry's data index into the second array at position idx
        if (self[0x18] < idx + 1) {
            self[0x10] = resizeArray(self[0x10], idx + 1, 4, &self[0x14], &self[0x18]);
        }
        if (self[0x14] <= idx) {
            self[0x14] = idx + 1;
        }
        *(int*)(self[0x10] + idx * 4) = index + 1; // Store index starting from 1

        // Ensure first array capacity for this index
        if (self[0x24] < (int)(index + 1)) {
            self[0x1c] = growArray(self[0x1c], &self[0x24]);
        }
        // Set the first array's count (it's actually a pointer to an array of variable-length objects)
        self[0x20] = (int*)(index + 1); // Assigns pointer value? This is suspicious: the original assigns param_1 (which is (int*)1) into self[0x20]
        // Actually the original: *(int **)(iVar9 + 0x20) = param_1; where param_1 starts at 1 and increments each iteration.
        // So self[0x20] stores a pointer that increments by 1 each iteration? That's weird.

        // Now read the actual data for this entry
        unsigned int actualSize = size; // from earlier
        char* entryData = (char*)((char*)baseOffset + currentOffset);
        currentOffset += 8; // skip the 8 bytes we already read for size? Actually original advances by 8 after reading size
        // But the size includes the 8 header bytes? The original: sVar10 = local_2c - 8; and piVar3[4] = iVar1 + 8; so it skips 8 bytes for header.

        // Allocate a buffer for this entry
        void* dataBuffer = allocateFromPool(actualSize); // calls a function that returns pointer
        memcpy(dataBuffer, entryData, actualSize);

        // Store entry in the first array (which seems to hold something else)
        // The first array is at self[0x1c] and each entry is 0x10 bytes? Actually the code uses puVar12 and offsets +0x10 per iteration
        int* firstArray = (int*)self[0x1c];
        int firstArrayOffset = dataOffset; // increments by 0x10 each iteration
        firstArray[firstArrayOffset + 0] = self[0]; // copy from self[0] (some ID?)
        firstArray[firstArrayOffset + 1] = (int)dataBuffer;
        firstArray[firstArrayOffset + 2] = actualSize;
        firstArray[firstArrayOffset + 3] = 0; // offset counter inside dataBuffer

        // Process the sub-elements within dataBuffer
        if (actualSize > 0) {
            do {
                char* currentData = (char*)dataBuffer + firstArray[firstArrayOffset + 3];
                // Each sub-element has a header: at +0x38 a unique ID, at +0x3c a count, at +0x40 data
                int uniqueId = ++globalIdCounter; // DAT_0103ae2c
                *(int*)(currentData + 0x38) = uniqueId;

                // Copy sub-element data to a global list (maybe a debug log?)
                size_t subDataSize = *(int*)(currentData + 0x3c) * 8;
                // The global allocator at DAT_01206880+0x14 is a stack-like buffer
                int* allocator = (int*)(DAT_01206880 + 0x14);
                // It stores function pointer? Actually it stores a vtable? The code:
                *(undefined***)*allocator = &PTR_FUN_01126ac8;
                allocator += 4;
                *allocator = uniqueId;
                allocator += 4;
                *allocator = subDataSize;
                allocator += 4;
                *allocator = 0x10; // alignment?
                allocator += 4;
                void* copyDest = (void*)(((int)allocator + 0xf) & 0xfffffff0);
                allocator = (int*)copyDest;
                memcpy(copyDest, currentData + 0x40, subDataSize);
                allocator += subDataSize / 4;
                DAT_01206880+0x14 = (int)allocator;

                // Advance to next sub-element
                int nextOffset = *(int*)(currentData) + firstArray[firstArrayOffset + 3]; // ??? The original: iVar7 = *(int *)(puVar12[3] + puVar12[1]) + puVar12[3];
                firstArray[firstArrayOffset + 3] = nextOffset;
            } while (nextOffset < actualSize);
        }

        // Advance to next entry
        index++;
        dataOffset += 0x10; // Each entry in first array is 16 bytes
    }

    return true; // The function returns 1 (true) in the original
}