// FUNC_NAME: DataParser::fillTripletArray
// Address: 0x00546960
// Role: Reads a serialized data container (binary stream with iterator) and fills an array of triplets (12 bytes each) at destination+0x14.
// Each triplet consists of three 4-byte pointers (offset 0, 4, 8). The source data defines a sequence of values and uses a switch to
// assign them to the triplet components. The iterator supports two modes: linked list (cStack_64 == 0) and bitmask-indexed (cStack_64 != 0).

void DataParser::fillTripletArray(int param_1, int destParam)
{
    int *thisPtr = (int *)this; // unaff_EDI is this pointer

    (**(code **)(*thisPtr + 0x220))(); // vtable method #0x220 – likely advance or reset iterator

    FUN_0043aff0(param_1, 0x6fd313e); // debug or setup call (e.g., set name with hash 0x6fd313e)

    // Iterator variables
    bool useBitmask;          // cStack_64, flag for iterator mode
    int bitFieldBase;         // iStack_60, base address for bitmask
    int *bucketArray;         // puStack_5c, pointer to current bucket (for linked list mode)
    uint currentIndex;        // uStack_58, current position index
    uint totalCount;          // uStack_54, total number of elements
    int *currentNode;         // ppuStack_8, current node pointer (for linked list mode)
    uint *tempPtr;            // puStack_50, temporary pointer during switch
    int *srcTriplet;          // ppuVar7, used to traverse source

    srcTriplet = currentNode;
    while (true) {
        bool continueFlag;
        if (useBitmask == false) {
            continueFlag = (*srcTriplet == 0);
        } else {
            continueFlag = (currentIndex == totalCount);
        }
        if (continueFlag) break;

        uint *valuePtr;
        if (useBitmask == false) {
            valuePtr = (uint *)srcTriplet;
        } else {
            valuePtr = &tempPtr; // points to puStack_50 (stack variable)
        }

        // Check a magic/type field; note: *(short *)(valuePtr + 6) is offset 6 from the node
        // If the short at offset 6 equals 0x25e3, then the next field is a short (compact), else it's a full pointer.
        uint val;
        if (*(short *)((int)valuePtr + 6) == 0x25e3) {
            val = (uint)*(ushort *)(valuePtr + 1); // offset 4 from node? but valuePtr is a pointer, so valuePtr[1] is 4 bytes, careful: casting to ushort*.
            // Actually: valuePtr is uint*, but we access valuePtr+1 as ushort* – likely reading a short at offset 4.
        } else {
            val = *((uint *)valuePtr + 1); // offset 4 as full uint
        }

        // Destination array base: destParam + 0x14
        uint *tripletArray = *(uint **)(destParam + 0x14); // +0x14: pointer to array of triplets (each 12 bytes)

        switch (val) {
        case 0: // Set offset 0 for all indices from 0 to count-1
        {
            uint fillValue = *((uint *)valuePtr + 2); // offset 8 value
            uint count = (**(code **)(*thisPtr + 0x228))(0); // vtable method #0x228 – getCount?
            byte idx = 0;
            if (count != 0) {
                uint i = 0;
                do {
                    idx = idx + 1;
                    tripletArray[i * 3 + 0] = fillValue; // offset 0 of triplet
                    i = (uint)idx;
                } while (i < count);
            }
            break;
        }
        case 1: // Set offset 0 for a range from current index to total
        {
            uint fillValue = *((uint *)valuePtr + 2);
            uint totalElements = (**(code **)(*thisPtr + 0x220))(); // get total count
            uint curIdx = (**(code **)(*thisPtr + 0x228))(0); // get current index (0..total)
            byte startIdx = (byte)curIdx;
            uint idx = (uint)startIdx;
            while (idx < totalElements) {
                tripletArray[idx * 3 + 0] = fillValue;
                idx = (uint)((byte)(curIdx + 1));
                curIdx = idx;
            }
            break;
        }
        case 2: // Set offset 4 for all indices 0..count-1
        {
            uint fillValue = *((uint *)valuePtr + 2);
            uint count = (**(code **)(*thisPtr + 0x228))(0);
            byte idx = 0;
            if (count != 0) {
                uint i = 0;
                do {
                    idx = idx + 1;
                    tripletArray[i * 3 + 1] = fillValue; // offset 4
                    i = (uint)idx;
                } while (i < count);
            }
            break;
        }
        case 3: // Set offset 4 for a range
        {
            uint fillValue = *((uint *)valuePtr + 2);
            uint totalElements = (**(code **)(*thisPtr + 0x220))();
            uint curIdx = (**(code **)(*thisPtr + 0x228))(0);
            byte startIdx = (byte)curIdx;
            uint idx = (uint)startIdx;
            while (idx < totalElements) {
                tripletArray[idx * 3 + 1] = fillValue;
                idx = (uint)((byte)(curIdx + 1));
                curIdx = idx;
            }
            break;
        }
        case 4: // Set offset 8 for all indices
        {
            uint fillValue = *((uint *)valuePtr + 2);
            uint count = (**(code **)(*thisPtr + 0x228))(0);
            byte idx = 0;
            if (count != 0) {
                uint i = 0;
                do {
                    idx = idx + 1;
                    tripletArray[i * 3 + 2] = fillValue; // offset 8
                    i = (uint)idx;
                } while (i < count);
            }
            break;
        }
        case 5: // Set offset 8 for a range
        {
            uint fillValue = *((uint *)valuePtr + 2);
            uint totalElements = (**(code **)(*thisPtr + 0x220))();
            uint curIdx = (**(code **)(*thisPtr + 0x228))(0);
            byte startIdx = (byte)curIdx;
            uint idx = (uint)startIdx;
            while (idx < totalElements) {
                tripletArray[idx * 3 + 2] = fillValue;
                idx = (uint)((byte)(curIdx + 1));
                curIdx = idx;
            }
            break;
        }
        }

        // Advance iterator
        if (useBitmask == false) {
            // Linked list mode: each node contains a self-relative offset to the next node
            int relativeOffset = *(int *)srcTriplet;
            if (relativeOffset < 0) {
                currentNode = (int *)((int)srcTriplet + relativeOffset);
                FUN_0043b140(); // some operation (e.g., pop stack or reset iterator)
                srcTriplet = currentNode;
            } else if ((uint)relativeOffset < totalCount - 1) {
                currentIndex = currentIndex + 1;
                currentNode = (int *)((int)srcTriplet + relativeOffset);
                srcTriplet = (int *)((int)srcTriplet + relativeOffset);
            } else {
                currentNode = (int *)&DAT_01163cf8; // sentinel address
                srcTriplet = (int *)&DAT_01163cf8;
            }
        } else {
            // Bitmask mode: advance by index, check bitmask to see if element exists
            currentIndex = currentIndex + 1;
            if (currentIndex != totalCount) {
                uStack_4c = (short)currentIndex;
                // Bitmask: base at bitFieldBase, each bit indicates presence
                byte bitmask = *(byte *)((currentIndex >> 3) + bitFieldBase);
                bool bitSet = (bitmask & (1 << (currentIndex & 7))) != 0;
                if (bitSet) {
                    tempPtr = bucketArray; // next bucket from bucket array
                    uStack_48 = *bucketArray;
                    bucketArray = bucketArray + 1;
                } else {
                    tempPtr = 0;
                    uStack_48 = 0;
                }
            }
        }
    }
    return;
}