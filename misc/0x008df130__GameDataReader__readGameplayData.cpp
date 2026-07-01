// FUNC_NAME: GameDataReader::readGameplayData
void __thiscall GameDataReader::readGameplayData(void *buffer) {
    char isEnd;
    int dataType;
    int chunkPtr;
    int arrayPtr;

    // Initialize stream from buffer
    initReadStream(buffer);
    // Verify magic/checksum (0xcec4e017)
    verifyChecksum(buffer, 0xcec4e017);

    do {
        isEnd = isStreamEnd();
        if (isEnd != '\0') {
            return;
        }
        advanceStream(); // Prepare next chunk?
        dataType = readDataTypeTag(); // Returns 0..0xb

        switch (dataType) {
        case 0: {
            // Read and store a vector/position into field at +0x280
            chunkPtr = readNextChunk(); // Returns pointer to read data
            uint vec = readVectorComponent(chunkPtr);
            *(uint *)(this + 0x280) = convertVector(vec);
            break;
        }
        case 1: {
            // Read a value into field at +0x284
            chunkPtr = readNextChunk();
            *(uint *)(this + 0x284) = *(uint *)(chunkPtr + 8);
            break;
        }
        case 2: {
            // Read a value into field at +0x288
            chunkPtr = readNextChunk();
            *(uint *)(this + 0x288) = *(uint *)(chunkPtr + 8);
            break;
        }
        case 3: {
            // Read a value into field at +0x28c
            chunkPtr = readNextChunk();
            *(uint *)(this + 0x28c) = *(uint *)(chunkPtr + 8);
            break;
        }
        case 4: {
            // Process array pointed by +0x298 (base)
            arrayPtr = *(int *)(this + 0x298);
            goto processArrayElement;
        }
        case 5: {
            // Write data to array element pointed by +0x2a4 (offset 0)
            chunkPtr = readNextChunk();
            **(uint **)(this + 0x2a4) = *(uint *)(chunkPtr + 8);
            break;
        }
        case 6: {
            // Process array at +0x298 + 0x10
            arrayPtr = *(int *)(this + 0x298) + 0x10;
            goto processArrayElement;
        }
        case 7: {
            // Write data to array element pointed by +0x2a4 (offset 4)
            chunkPtr = readNextChunk();
            *(uint *)(*(int *)(this + 0x2a4) + 4) = *(uint *)(chunkPtr + 8);
            break;
        }
        case 8: {
            // Process array at +0x298 + 0x20
            arrayPtr = *(int *)(this + 0x298) + 0x20;
            goto processArrayElement;
        }
        case 9: {
            // Write data to array element pointed by +0x2a4 (offset 8)
            chunkPtr = readNextChunk();
            *(uint *)(*(int *)(this + 0x2a4) + 8) = *(uint *)(chunkPtr + 8);
            break;
        }
        case 10: {
            // Process array at +0x298 + 0x30
            arrayPtr = *(int *)(this + 0x298) + 0x30;
            goto processArrayElement;
        }
        case 0xb: {
            // Write data to array element pointed by +0x2a4 (offset 0xc)
            chunkPtr = readNextChunk();
            *(uint *)(*(int *)(this + 0x2a4) + 0xc) = *(uint *)(chunkPtr + 8);
            break;
        }

processArrayElement:
            // Read data into the array element at arrayPtr
            readNextChunk(arrayPtr);
            finalizeArrayElement(arrayPtr); // Process the element (e.g., push to list)
            break;
        }
    } while (true);
}