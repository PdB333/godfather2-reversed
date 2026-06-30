// FUNC_NAME: MemoryHeap::allocateBlock
// Function address: 0x006495b0
// This is the core memory allocation routine for the EARS engine heap.
// It implements a thread-safe general-purpose allocator with free lists,
// splitting, and coalescing. It manages a set of bins (size classes) and
// falls back to a system allocator if no free block fits.

int* __thiscall MemoryHeap::allocateBlock(uint requestedSize, uint alignment, int offset, uint flags)
{
    LPCRITICAL_SECTION pCriticalSection;
    uint uVar11;
    uint uVar7;
    int iVar8;
    int iVar9;
    BlockNode* piVar5;
    BlockNode* piVar10;
    uint uVar6;
    int iVar2;
    uint uVar12;
    uint local_14;
    float fVar3;
    char cVar4;

    uVar12 = flags;
    iVar2 = this; // +0x00: this pointer
    local_14 = 0;

    // Align requested size to 16 bytes (minimum 16)
    if (requestedSize < 0x10) {
        requestedSize = 0x10;
    } else {
        requestedSize = (requestedSize + 0xf) & 0xfffffff0;
    }

    // Align alignment to 16 bytes (minimum 16)
    if (alignment < 0x10) {
        alignment = 0x10;
    }

    do {
        // Check flag bit0: if set, attempt to allocate from the free list of already aligned blocks?
        for (; (uVar12 & 1) != 0; uVar12 = (uVar12 & 0xfffffffe) | 4) {
            uVar11 = (requestedSize + alignment + 0xf + offset) & 0xfffffff0;

            // Traverse the list of bins starting at +0x18
            piVar5 = *(BlockNode**)(iVar2 + 0x18);
            while (piVar5 != (BlockNode*)(iVar2 + 4)) {
                // Traverse blocks within the bin (doubly linked via offset 3 and 5)
                for (piVar10 = (BlockNode*)piVar5[3]; piVar10 != piVar5; piVar10 = (BlockNode*)piVar10[3]) {
                    // Check if block is free (bit0 == 0) and its size (masked) is at least uVar11
                    if (((piVar10[1] & 1U) == 0) && (uVar7 = piVar10[1] & 0xfffffffe, uVar11 <= uVar7)) {
                        // Remove the block from the free list (unlink)
                        *(int*)(piVar10[5] + 0x18) = piVar10[6];
                        *(int*)(piVar10[6] + 0x14) = piVar10[5];

                        // Mark block as used
                        piVar10[1] = piVar10[1] | 1;

                        // Compute offset to satisfy alignment and offset
                        iVar8 = *piVar10; // block start
                        iVar9 = ((iVar8 - requestedSize) + uVar7 + alignment - 1 + offset & -alignment) - offset;
                        piVar10[2] = iVar9; // user data offset from block start?

                        // If the block would end up overlapping with its own start, adjust
                        if (iVar8 + uVar7 < iVar9 + requestedSize) {
                            piVar10[2] = ((iVar8 - uVar11) + uVar7 + alignment - 1 + offset & -alignment) - offset;
                        }
                        iVar8 = (iVar8 - requestedSize) - piVar10[2];
                        goto LAB_00649905;
                    }
                }
                piVar5 = (BlockNode*)piVar5[5]; // next bin
            }
        }

        uVar6 = uVar12 & 4;
        uVar11 = requestedSize;

        // If flag bit2 is set, or alignment requirement is already satisfied
        if ((uVar6 != 0) || (uVar11 = (requestedSize + alignment + 0xf + offset) & 0xfffffff0, requestedSize <= uVar11)) {
            // Determine bin index based on size
            fVar3 = (float)(int)uVar11;
            if ((int)uVar11 < 0) {
                fVar3 = fVar3 + DAT_00e44578; // float constant for negative conversion
            }
            uVar7 = ((uint)fVar3 >> 0x17) - 0x7f;
            if (uVar7 < 6) {
                uVar7 = 6;
            }
            uVar7 = uVar7 - 6;
            if (7 < uVar7) {
                uVar7 = 7;
            }

            // Scan bins from computed index to max (8 bins)
            if (uVar7 < 8) {
                piVar5 = (BlockNode*)(uVar7 * 0x20 + 0x78 + iVar2);
                do {
                    // Scan blocks within the bin (offset 6 is next, offset 3 is prev? Actually offset 6 may be next free)
                    for (piVar10 = (BlockNode*)piVar5[6]; piVar10 != piVar5; piVar10 = (BlockNode*)piVar10[6]) {
                        uVar7 = piVar10[1] & 0xfffffffe; // block size
                        // Check size fits and alignment satisfied (bit2 flag ensures alignment)
                        if ((uVar11 <= uVar7) && ((uVar6 == 0) || ((alignment - 1 & *piVar10 + offset) == 0))) {
                            // Remove from free list
                            *(int*)(piVar10[5] + 0x18) = piVar10[6];
                            *(int*)(piVar10[6] + 0x14) = piVar10[5];

                            // Mark used
                            piVar10[1] = piVar10[1] | 1;

                            // Compute aligned user offset
                            offset = (*piVar10 + alignment - 1 + offset & -alignment) - offset;
                            iVar8 = (*piVar10 - offset) - requestedSize;
                            piVar10[2] = offset;
LAB_00649905:
                            // Attempt to split the block if remaining is large enough
                            if ((*(uint*)(iVar2 + 0x178) <= iVar8 + uVar7) &&
                                (piVar5 = (BlockNode*)(**(code**)(iVar2 + 0x18c))(iVar2, 0x20, *(undefined4*)(iVar2 + 0x194)),
                                 piVar5 != 0)) {
                                // Split: create a new block from the tail portion
                                piVar5[4] = piVar10[4];
                                *(BlockNode**)(piVar10[4] + 0xc) = piVar5;
                                piVar5[3] = (int)piVar10;
                                uVar7 = uVar7 - (iVar8 + uVar7);
                                piVar10[4] = (int)piVar5;
                                *piVar5 = *piVar10 + uVar7;
                                piVar5[1] = (-uVar7 ^ piVar5[1]) & 1 ^ (piVar10[1] & 0xfffffffeU) - uVar7;
                                piVar10[1] = (piVar10[1] ^ uVar7) & 1 ^ uVar7;
                                piVar5[1] = piVar5[1] & 0xfffffffe; // mark free
                                FUN_00649490(); // likely update free list pointers
                            }

                            // Attempt to coalesce with previous block?
                            uVar12 = piVar10[2] - *piVar10;
                            if ((*(uint*)(iVar2 + 0x178) <= uVar12) &&
                                (piVar5 = (BlockNode*)(**(code**)(iVar2 + 0x18c))(iVar2, 0x20, *(undefined4*)(iVar2 + 0x194)),
                                 piVar5 != 0)) {
                                piVar5[3] = piVar10[3];
                                *(BlockNode**)(piVar10[3] + 0x10) = piVar5;
                                piVar5[4] = (int)piVar10;
                                piVar10[3] = (int)piVar5;
                                iVar2 = *piVar10;
                                *piVar5 = iVar2;
                                piVar5[1] = (piVar5[1] ^ uVar12) & 1 ^ uVar12;
                                *piVar10 = iVar2 + uVar12;
                                piVar10[1] = (-uVar12 ^ piVar10[1]) & 1 ^ (piVar10[1] & 0xfffffffeU) - uVar12;
                                piVar5[1] = piVar5[1] & 0xfffffffe;
                                FUN_00649490();
                            }
                            return piVar10;
                        }
                    }
                    uVar7 = uVar7 + 1;
                    piVar5 = piVar5 + 8;
                } while (uVar7 < 8);
            }
        }

        // If we reach here, no suitable block found; may need to extend heap
        if (uVar6 == 0) {
            // Compute bin index again
            fVar3 = (float)(int)uVar11;
            if ((int)uVar11 < 0) {
                fVar3 = fVar3 + DAT_00e44578;
            }
            uVar7 = ((uint)fVar3 >> 0x17) - 0x7f;
            if (uVar7 < 6) {
                uVar7 = 6;
            }
            uVar7 = uVar7 - 6;
            if (7 < uVar7) {
                uVar7 = 7;
            }

            piVar5 = *(BlockNode**)(uVar7 * 0x20 + 0x90 + iVar2);
            // Check if the first block in the bin is large enough and aligned
            if (((piVar5[1] & 0xfffffffeU) < requestedSize) || ((alignment - 1 & *piVar5 + offset) != 0)) {
                // Need to allocate more memory from the system
                if (*(int*)(iVar2 + 0x198) == 0) {
                    return 0; // no system allocator
                }
                local_14 = local_14 + 1;
                if (*(uint*)(iVar2 + 0x1a0) <= local_14) {
                    return 0; // exceeded retry limit
                }
                if (uVar11 < requestedSize) {
                    return 0;
                }

                // Release critical section recursively (depth stored at +0x18 of critical section)
                iVar8 = *(int*)(*(int*)(iVar2 + 0x1b8) + 0x18);
                iVar9 = iVar8;
                if (0 < iVar8) {
                    do {
                        pCriticalSection = *(LPCRITICAL_SECTION*)(iVar2 + 0x1b8);
                        // Advance past critical section header (hack)
                        pCriticalSection = (LPCRITICAL_SECTION)((int)pCriticalSection + sizeof(CRITICAL_SECTION));
                        // Modify debug info (trick to fake recursion?)
                        pCriticalSection->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCriticalSection->DebugInfo[-1].SpareWORD + 1);
                        LeaveCriticalSection(*(LPCRITICAL_SECTION*)(iVar2 + 0x1b8));
                        iVar9 = iVar9 - 1;
                    } while (iVar9 != 0);
                }

                // Call system allocator function
                cVar4 = (**(code**)(iVar2 + 0x198))(iVar2, requestedSize, uVar11, *(undefined4*)(iVar2 + 0x19c));

                // Re-acquire critical section
                if (0 < iVar8) {
                    do {
                        pCriticalSection = *(LPCRITICAL_SECTION*)(iVar2 + 0x1b8);
                        EnterCriticalSection(pCriticalSection);
                        pCriticalSection = (LPCRITICAL_SECTION)((int)pCriticalSection + sizeof(CRITICAL_SECTION));
                        pCriticalSection->DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCriticalSection->DebugInfo->Type + 1);
                        iVar8 = iVar8 - 1;
                    } while (iVar8 != 0);
                }

                uVar12 = flags;
                if (cVar4 == '\0') {
                    return 0; // system alloc failed
                }
                // Otherwise, continue loop to find the block
            } else {
                uVar12 = 4; // set bit2 to indicate alignment satisfied
            }
        } else {
            uVar12 = uVar12 & 0xfffffffb; // clear bit2
        }
    } while (true);
}