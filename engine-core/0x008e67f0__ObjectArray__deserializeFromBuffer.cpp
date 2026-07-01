// FUNC_NAME: ObjectArray::deserializeFromBuffer
int __thiscall ObjectArray::deserializeFromBuffer(int thisPtr, int param2, short* buffer)
{
    short* count1Ptr;
    short* dataBlock;
    int i;
    int j;
    int* arrayPtr;
    int count;
    int capacity;
    int newCapacity;
    int* newArray;
    int objectHandle;
    int localData[4]; // 4 ints = 16 bytes

    // Check header type
    if (*buffer != 2) {
        return 1; // Failure or unsupported type
    }

    count1Ptr = buffer + 2; // Offset to first count (number of large blocks)
    dataBlock = buffer + 8; // Start of data blocks (after header of 8 shorts? Actually header: type(1), unknown(1?), count1(1), count2(1), then data)
    // Note: buffer[0]=type, buffer[1]=? (unused), buffer[2]=count1, buffer[3]=count2, then data starts at buffer[4]? But code uses buffer+2 and buffer+8. Let's analyze offsets:
    // buffer is short*. buffer+2 = &buffer[2] (4 bytes offset). buffer+8 = &buffer[8] (16 bytes offset). So header is 8 shorts? Actually buffer[0] and buffer[1] are first two shorts (type and something), then buffer[2] is count1, buffer[3] is count2, then buffer[4..7] are unused? Then data starts at buffer[8]. That's 8 shorts header.

    // Process first set of large blocks (each 0x60 shorts = 192 bytes)
    if (*count1Ptr != 0) {
        for (i = 0; i < (int)(unsigned short)*count1Ptr; i++) {
            objectHandle = FUN_00446100(dataBlock, 0); // Create object from dataBlock
            FUN_008e3cf0(); // Possibly notify or prepare

            // Resize dynamic array if needed
            count = *(int*)(thisPtr + 0x14);
            capacity = *(int*)(thisPtr + 0x18);
            if (count == capacity) {
                if (capacity == 0) {
                    newCapacity = 1;
                } else {
                    newCapacity = capacity * 2;
                }
                FUN_008e5cf0(newCapacity); // Reallocate array
            }

            // Add object to array
            arrayPtr = *(int**)(thisPtr + 0x10);
            arrayPtr[*(int*)(thisPtr + 0x14)] = objectHandle;
            *(int*)(thisPtr + 0x14) = *(int*)(thisPtr + 0x14) + 1;

            FUN_008e4da0(dataBlock + 8); // Cleanup or release temporary data
            dataBlock += 0x60; // Move to next block (0x60 shorts)
        }
    }

    // Process second set of small blocks (each 10 shorts = 20 bytes)
    if (buffer[3] != 0) {
        for (j = 0; j < (int)(unsigned short)buffer[3]; j++) {
            int* src = (int*)FUN_008e8cc0(dataBlock); // Get pointer to 4 ints from block
            localData[0] = src[0];
            localData[1] = src[1];
            localData[2] = src[2];
            localData[3] = src[3];
            FUN_00446100(localData, 0); // Create object from local data
            FUN_008e8fd0(dataBlock); // Free or release block
            dataBlock += 10; // Move to next block (10 shorts)
        }
    }

    return 1; // Success
}