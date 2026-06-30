// FUNC_NAME: DataTreeParser::parseTreeData
int* __thiscall DataTreeParser::parseTreeData(int count, DataTreeAllocator* pAllocator, char* pData) {
    int *pNode; // pointer to first-level node
    int local_28; // offset within pData
    int local_4; // remaining top-level items
    int local_20; // offset within a top-level item for second-level items
    uint local_c; // second-level item counter
    uint local_14; // third-level item counter

    // Mask the 'this' pointer low bits (probably a version/magic value)
    pNode = (int*)((uint)this & 0xffffff00);

    if (pData == nullptr || count == 0) {
        return pNode;
    }

    local_28 = 0; // start of current top-level item
    local_4 = count;

    do {
        // --- Allocate first-level node ---
        int* pFirstLevel = *(int**)(pAllocator + 0x34); // free list head for pool1
        if (pFirstLevel == nullptr) {
            if (*(int*)(pAllocator + 0x30) == 0 || ((*(byte*)(pAllocator + 0x24) & 1) == 0)) {
                FUN_004de190(); // pool expansion?
            }
            pFirstLevel = *(int**)(pAllocator + 0x34);
            if (pFirstLevel == nullptr) {
                goto SKIP_FIRST_LEVEL;
            }
        }
        // Remove from free list
        int nextFree = *pFirstLevel;
        pAllocator->usedCount1++; // offset 0x10
        pAllocator->freeCount1--; // offset 0x0c
        pAllocator->freeList1 = nextFree; // offset 0x34

        pNode = pFirstLevel;
        if (pFirstLevel != nullptr) {
            // Initialize first-level node
            char* pNameDest = (char*)(pFirstLevel + 1); // offset 0x04
            *pNameDest = '\0';
            *pFirstLevel = 0; // clear next pointer
            pFirstLevel[9] = 0; // hash
            pFirstLevel[10] = 0; // second-level count

            // Copy name from source: first 0x20 bytes of top-level item
            _strncpy(pNameDest, pData + local_28, 0x20);
            int hash = FUN_004dafd0(pNameDest);
            pFirstLevel[9] = hash;
            pFirstLevel[10] = *(int*)(pData + local_28 + 0x20); // number of second-level items

            FUN_005dbc10(pNameDest, hash); // register name in hash table

            // --- Process second-level items ---
            local_20 = 0; // offset within top-level item for second-level data
            local_c = 0;
            int secondLevelCount = *(int*)(pData + local_28 + 0x20);

            if (secondLevelCount != 0) {
                do {
                    char* pSecondSrc = pData + local_28 + local_20 + 0x24; // second-level item starts at offset 0x24 from top-level base

                    // Allocate second-level node
                    int* pSecondLevel = *(int**)(pAllocator + 0x6c); // free list for pool2
                    if (pSecondLevel == nullptr) {
                        if (*(int*)(pAllocator + 0x68) == 0 || ((*(byte*)(pAllocator + 0x5c) & 1) == 0)) {
                            FUN_004de190();
                        }
                        pSecondLevel = *(int**)(pAllocator + 0x6c);
                        if (pSecondLevel == nullptr) {
                            goto SKIP_SECOND_LEVEL;
                        }
                    }
                    // Remove from free list
                    int nextSecondFree = *pSecondLevel;
                    pAllocator->usedCount2++; // offset 0x48
                    pAllocator->freeCount2--; // offset 0x44
                    pAllocator->freeList2 = nextSecondFree; // offset 0x6c

                    if (pSecondLevel != nullptr) {
                        // Initialize second-level node
                        char* pName2 = (char*)(pSecondLevel + 1); // offset 0x04
                        char* pValue2 = (char*)(pSecondLevel + 9); // offset 0x24?
                        *pSecondLevel = 0; // clear children pointer
                        pSecondLevel[0x11] = 0; // hash of name2?
                        pSecondLevel[0x12] = 0; // third-level count
                        pSecondLevel[0x13] = 0; // link to children?
                        *pName2 = '\0';
                        *pValue2 = '\0';

                        // Copy name (from second-level item at offset 0x20)
                        _strncpy(pName2, pSecondSrc + 0x20, 0x20);
                        int hash2 = FUN_004dafd0(pName2);
                        pSecondLevel[0x11] = hash2;

                        // Copy value string (from second-level item at offset 0x00)
                        _strncpy(pValue2, pSecondSrc, 0x20);
                        pSecondLevel[0x12] = *(int*)(pSecondSrc + 0x40); // third-level count

                        // Link second-level node to first-level node's child list
                        if (*pFirstLevel != 0) {
                            pSecondLevel[0x13] = *pFirstLevel; // save old child pointer
                        }
                        *pFirstLevel = (int)pSecondLevel; // first-level node's next becomes this second-level node

                        // Register second-level name in hash table
                        FUN_005dbc10(pValue2, hash2, pName2, FUN_004dafd0(pValue2));

                        // --- Process third-level items ---
                        local_14 = 0;
                        int thirdLevelCount = *(int*)(pSecondSrc + 0x40);
                        if (thirdLevelCount != 0) {
                            char* pThirdSrc = pSecondSrc + 0x44; // third-level items start at offset 0x44 from second-level base
                            do {
                                // Allocate third-level node
                                byte* pThirdLevel = *(byte**)(pAllocator + 0xa4); // free list for pool3
                                if (pThirdLevel == nullptr) {
                                    if (*(int*)(pAllocator + 0xa0) == 0 || ((*(byte*)(pAllocator + 0x94) & 1) == 0)) {
                                        FUN_004de190();
                                    }
                                    pThirdLevel = *(byte**)(pAllocator + 0xa4);
                                    if (pThirdLevel == nullptr) {
                                        goto SKIP_THIRD_LEVEL;
                                    }
                                }
                                // Remove from free list
                                int nextThirdFree = *(int*)pThirdLevel;
                                pAllocator->usedCount3++; // offset 0x80
                                pAllocator->freeCount3--; // offset 0x7c
                                pAllocator->freeList3 = nextThirdFree; // offset 0xa4

                                if (pThirdLevel != nullptr) {
                                    // Initialize third-level node (16 bytes for field data? Actually we see 0x30 bytes)
                                    // Clear the first 16 bytes?? Actually they clear 16 bytes from offset 0x20 to 0x30
                                    for (int i = 0; i < 16; i++) {
                                        pThirdLevel[0x20 + i] = 0;
                                    }
                                    *pThirdLevel = 0; // clear first byte? Actually they set to 0

                                    // Copy name from source
                                    _strncpy((char*)pThirdLevel, pThirdSrc, 0x20); // name
                                    // Compute hash (case-insensitive)
                                    int hash3 = 0;
                                    byte* p = pThirdLevel;
                                    while (*p != 0) {
                                        uint c = *p;
                                        if (c - 'A' < 26) {
                                            c += 0x20; // tolower
                                        }
                                        hash3 = hash3 * 0x1003f + c;
                                        p++;
                                    }
                                    *(int*)(pThirdLevel + 0x20) = hash3;
                                    *(int*)(pThirdLevel + 0x28) = *(int*)(pThirdSrc + 0x24); // value2
                                    *(int*)(pThirdLevel + 0x24) = *(int*)(pThirdSrc + 0x20); // value1

                                    // Link to second-level node's child list
                                    if (*pSecondLevel != 0) {
                                        *(int*)(pThirdLevel + 0x2c) = *pSecondLevel;
                                    }
                                    *pSecondLevel = (int)pThirdLevel;

                                    // Register third-level in mesh? With hash and float value
                                    int hash3again = 0;
                                    p = pThirdLevel;
                                    while (*p != 0) {
                                        uint c = *p;
                                        if (c - 'A' < 26) {
                                            c += 0x20;
                                        }
                                        hash3again = hash3again * 0x1003f + c;
                                        p++;
                                    }
                                    FUN_005dbc10((char*)pThirdLevel, hash3again, *(int*)(pThirdLevel + 0x24), (double)*(float*)(pThirdLevel + 0x28));
                                }

SKIP_THIRD_LEVEL:
                                local_14++;
                                pThirdSrc += 0x28; // each third-level item is 0x28 bytes
                            } while (local_14 < thirdLevelCount);
                        }
                    }

SKIP_SECOND_LEVEL:
                    local_20 += 0x44; // each second-level item is 0x44 bytes
                    local_28 += 0x44; // also advance global offset for next item (within same top-level)
                    local_c++;
                } while (local_c < secondLevelCount);
            }
        }

SKIP_FIRST_LEVEL:
        // Check if the collector array is full; if so, call grow function
        if (*(int*)(pAllocator + 0xac) == *(int*)(pAllocator + 0xb0)) {
            FUN_005e1ba0(); // array expansion?
        }
        // Store allocated first-level node into collector array
        int* pArray = *(int**)(pAllocator + 0xa8);
        int idx = *(int*)(pAllocator + 0xac);
        *(int*)(pAllocator + 0xac) = idx + 1;
        if (pArray != nullptr) {
            pArray[idx] = pNode;
            pNode = pNode; // alias
        }

        local_28 += 0x24; // top-level item header size (0x24)
        local_4--;
    } while (local_4 != 0);

    // Return value: pointer with low byte set to 1? (success indicator)
    return (int*)((uint)pNode | 1);
}