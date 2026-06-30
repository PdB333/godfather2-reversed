// FUNC_NAME: Deserializer::readTwoArrays
void __thiscall Deserializer::readTwoArrays(OutputObject* outObj)
{
    int count;
    int* elementPtr;
    uint allocSize;
    int i;
    int j;
    
    // Read the first count (likely from stream)
    readIntFromStream();
    count = someStackInt; // This is unclear, but assume it's read from stream into local var
    if (count < 0) {
        // Error handling
        errorHandler(*this->allocator, "bad integer in %s", this->name);
    }
    
    // Allocate first array (8 bytes per element)
    allocSize = count * 8;
    if (allocSize != 0) {
        if (allocSize > 0xfffffffc) {
            errorHandler(*this->allocator, "memory allocation error: block too big");
        }
        elementPtr = (int*)(*DAT_012059dc)(0, allocSize); // malloc
        if (elementPtr == 0) {
            if (*this->allocator != 0) {
                memoryAllocationHandler();
                return;
            }
            goto zero_count;
        }
        if (*this->allocator != 0) {
            // Update allocation size tracker at allocator + 0x10 + 0x24
            *(int*)(*(int*)(*this->allocator + 0x10) + 0x24) += allocSize;
        }
    } else {
zero_count:
        elementPtr = 0;
    }
    
    outObj->array1 = elementPtr;
    outObj->array1Count = count;
    
    // Fill first array
    if (count > 0) {
        for (i = 0; i < count; i++) {
            uint8_t type;
            uint8_t* pairPtr = (uint8_t*)(outObj->array1 + i * 8);
            type = (uint8_t)readRandomByte();
            if (type == 0) {
                *(uint32_t*)pairPtr = 0; // type 0: just zero
            } else if (type == 3) {
                *(uint32_t*)pairPtr = 3;
                readIntFromStream(); // read another int? Actually reads from stack? The decompiled shows:
                // uVar5 = FUN_006418b0(); -> random byte?
                // Actually confusing. The code:
                // *puVar2 = 3;
                // FUN_00641940();
                // puVar2[1] = uStack_4;
                // So it reads a 4-byte value from stack? This is weird.
                // Better to treat as reading a value from the stream.
                *(uint32_t*)(pairPtr + 4) = readIntFromStream(); // value for type 3
            } else if (type == 4) {
                *(uint32_t*)pairPtr = 4;
                *(uint32_t*)(pairPtr + 4) = readValueForType4(); // FUN_00641a50
            } else {
                errorHandler(*this->allocator, "bad constant type (%d) in %s", type, this->name);
            }
        }
    }
    
    // Read second count
    if (this->someFlag != 0) {
        // Read 4 bytes into local_8 (big-endian?)
        readBytesIntoLocal((uint8_t*)&count, 4);
    }
    
    while (count < 0) {
        errorHandler(*this->allocator, "bad integer in %s", this->name);
    }
    
    // Allocate second array (4 bytes per element)
    allocSize = count * 4;
    if (allocSize != 0) {
        if (allocSize > 0xfffffffc) {
            errorHandler(*this->allocator, "memory allocation error: block too big");
        }
        elementPtr = (int*)(*DAT_012059dc)(0, allocSize);
        if (elementPtr != 0) {
            if (*this->allocator != 0) {
                *(int*)(*(int*)(*this->allocator + 0x10) + 0x24) += allocSize;
            }
        } else {
            if (*this->allocator != 0) {
                memoryAllocationHandler();
                return;
            }
        }
    } else {
        elementPtr = 0;
    }
    
    outObj->array2 = elementPtr;
    outObj->array2Count = count;
    
    // Fill second array
    if (count > 0) {
        for (j = 0; j < count; j++) {
            int value = readIntFromOtherFunction(); // FUN_00642070
            outObj->array2[j] = value;
        }
    }
}