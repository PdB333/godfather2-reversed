// FUNC_NAME: GameWorld::initializeBehaviorTable
uint* GameWorld::initializeBehaviorTable(int mode)
{
    // Global flag: DAT_01205358 (0x01205358) - multiplayer? Single player?
    bool bIsSinglePlayer = (g_isSinglePlayer == 0);

    // Get the process/engine global from FS segment
    int* pProcess = *(int**)(__readfsdword(0x2c));
    int* pEngine = *(int**)(*pProcess + 0x24); // engine singleton

    // Behavior table (array of command entries) from engine
    uint* pBehaviorTable = *(uint**)(pEngine + 0x178);

    // Store the mode at offset +0x39f8
    *(int*)(this + 0x39f8) = mode;

    // Add basic behavior entries based on single/multiplayer
    if (bIsSinglePlayer)
    {
        addBehavior(pBehaviorTable, this, (code*)0x0042d9e0, 0, 0, 0);
        addBehavior(pBehaviorTable, this, (code*)0x0042c9f0, 0, 1, 0);
    }
    else // multiplayer
    {
        if (*pBehaviorTable != 0)
        {
            uint* pEntry = (uint*)pBehaviorTable[1];
            *(code**)(pEntry + 1) = (code*)0x0042d9c0; // +4
            *(int*)(pEntry + 3) = (int)this;           // +0xc
        }
        addBehavior(pBehaviorTable, this, (code*)0x0042c9e0, 0, 1, 0);
    }

    // Add more behavior entries; index order differs
    uint nextIndex = 3;
    if (bIsSinglePlayer)
    {
        addBehavior(pBehaviorTable, this, (code*)0x0042dd40, 0, nextIndex, 0);
    }
    else
    {
        addBehavior(pBehaviorTable, this, (code*)0x0042dcc0, 0, 3, 0);
        addBehavior(pBehaviorTable, this, (code*)0x0042dda0, 0, 4, 0);
        addBehavior(pBehaviorTable, this, (code*)0x0042ddb0, 0, 5, 0);
        nextIndex = 6;
        addBehavior(pBehaviorTable, this, (code*)0x0042ddc0, 0, nextIndex, 0);
    }

    // Entry index 8 always added
    addBehavior(pBehaviorTable, this, (code*)0x0042ddd0, 0, 8, 0);

    // If flag bit 3 is clear, add more specific behavior handlers
    if ((*(uint*)(this + 0x3af8) >> 3 & 1) == 0)
    {
        addBehavior(pBehaviorTable, this, (code*)0x0042dde0, 0, 9, 0);
        if (9 < *pBehaviorTable)
        {
            uint* pEntry = (uint*)pBehaviorTable[1];
            *(code**)((uint)pEntry + 0x1b4) = (code*)0x0042d990;
            *(uint*)((uint)pEntry + 0x1bc) = 0;
            if (9 < *pBehaviorTable)
            {
                pEntry = (uint*)pBehaviorTable[1];
                *(code**)((uint)pEntry + 0x1d0) = (code*)0x0042d9a0;
                *(uint*)((uint)pEntry + 0x1d8) = 0;
            }
        }

        // Mode 1 skips extra entries
        if (mode != 1)
        {
            addBehavior(pBehaviorTable, this, (code*)0x0042df40, 0, 0xb, 0);
            if (0xb < *pBehaviorTable)
            {
                uint* pEntry = (uint*)pBehaviorTable[1];
                *(code**)((uint)pEntry + 0x214) = (code*)0x0042d990;
                *(uint*)((uint)pEntry + 0x21c) = 0;
                if (0xb < *pBehaviorTable)
                {
                    pEntry = (uint*)pBehaviorTable[1];
                    *(code**)((uint)pEntry + 0x230) = (code*)0x0042d9a0;
                    *(uint*)((uint)pEntry + 0x238) = 0;
                }
            }
            addBehavior(pBehaviorTable, this, (code*)0x0042e0a0, 0, 0xc, 0);
            if (0xc < *pBehaviorTable)
            {
                uint* pEntry = (uint*)pBehaviorTable[1];
                *(code**)((uint)pEntry + 0x244) = (code*)0x0042d990;
                *(uint*)((uint)pEntry + 0x24c) = 0;
                if (0xc < *pBehaviorTable)
                {
                    pEntry = (uint*)pBehaviorTable[1];
                    *(code**)((uint)pEntry + 0x260) = (code*)0x0042d9a0;
                    *(uint*)((uint)pEntry + 0x268) = 0;
                }
            }
        }
    }

    // Additional entry for mode==0 after random call
    if (mode == 0 && FUN_0041df10() != 0)
    {
        if (0x17 < *pBehaviorTable)
        {
            uint* pEntry = (uint*)pBehaviorTable[1];
            *(code**)((uint)pEntry + 0x454) = (code*)0x0042da60;
            *(uint*)((uint)pEntry + 0x45c) = 0;
        }
    }

    // Entry 15 always added
    addBehavior(pBehaviorTable, this, (code*)0x0042e5c0, 0, 0xf, 0);

    // Mode 0 also triggers vertex processing and spatial partition update
    if (mode == 0)
    {
        // If engine has a flag at +0xe0 (non-zero)
        if (*(char*)(pEngine + 0xe0) != 0)
        {
            // Get and set some value (maybe screen matrix?)
            uint someVal = FUN_0042e5e0();
            FUN_0042a3f0(someVal);

            // Process vertices stored at offset +0x2614
            int vertexCount = *(unsigned short*)(this + 0x262a);
            unsigned short* vertexIndices = *(unsigned short**)(this + 0x262c);
            float* vertexArray = *(float**)(this + 0x2614);
            for (int i = 0; i < vertexCount; i++)
            {
                int idx = vertexIndices[i];
                int* pVertex = (int*)(this + 0x2620) + idx * 8; // +0x20 per vertex (32 bytes)
                // Compute distance using engine matrix and global constants
                float dist = (((*(float*)(pEngine + 0x84) * vertexArray[idx * 4 + 1] +
                               *(float*)(pEngine + 0x88) * vertexArray[idx * 4 + 2] +
                               *(float*)(pEngine + 0x80) * vertexArray[idx * 4 + 0] +
                               *(float*)(pEngine + 0x8c)) - vertexArray[idx * 4 + 3]) -
                              *(float*)(0x00e44564) + *(float*)(0x00e44628)) * *(float*)(0x00e445d0);
                if (dist < 0.0f) dist = 0.0f;
                if (dist > *(float*)(0x00e44624)) dist = *(float*)(0x00e44624);
                int adjustedDist = (int)(dist + 0.5f); // ROUND
                addBehavior(pBehaviorTable, this, (code*)0x0042e270, 0, 0x11, adjustedDist << 8);
            }
        }

        // Update spatial partition (linked-list reinsertion)
        int* listStart = (int*)(this + 0x3a74);
        int listCount = *(int*)(this + 0x3af4);
        int globalPtr = (*(int*)(*pProcess + 0x34) == 0) ? *(int*)(0x00f15a4c) : (*(int*)(0x00f15a4c + 4));
        if (globalPtr != g_prevGlobal) // g_prevGlobal at 0x01128648
        {
            g_prevGlobal = globalPtr;
            for (int* pList = listStart; pList != listStart + listCount; ++pList)
            {
                int* pNode = (int*)*pList;
                // Each node has three linked lists at +0x10, +0x14, +0x18
                for (int j = 0; j < 3; ++j)
                {
                    int* pCurrent = (int*)(pNode + 4 * (0x10/4 + j)); // offset 0x10 + j*4?? Actually the code increments piVar8 directly
                    // Walk the linked list
                    while (pCurrent)
                    {
                        int* pNext = (int*)*pCurrent; // same as pCurrent[0x10/4]? Hard to parse
                        // In multiplayer mode, unlink and reinsert
                        if (g_isSinglePlayer != 0)
                        {
                            // Remove node from current list
                            if (*(int*)((int)pCurrent + 0xc))
                                *(int*)(*(int*)((int)pCurrent + 0xc) + 0x10) = *(int*)((int)pCurrent + 0x10);
                            if (*(int*)((int)pCurrent + 0x10))
                                *(int*)(*(int*)((int)pCurrent + 0x10) + 0xc) = *(int*)((int)pCurrent + 0xc);
                            *(int*)((int)pCurrent + 0x10) = 0;
                            *(int*)((int)pCurrent + 0xc) = 0;
                            // Check mask and reinsert into appropriate bin
                            int category = *(int*)(*(int*)(*pProcess + 8) + 0x7c + *(int*)((int)pCurrent + 0x18));
                            if ((category & 0x4000) != 0 && FUN_00432cd0(this, pCurrent))
                            {
                                uint subMask = category & 0xc;
                                int bin;
                                if (subMask == 0) bin = 1;
                                else if (subMask == 4) bin = 3;
                                else bin = (subMask != 8) + 2 + ???; // original: (uVar11 != 8) + 2 gives 2 or 3
                                int* pBin = (int*)(FUN_00432cd0(this, pCurrent) + 0xc + bin * 4);
                                *(int*)((int)pCurrent + 0x10) = *pBin;
                                *(int*)((int)pCurrent + 0xc) = (int)pBin;
                                if (*pBin) *(int*)(*pBin + 0xc) = (int)&pCurrent[0x10/4]; // address of next field
                                *pBin = (int)pCurrent;
                            }
                        }
                        pCurrent = pNext;
                    }
                }
            }
        }

        // Final initialization if mode is 0
        if (*(int*)(this + 0x39f8) == 0)
        {
            FUN_00428350();
        }
    }

    return pBehaviorTable;
}