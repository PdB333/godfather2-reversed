// FUN_0044e3e0: CharacterData::parseDataBlock
void CharacterData::parseDataBlock(void) {
    // local variable declarations with inferred types
    int* pData;            // pointer to data node array
    int** ppNodeArray;     // current node pointer
    int** ppBaseArray;     // base of node array
    uint nodeIndex;        // index into node array
    uint nodeCount;        // total nodes
    bool bIsBitFlagMode;   // flag for bit-array iteration mode
    int* pBitArray;        // pointer to bitmask array
    int* pCurrentElement;  // pointer to current element in data stream
    int** ppTempNode;      // temporary node pointer for conditionals
    int* pTempData;        // temporary data pointer
    uint currentBit;       // for bitmask indexing
    undefined8 uVar8;      // temporary 8-byte value
    int* pVarTemp;         // temporary pointer
    int* pNullPtr;         // nullptr (0x0)
    int iVar;              // temporary integer
    bool bFlag;            // boolean flag for loop condition

    // Local structures
    struct LocalDataBuffer { // size 0x3c+4? 
        int val0;  // multiple ints
        int val1;
        int val2;
        int val3;
        int val4;
        int val5;
        int val6;
        int val7;
        int val8;
        int val9;
        int val10;
        int val11;
        int val12;
        int val13;
        int val14;
        int val15;
        int val16;
    } localBuf;

    int* localPtr; // unused pointer

    // Initial hash/string lookup
    hashLookup(this, 0x774eb208); // likely maps a hash to internal data

    pNullPtr = nullptr;
    ppBaseArray = ppTempNode; // initial assignment from uninitialized local_5c? Actually local_5c is uninitialized, but might be from stack
    nodeIndex = nodeCount; // similarly local_ac, local_a8

    while (true) {
        // Determine iteration mode and check loop condition
        if (!bIsBitFlagMode) {
            bFlag = (*ppTempNode == nullptr);
        } else {
            bFlag = (nodeIndex >= nodeCount);
        }
        if (bFlag) break;

        // Select current node pointer based on mode
        if (!bIsBitFlagMode) {
            ppTempNode = ppBaseArray; // in linear mode, node pointer is ppBaseArray
        } else {
            // bit mode: ppTempNode already set from earlier
        }

        // Check if current node has a special type tag (0x25e3)
        if (*(short*)((int)ppTempNode + 6) == 0x25e3) {
            // Type tag: 0x25e3 indicates a short reference (index?)
            pData = (int*)(uint)*(unsigned short*)(ppTempNode + 1);
        } else {
            pData = ppTempNode[1];
        }

        if (pData == nullptr) {
            // Type 0: load a set of attributes from external source
            localBuf.val13 = DAT_00e2b1a4; // global constant
            int tempVal = DAT_00e2b1a4;

            // Zero out local buffer with null pointers
            for (int i = 0; i < 16; i++) {
                // Actually the code sets specific locals; we'll mimic
            }

            // Call a function that fills localBuf
            fillLocalBuffer(&localBuf); // FUN_0043ac60

            // Copy local buffer fields to object offsets
            *(int*)(this + 0xa0) = localBuf.val0;
            *(int*)(this + 0xa4) = localBuf.val1;
            *(int*)(this + 0xa8) = localBuf.val2;
            *(int*)(this + 0xb0) = localBuf.val3;
            *(int*)(this + 0xb4) = localBuf.val4;
            *(int*)(this + 0xb8) = localBuf.val5;
            *(int*)(this + 0xc0) = localBuf.val6;
            *(int*)(this + 0xc4) = localBuf.val7;
            *(int*)(this + 0xc8) = localBuf.val8;
            *(int*)(this + 0xd0) = localBuf.val9;
            *(int*)(this + 0xd4) = localBuf.val10;
            *(int**)(this + 0xac) = nullptr;
            *(int**)(this + 0xbc) = nullptr;
            *(int**)(this + 0xcc) = nullptr;
            *(int*)(this + 0xd8) = localBuf.val11;
            *(int*)(this + 0xdc) = tempVal;

            // Initialize a sub-structure at this+0xe0 from the region at this+0xa0
            initSubStruct((void*)(this + 0xa0), (void*)(this + 0xe0)); // FUN_0056c640

            // Reset iteration variables (actual code resets them)
            ppBaseArray = ppTempNode; // and uVar4 = local_ac
        }
        else if (pData == (int*)0x1) {
            // Type 1: set a boolean flag at offset 0x12c
            *(int*)(this + 0x12c) = (ppTempNode[2] != nullptr) ? 1 : 0;
        }
        else if (pData == (int*)0x2) {
            // Type 2: load a 12-byte structure (Vector3 + pointer?) into offsets 0x120-0x128
            if (*(short*)((int)ppTempNode + 6) == 0x25e3) {
                int* pTemp = ppTempNode[0];
                if (pTemp == nullptr) {
                    uVar8 = 0; // two 4-byte zeros
                    *(int**)(&uVar8 + 1) = nullptr; // local_bc
                } else {
                    uVar8 = *(undefined8*)((int)ppTempNode[2] + (int)pTemp);
                    *(int**)((int)&uVar8 + 8) = *(int**)((int)ppTempNode[2] + (int)pTemp + 8);
                }
            } else {
                uVar8 = *(undefined8*)(ppTempNode + 2);
                *(int**)((int)&uVar8 + 8) = ppTempNode[4];
            }
            *(int*)(this + 0x120) = (int)uVar8;
            *(int*)(this + 0x124) = *(int*)((int)&uVar8 + 4);
            *(int**)(this + 0x128) = *(int**)((int)&uVar8 + 8);
        }

        // Advance to next node based on mode
        if (!bIsBitFlagMode) {
            if ((int)nodeIndex < 0) {
                // Negative index: jump to next node via dereferencing
                ppBaseArray = (int**)((int)ppBaseArray + (int)*ppBaseArray);
                callIterator(); // FUN_0043b140
                ppTempNode = ppBaseArray;
                nodeIndex = nodeCount; // reset from local_ac?
            } else if ((int)nodeIndex < (int)(nodeCount - 1)) {
                nodeIndex++;
                ppBaseArray = (int**)((int)ppBaseArray + (int)*ppBaseArray);
                ppTempNode = ppBaseArray;
                uiVar4 = nodeIndex;
            } else {
                ppBaseArray = &DAT_01163cf8; // sentinel/end marker
                ppTempNode = &DAT_01163cf8;
            }
        } else {
            nodeIndex++;
            if (nodeIndex != nodeCount) {
                // Set current node from bit array
                if ((*(byte*)((nodeIndex >> 3) + pBitArray) & (1 << (nodeIndex & 7))) == 0) {
                    // Bit not set: use next element from data stream
                    *(int*)&localBuf = *pCurrentElement; // store in some local struct
                    ppTempNode = pCurrentElement;
                    pCurrentElement++;
                } else {
                    ppTempNode = nullptr; // skip this index
                }
            }
        }
    }
    return;
}