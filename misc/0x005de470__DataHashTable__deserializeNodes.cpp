// FUNC_NAME: DataHashTable::deserializeNodes
int *__thiscall DataHashTable::deserializeNodes(int count, void *thisManager, char *sourceBuffer)
{
    int *nodePtr;
    int *freeNode;
    char *srcStr;
    char *srcMid;
    int *allocNode;
    byte bLoop;
    int hashResult;
    uint uHashAccum;
    int *childNode;
    byte *innerByte;
    char *srcInner;
    int *destMid;
    int *destMid2;
    int *destMidStr2;
    int local20; // offset within source for middle records
    int local28; // offset within source for top records
    uint innerCount;
    uint midCount;
    int *currTopNode;
    int remaining;

    // Initialization: clear high bits of EAX (not used here)
    nodePtr = (int *)(in_EAX & 0xffffff00);

    if (sourceBuffer != NULL && count != 0) {
        local28 = 0;
        remaining = count;
        if (count != 0) {
            do {
                // Allocate or retrieve a top-level node from the free pool (offset +0x34)
                freeNode = *(int **)((char *)thisManager + 0x34);
                srcStr = sourceBuffer + local28;
                currTopNode = NULL;
                if (freeNode == NULL) {
                    if (*(int *)((char *)thisManager + 0x30) == 0 || (*(byte *)((char *)thisManager + 0x24) & 1) == 0) {
                        poolAllocate(thisManager);  // FUN_004de190
                    }
                    freeNode = *(int **)((char *)thisManager + 0x34);
                    if (freeNode != NULL) goto allocTop;
                } else {
allocTop:
                    // Take node from free list
                    hashResult = *freeNode;
                    *(int *)((char *)thisManager + 0x10) += 1;   // used count
                    *(int *)((char *)thisManager + 0x0c) -= 1;   // free count
                    *(int *)((char *)thisManager + 0x34) = hashResult;
                    currTopNode = freeNode;
                    if (freeNode != NULL) {
                        // Initialize the node
                        childNode = freeNode + 1;
                        *(char *)childNode = '\0';
                        *freeNode = 0;
                        freeNode[10] = 0;  // offset 0x28
                        freeNode[9] = 0;   // offset 0x24
                        *(char *)childNode = '\0';
                        _strncpy((char *)childNode, srcStr, 0x20); // copy name (32 chars)

                        // Compute hash of the name
                        hashResult = computeHash((char *)childNode); // FUN_004dafd0
                        freeNode[9] = hashResult;   // store hash at +0x24
                        freeNode[10] = *(int *)(srcStr + 0x20); // count of middle children from source at +0x20

                        // Perform hash-based insertion (FUN_005dbc10)
                        hashResult = computeHash((char *)childNode);
                        insertIntoHashTable(thisManager, (char *)childNode, hashResult);

                        // Now process middle-level records within this top-level block
                        local20 = 0;
                        midCount = 0;
                        if (*(int *)(srcStr + 0x20) != 0) {
                            do {
                                // Allocate middle node from pool at +0x6c
                                freeNode = *(int **)((char *)thisManager + 0x6c);
                                srcMid = srcStr + local20 + 0x24; // start of middle record in source
                                if (freeNode == NULL) {
                                    if (*(int *)((char *)thisManager + 0x68) == 0 || (*(byte *)((char *)thisManager + 0x5c) & 1) == 0) {
                                        poolAllocate(thisManager);
                                    }
                                    freeNode = *(int **)((char *)thisManager + 0x6c);
                                    if (freeNode != NULL) goto allocMid;
                                } else {
allocMid:
                                    // Take from free list
                                    hashResult = *freeNode;
                                    *(int *)((char *)thisManager + 0x48) += 1;
                                    *(int *)((char *)thisManager + 0x44) -= 1;
                                    *(int *)((char *)thisManager + 0x6c) = hashResult;
                                    if (freeNode != NULL) {
                                        destMid = freeNode + 1;   // string1 at +4
                                        destMid2 = freeNode + 9;  // string2 at +0x24
                                        *freeNode = 0;
                                        freeNode[0x11] = 0; // offset 0x44, hash1?
                                        freeNode[0x12] = 0; // offset 0x48, something
                                        freeNode[0x13] = 0; // offset 0x4c, child chain
                                        *(char *)destMid = '\0';
                                        *(char *)destMid2 = '\0';
                                        // Copy first string (32 chars) from source at srcMid+0x20
                                        _strncpy((char *)destMid, srcMid + 0x20, 0x20);
                                        hashResult = computeHash((char *)destMid);
                                        freeNode[0x11] = hashResult;
                                        // Copy second string (32 chars) from source at srcMid
                                        _strncpy((char *)destMid2, srcMid, 0x20);
                                        freeNode[0x12] = *(int *)(srcMid + 0x40); // count of inner children
                                        // Link this middle node into the top node's child chain
                                        if (*currTopNode != 0) {
                                            freeNode[0x13] = *currTopNode; // next sibling
                                        }
                                        *currTopNode = (int)freeNode; // top node's first child points to this
                                        // Compute hash of second string and insert into hash table
                                        hashResult = computeHash((char *)destMid2);
                                        hashResult = computeHash((char *)destMid, (char *)destMid2, hashResult);
                                        insertIntoHashTable(thisManager, (char *)destMid, hashResult);

                                        // Process inner-level records within this middle block
                                        innerCount = 0;
                                        if (*(int *)(srcMid + 0x40) != 0) {
                                            srcInner = srcMid + 0x44;
                                            do {
                                                // Allocate inner node from pool at +0xa4
                                                innerByte = *(byte **)((char *)thisManager + 0xa4);
                                                if (innerByte == NULL) {
                                                    if (*(int *)((char *)thisManager + 0xa0) == 0 || (*(byte *)((char *)thisManager + 0x94) & 1) == 0) {
                                                        poolAllocate(thisManager);
                                                    }
                                                    innerByte = *(byte **)((char *)thisManager + 0xa4);
                                                    if (innerByte != NULL) goto allocInner;
                                                } else {
allocInner:
                                                    // Take from free list
                                                    uHashAccum = *(uint *)innerByte;
                                                    *(int *)((char *)thisManager + 0x80) += 1;
                                                    *(int *)((char *)thisManager + 0x7c) -= 1;
                                                    *(uint *)((char *)thisManager + 0xa4) = uHashAccum;
                                                    if (innerByte != NULL) {
                                                        // Zero out the node (size maybe 0x30)
                                                        innerByte[0x20] = 0;
                                                        innerByte[0x21] = 0;
                                                        innerByte[0x22] = 0;
                                                        innerByte[0x23] = 0;
                                                        innerByte[0x24] = 0;
                                                        innerByte[0x25] = 0;
                                                        innerByte[0x26] = 0;
                                                        innerByte[0x27] = 0;
                                                        innerByte[0x28] = 0;
                                                        innerByte[0x29] = 0;
                                                        innerByte[0x2a] = 0;
                                                        innerByte[0x2b] = 0;
                                                        innerByte[0x2c] = 0;
                                                        innerByte[0x2d] = 0;
                                                        innerByte[0x2e] = 0;
                                                        innerByte[0x2f] = 0;
                                                        *innerByte = 0;
                                                        // Copy name string (32 chars) from source
                                                        _strncpy((char *)innerByte, srcInner, 0x20);
                                                        // Compute case-insensitive hash (similar to djb2 but with multiplier 0x1003f)
                                                        hashResult = 0;
                                                        bLoop = *innerByte;
                                                        innerByte = innerByte; // keep pointer for loop
                                                        while (bLoop != 0) {
                                                            uHashAccum = (uint)bLoop;
                                                            if (uHashAccum - 0x41 < 0x1a) {
                                                                uHashAccum += 0x20; // convert uppercase to lowercase
                                                            }
                                                            hashResult = hashResult * 0x1003f + uHashAccum;
                                                            bLoop = *innerByte;
                                                        }
                                                        *(int *)(innerByte + 0x20) = hashResult; // store hash at +0x20
                                                        *(float *)(innerByte + 0x28) = *(float *)(srcInner + 0x24); // value2 (float)
                                                        local20 += 0x28; // update offset for next inner record
                                                        local28 += 0x28;
                                                        *(float *)(innerByte + 0x24) = *(float *)(srcInner + 0x20); // value1 (float)
                                                        // Link inner node into middle node's child chain
                                                        if (*(int *)(freeNode + 0x13) != 0) {
                                                            *(int *)(innerByte + 0x2c) = *(int *)(freeNode + 0x13);
                                                        }
                                                        *(int *)(freeNode + 0x13) = (int)innerByte; // update child chain pointer
                                                        // Insert inner node into hash table
                                                        // Recompute hash (using same loop, but note that innerByte was advanced in loop; we need original pointer)
                                                        // The decompiled code uses the same _Dest_01 pointer after the loop; we'll use original
                                                        hashResult = 0;
                                                        // We'll use the pointer that was stored (but it's been advanced? Actually the loop was on pbVar7 which was a copy; _Dest_01 unchanged).
                                                        // So we can recompute hash from the string at _Dest_01.
                                                        // Actually the decompiled code does a second loop after the copy and then calls FUN_005dbc10 with three args.
                                                        // We'll mimic that:
                                                        hashResult = 0;
                                                        bLoop = *innerByte;
                                                        innerByte = innerByte; // pointer to start
                                                        while (bLoop != 0) {
                                                            uHashAccum = (uint)bLoop;
                                                            if (uHashAccum - 0x41 < 0x1a) {
                                                                uHashAccum += 0x20;
                                                            }
                                                            hashResult = hashResult * 0x1003f + uHashAccum;
                                                            bLoop = *innerByte;
                                                        }
                                                        insertIntoHashTable(thisManager, (char *)innerByte, hashResult,
                                                                            *(float *)(innerByte + 0x24), *(float *)(innerByte + 0x28));
                                                    }
                                                }
                                                innerCount += 1;
                                                srcInner += 0x28;
                                            } while (innerCount < *(uint *)(srcMid + 0x40));
                                        }
                                    }
                                }
                                local20 += 0x44;
                                local28 += 0x44;
                                midCount += 1;
                            } while (midCount < *(uint *)(srcStr + 0x20));
                        }
                    }
                }
                // Check if hash table needs resizing
                if (*(int *)((char *)thisManager + 0xac) == *(int *)((char *)thisManager + 0xb0)) {
                    rehashTable(thisManager); // FUN_005e1ba0
                }
                // Add current top node to the hash table's array
                undefined4 *tableSlot = (undefined4 *)(*(int *)((char *)thisManager + 0xa8) + *(int *)((char *)thisManager + 0xac) * 4);
                *(int *)((char *)thisManager + 0xac) += 1;
                if (tableSlot != NULL) {
                    *tableSlot = (undefined4)currTopNode;
                    nodePtr = currTopNode;
                }
                local28 += 0x24;
                remaining -= 1;
            } while (remaining != 0);
        }
        // Return success indicator (the last node pointer combined with 1 in high byte)
        nodePtr = (int *)CONCAT31((int3)((uint)nodePtr >> 8), 1);
    }
    return nodePtr;
}