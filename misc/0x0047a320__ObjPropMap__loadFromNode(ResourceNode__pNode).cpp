// FUNC_NAME: ObjPropMap::loadFromNode(ResourceNode* pNode)

void __thiscall ObjPropMap::loadFromNode(ResourceNode* pNode)
{
    int* piVar15;
    char* pcVar2;
    char cVar3;
    ushort uVar4;
    int* pKeyValue;
    int* pKeyValue2;
    int iVar7;
    uint uVar8;
    uint* puVar9;
    uint* puVar10;
    uint uVar11;
    int iVar12;
    uint** ppuVar13;
    bool bVar14;
    int local_ac;          // array base offset
    uint* local_a8;        // array pointer
    uint local_a4;         // current index
    uint local_a0;         // total count
    uint* local_9c;        // current node
    short local_98;        // node index
    uint local_94;         // node data
    uint** local_54;       // linked list walker
    int m_keyValueBuffer[16]; // 8 pairs of (key,value)

    // Clear previously allocated node list
    if (*(int*)((int)this + 0x58) != 0) {
        freeNodeList();   // FUN_0047a040
    }

    // Initialize key-value buffer to zero
    for (int i = 0; i < 16; i++) {
        m_keyValueBuffer[i] = 0;
    }

    // Begin reading child nodes with magic signature 0x6df50074
    beginReadChildNodes(pNode, 0x6df50074);   // FUN_0043aff0

    ppuVar13 = local_54;   // linked list pointer

    do {
        // Determine iteration mode: 0 -> linked list, else array
        if (local_b0 == '\0') {
            bVar14 = (*ppuVar13 == (int*)0x0);
        } else {
            bVar14 = (local_a4 == local_a0);
        }

        if (bVar14) {
            // After all children processed, handle special nodes
            if ((*(byte*)((int)this + 0x5e) & 2) != 0) {
                // Look for "someSetting" node by hash
                iVar7 = getChildNodeByHash((int)this + 0x20, 0x5e1f74a6, 0xffffffff);
                if ((iVar7 != 0) && (*(int*)(iVar7 + 0xc) != 0)) {
                    *(int*)((int)this + 0x60) = *(int*)(iVar7 + 0xc);
                }

                // Look for "anotherSetting" node by hash
                iVar7 = getChildNodeByHash((int)this + 0x20, 0x137726b7, 0xffffffff);
                if ((iVar7 != 0) && (*(code**)(*(int*)((int)this + 0x3c) + 8))()->isActive() && 
                    (cVar3 = compareString(&g_stringBuffer[0x4], ""), cVar3 == '\0')) {
                    g_stringCounter = g_stringCounter + 1;   // _DAT_012067c8
                    addStringToGlobalList(&g_stringBuffer[0x4], 0x8000); // FUN_004084d0
                }
            }

            // If we have collected any key-value pairs, allocate and store them
            if (*(byte*)((int)this + 0x5c) != 0) {
                uint count = (uint)*(byte*)((int)this + 0x5c);
                uint* pAlloc = (uint*)allocateMemory(-(uint)(0xfffffffb < count * 0xc) | count * 0xc + 4);
                if (pAlloc == (uint*)0x0) {
                    puVar10 = (uint*)0x0;
                } else {
                    puVar10 = pAlloc + 1; // skip header count
                    *pAlloc = count;
                    pAlloc = puVar10;
                    while (count != 0) {
                        count--;
                        *pAlloc = 0;
                        *(ushort*)(pAlloc + 1) = 0;
                        *(ushort*)((int)pAlloc + 6) = 0;
                        pAlloc = pAlloc + 3;
                    }
                }
                *(uint**)((int)this + 0x58) = puVar10; // store allocated list

                // Copy key-value pairs from buffer to allocated list
                piVar15 = m_keyValueBuffer;
                int offset = 0;
                do {
                    pcVar2 = (char*)*piVar15;
                    if ((pcVar2 != (char*)0x0) && (*pcVar2 != '\0')) {
                        int destIndex = *(int*)((int)this + 0x58) + offset;
                        if (*pcVar2 != '\0') {
                            uVar8 = hashString(pcVar2); // FUN_004dafd0
                            setKeyInList(destIndex, uVar8); // FUN_00408260
                        }
                        offset += 0xc;
                        *(int*)(destIndex + 8) = piVar15[1]; // value
                    }
                    piVar15 = piVar15 + 2;
                } while (piVar15 != m_keyValueBuffer + 16);
            }
            return;
        }

        // Determine current node structure
        uint** ppuVar6 = &local_9c;
        if (local_b0 == '\0') {
            ppuVar6 = ppuVar13;
        }

        // Check node type tag at offset 6
        if (*(short*)((int)ppuVar6 + 6) == 0x25e3) {
            // Node stores ID as ushort in its second field
            uint nodeId = (uint)*(ushort*)((int)ppuVar6 + 2);
        } else {
            uint nodeId = (uint)(ppuVar6[1]);
        }

        // nodeId is overloaded: we use puVar5 = nodeId - 3
        uVar11 = nodeId - 3;
        if (uVar11 < 0x10) {
            // Key-value pair retrieval
            if ((uVar11 & 1) == 0) {
                // Even: store key string
                ppuVar6 = &local_9c;
                if (local_b0 == '\0') {
                    ppuVar6 = ppuVar13;
                }
                if (*(short*)((int)ppuVar6 + 6) == 0x25e3) {
                    if (*ppuVar6 == (int*)0x0) goto LAB_0047a673;
                    ppuVar6 = (uint**)((int)ppuVar6[2] + (int)*ppuVar6);
                } else {
                    ppuVar6 = ppuVar6 + 2;
                }
                if ((ppuVar6 != (uint**)0x0) && (*(char*)ppuVar6 != '\0')) {
                    m_keyValueBuffer[(uVar11 >> 1) * 2] = (int)ppuVar6;
                    *(byte*)((int)this + 0x5c) = *(byte*)((int)this + 0x5c) + 1;
                }
            } else {
                // Odd: store value integer
                ppuVar6 = &local_9c;
                if (local_b0 == '\0') {
                    ppuVar6 = ppuVar13;
                }
                m_keyValueBuffer[(uVar11 >> 1) * 2 + 1] = (int)ppuVar6[2];
            }
        } else {
            // Special node IDs: 3,4,5 (after subtracting 3)
            if (nodeId == 3) { // "Collection" node
                ppuVar6 = &local_9c;
                if (local_b0 == '\0') {
                    ppuVar6 = ppuVar13;
                }
                // Get the string from the node
                if (*(short*)((int)ppuVar6 + 6) == 0x25e3) {
                    if (*ppuVar6 == (int*)0x0) {
                        ppuVar6 = (uint**)(int)&g_nullString; // DAT_00e2a89b
                    } else {
                        ppuVar6 = (uint**)((int)ppuVar6[2] + (int)*ppuVar6);
                    }
                } else {
                    ppuVar6 = ppuVar6 + 2;
                }
                int* listPtr = (int*)((int)this + 0x50);
                clearStringList(listPtr);        // FUN_004086d0
                initStringList(listPtr);         // FUN_00408310
                ppuVar13 = local_54;
                if ((ppuVar6 != (uint**)0x0) && (*(char*)ppuVar6 != '\0')) {
                    uVar8 = hashString(ppuVar6); // FUN_004dafd0
                    addStringToList(listPtr, uVar8); // FUN_00408260
                    ppuVar13 = local_54;
                    if (*listPtr != 0) {
                        *(short*)((int)this + 0x54) = *(short*)((int)this + 0x54) + 1;
                        iVar7 = getGlobalSlot(); // FUN_00407da0
                        if (iVar7 == 0) {
                            goto LAB_0047a66a;
                        } else {
                            uVar4 = *(ushort*)(iVar7 + 0x14);
                            *(ushort*)(iVar7 + 0x14) = ((uVar4 ^ (uVar4 * 2 >> 1) + 1) & 0x7fff) ^ uVar4;
                            ppuVar13 = local_54;
                        }
                    }
                }
            } else if (nodeId == 4) { // "Pointer" node
                ppuVar6 = &local_9c;
                if (local_b0 == '\0') {
                    ppuVar6 = ppuVar13;
                }
                *(uint**)((int)this + 0x60) = ppuVar6[2];
            } else if (nodeId == 5) { // "Flags" node
                ushort oldFlags = *(ushort*)((int)this + 0x5e);
                ppuVar6 = &local_9c;
                if (local_b0 == '\0') {
                    ppuVar6 = ppuVar13;
                }
                uint newFlags = (uint)ppuVar6[2];
                *(ushort*)((int)this + 0x5e) = (ushort)newFlags;
                // Bit 1 toggled
                if ((((byte)newFlags ^ (byte)oldFlags) & 2) != 0) {
                    if ((newFlags & 2) == 0) {
                        // Clearing flag: if bit 14 was set, clear it and clear global strings
                        if ((newFlags & 0x4000) != 0) {
                            *(ushort*)((int)this + 0x5e) = (ushort)newFlags & 0xbfff;
                            clearStringList((int*)&g_stringList1);   // FUN_004086d0
                            clearStringList((int*)&g_stringList2);   // FUN_004086d0
                            ppuVar13 = local_54;
                        }
                    } else {
                        // Setting flag: also set bit 14
                        *(ushort*)((int)this + 0x5e) = (ushort)newFlags | 0x4000;
                        if (g_stringList1.head != 0) {
                            g_stringList1.referenceCount++;   // _DAT_0120e928
                            iVar7 = getGlobalSlot(); // FUN_00407da0
                            if (iVar7 == 0) {
                                addEntryToStringList(&g_stringList1, 0x8000); // FUN_004084d0
                                ppuVar13 = local_54;
                            } else {
                                uVar4 = *(ushort*)(iVar7 + 0x14);
                                *(ushort*)(iVar7 + 0x14) = ((uVar4 ^ (uVar4 * 2 >> 1) + 1) & 0x7fff) ^ uVar4;
                                ppuVar13 = local_54;
                            }
                        }
                        if (g_stringList2.head != 0) {
                            g_stringList2.referenceCount++;   // _DAT_0120e920
                            iVar7 = getGlobalSlot(); // FUN_00407da0
                            if (iVar7 == 0) {
                                int* listPtr2 = (int*)&g_stringList2;
                                goto LAB_0047a66a;
                            }
                            uVar4 = *(ushort*)(iVar7 + 0x14);
                            *(ushort*)(iVar7 + 0x14) = ((uVar4 ^ (uVar4 * 2 >> 1) + 1) & 0x7fff) ^ uVar4;
                            ppuVar13 = local_54;
                        }
                    }
                }
            }
        }

LAB_0047a673:
        // Advance to next node
        if (local_b0 == '\0') {
            // Linked list mode: move to next sibling or end
            if ((int)local_a4 < 0) {
                local_54 = (uint**)((int)ppuVar13 + (int)*ppuVar13);
                advanceNodeReader();   // FUN_0043b140
                ppuVar13 = local_54;
            } else if ((int)local_a4 < (int)(local_a0 - 1)) {
                local_a4 = local_a4 + 1;
                local_54 = (uint**)((int)ppuVar13 + (int)*ppuVar13);
                ppuVar13 = (uint**)((int)ppuVar13 + (int)*ppuVar13);
            } else {
                local_54 = (uint**)(int)&g_endNodeMarker;   // DAT_01163cf8
                ppuVar13 = (uint**)(int)&g_endNodeMarker;
            }
        } else {
            // Array mode: move to next index, check bitmask
            local_a4 = local_a4 + 1;
            if (local_a4 != local_a0) {
                local_98 = (short)local_a4;
                if ((*(byte*)((local_a4 >> 3) + local_ac) & (byte)(1 << ((byte)local_a4 & 7))) == 0) {
                    local_94 = *local_a8;
                    local_9c = local_a8;
                    local_a8 = local_a8 + 1;
                } else {
                    local_9c = (int*)0x0;
                    local_94 = 0;
                }
            }
        }
    } while (true);
}