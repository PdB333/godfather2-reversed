// FUNC_NAME: Heap::validate

#include <windows.h> // for CRITICAL_SECTION

// Forward declarations of helper functions (assumed to be in same module)
int checkBlock(int blockPtr);
int checkBlockHeader(int blockPtr);
int checkFreeList(int freeListHead);
int checkSomething(int offset);
bool checkAllocation(int heapPtr);

// Heap class (partial reconstruction)
class Heap {
public:
    // Fields (offsets relative to this)
    // +0x00: unknown (maybe size or flags)
    // +0x04: flags/size (bit0 used)
    // +0x08: array of 10 pointers to free blocks? (actually linked list heads)
    // +0x30: array of 128 (0x80) pointers? (actually a list of allocated blocks)
    // +0x430: bitmask for something (size 4 bytes)
    // +0x440: pointer to current allocation context?
    // +0x448: end marker for list at 0x460
    // +0x460: list of memory regions (linked list)
    // +0x464: pointer to current region in list
    // +0x488: some counter
    // +0x490: another counter
    // +0x49c: end marker for list at 0x4a8
    // +0x4a8: list of something (maybe free blocks)
    // +0x4cc: some size
    // +0x4d0: some flag
    // +0x4d4: some power-of-two check
    // +0x4e8: critical section pointer

    int validate(int validationLevel) {
        LPCRITICAL_SECTION criticalSection = *(LPCRITICAL_SECTION*)(this + 0x4e8);
        int result = 0;

        if (criticalSection != nullptr) {
            EnterCriticalSection(criticalSection);
            // Some debug info increment (likely a counter)
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo->Type + 1);
        }

        if (validationLevel > 0) {
            int local_14 = 0;
            // Check if allocation context is valid
            if (*(int*)(this + 0x440) == 0 || *(int*)(this + 0x440) == (int)(this + 0x30)) {
                if (criticalSection != nullptr) {
                    criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
                    LeaveCriticalSection(criticalSection);
                }
                return 0;
            }

            uint flags = *(uint*)(this + 4) & 0xfffffffe;
            uint score = (uint)(0x50 < flags); // initial score based on flags

            if (validationLevel > 1) {
                // Iterate over the 10 free block lists (at +0x08)
                uint listIndex = 0;
                uint* listPtr = (uint*)(this + 8);
                do {
                    uint block = *listPtr;
                    int iterations = 0;
                    while (block != 0 && iterations < 2000000) {
                        // Check if block is within a known region
                        for (uint region = *(uint*)(this + 0x460); region != (uint)(this + 0x448); region = *(uint*)(region + 0x18)) {
                            if (region <= block && block < *(int*)(region + 4) + region) {
                                // Block is inside a region, mark as valid
                                // (no score addition)
                                break;
                            }
                        }
                        // If not found in any region, add to score
                        int notInRegion = 1; // default: not in region
                        // Actually the loop above sets a flag; we need to replicate logic
                        // Simplified: we'll just use the decompiled logic
                        // The decompiled code has a goto that sets iVar6=0 if found, else 1
                        // We'll simulate with a boolean
                        bool found = false;
                        for (uint region = *(uint*)(this + 0x460); region != (uint)(this + 0x448); region = *(uint*)(region + 0x18)) {
                            if (region <= block && block < *(int*)(region + 4) + region) {
                                found = true;
                                break;
                            }
                        }
                        int iVar6 = found ? 0 : 1;

                        uint blockSize = *(uint*)(block + 4);
                        block = *(uint*)(block + 0xc); // next block in list
                        iterations++;
                        score += iVar6 + (uint)((blockSize >> 3 & 0xfffffff) - 2 != listIndex) +
                                 (uint)((blockSize & 0x80000000) == 0) +
                                 ((byte)~(byte)(blockSize >> 2) & 1) +
                                 (uint)(1999999 < iterations);
                    }
                    listPtr++;
                    listIndex++;
                } while (listIndex < 10);

                // Now iterate over the allocated blocks list (at +0x30)
                int* allocPtr = (int*)(this + 0x30);
                uint allocIndex = 0;
                do {
                    int* block = (int*)*allocPtr;
                    if (allocIndex < 2) {
                        // For first two entries, just check if block is null
                        bool isNull = (block == nullptr);
                        score += isNull;
                    } else {
                        // Check the linked list of blocks
                        int* current = (int*)block[3]; // next pointer
                        score += (block == nullptr);
                        uint* countPtr = (uint*)(uint)(current == (allocPtr - 2));
                        for (; current != block; current = (int*)current[3]) {
                            if (current == (allocPtr - 2)) {
                                countPtr = (uint*)((int)countPtr + 1);
                            } else {
                                // Check if current is within a region
                                bool found = false;
                                for (int* region = *(int**)(this + 0x460); region != (int*)(this + 0x448); region = (int*)region[6]) {
                                    if (region <= current && current < (int*)(region[1] + (int)region)) {
                                        found = true;
                                        break;
                                    }
                                }
                                score += found ? 0 : 1;
                            }
                        }
                        bool isNull = (countPtr == nullptr);
                        score += isNull;
                    }
                    allocIndex += 2;
                    allocPtr += 2;
                } while (allocIndex < 0x100);

                // Additional checks
                score += (99999 < *(uint*)(this + 0x4cc)) +
                         (uint)(*(int*)(this + 0x4d0) == 0) +
                         (uint)((*(uint*)(this + 0x4d4) - 1 & *(uint*)(this + 0x4d4)) != 0) +
                         (uint)(0x58 < flags);

                // Iterate over free lists again to check sizes
                int listIdx = 0;
                uint* listPtr2 = (uint*)(this + 8);
                do {
                    uint block = *listPtr2;
                    if ((int)((*(uint*)(this + 4) >> 3) - 2) < listIdx) {
                        score += (block != 0);
                    }
                    for (; block != 0; block = *(uint*)(block + 0xc)) {
                        local_14 += (*(uint*)(block + 4) & 0x7ffffff8);
                        score += ((*(uint*)(block + 4) >> 3 & 0xfffffff) - 2 != listIdx);
                    }
                    listPtr2++;
                    listIdx++;
                } while (listIdx < 10);

                if (local_14 != 0) {
                    score += ((byte)~*(byte*)(this + 4) & 1);
                }

                // Iterate over allocated blocks again with size checks
                uint* allocPtr2 = (uint*)(this + 0x30);
                uint allocIdx2 = 1;
                do {
                    if (allocIdx2 > 1) {
                        uint bitmask = *(uint*)(this + 0x430 + ((allocIdx2 >> 5) * 4));
                        if ((bitmask & (1 << (allocIdx2 & 0x1f))) == 0) {
                            score += (allocPtr2 != (uint*)*(int*)((int)allocPtr2 + 8));
                        }
                    }
                    int block = *(int*)((int)allocPtr2 + 8);
                    if ((uint*)block != allocPtr2) {
                        // Process block
                        int iVar6 = checkBlock(block);
                        score += iVar6;
                        uint blockSize = *(uint*)(block + 4) & 0x7ffffff8;
                        if (allocIdx2 > 1) {
                            uint sizeClass;
                            if (blockSize < 0x200) {
                                sizeClass = blockSize >> 3;
                            } else if (blockSize >> 6 < 0x21) {
                                sizeClass = (blockSize >> 6) + 0x38;
                            } else if (blockSize >> 9 < 0x15) {
                                sizeClass = (blockSize >> 9) + 0x5b;
                            } else if (blockSize >> 0xc < 0xb) {
                                sizeClass = (blockSize >> 0xc) + 0x6e;
                            } else if (blockSize >> 0xf < 5) {
                                sizeClass = (blockSize >> 0xf) + 0x77;
                            } else if (blockSize >> 0x12 < 3) {
                                sizeClass = (blockSize >> 0x12) + 0x7c;
                            } else {
                                sizeClass = 0x7e;
                            }
                            score += (sizeClass != allocIdx2);
                            if (blockSize > 0x1ff) {
                                if (((uint*)*(int*)(block + 8) == allocPtr2) ||
                                    (blockSize <= (*(uint*)(*(int*)(block + 8) + 4) & 0x7ffffff8))) {
                                    iVar6 = 0;
                                } else {
                                    iVar6 = 1;
                                }
                                score += iVar6;
                            }
                        }
                        // Walk through block's internal chunks
                        uint chunkPtr = blockSize + block;
                        do {
                            uint chunkSize = *(uint*)(chunkPtr + 4) & 0x7ffffff8;
                            if (chunkSize < 0x10) {
                                // Check if chunk is at end of region
                                for (uint region = *(uint*)(this + 0x460); region != (uint)(this + 0x448); region = *(uint*)(region + 0x18)) {
                                    if (region <= chunkPtr && chunkPtr < *(int*)(region + 4) + region) {
                                        if (*(int*)(region + 4) - 0x10 + region <= chunkPtr) {
                                            goto nextBlock;
                                        }
                                        break;
                                    }
                                }
                            }
                            if (((*(byte*)(chunkSize + 4 + chunkPtr) & 1) == 0) || (chunkSize < 0x10)) {
                                goto nextBlock;
                            }
                            int iVar6 = checkBlockHeader(chunkPtr);
                            score += iVar6;
                            chunkPtr += (*(uint*)(chunkPtr + 4) & 0x7ffffff8);
                        } while (true);
                    }
nextBlock:
                    allocPtr2 = (uint*)((int)allocPtr2 + 8);
                    allocIdx2++;
                } while (allocIdx2 < 0x80);

                // Iterate over another list (at +0x4a8)
                for (int* listPtr3 = *(int**)(this + 0x4a8); listPtr3 != (int*)(this + 0x49c); listPtr3 = (int*)listPtr3[3]) {
                    score += ((byte)~(byte)((uint)listPtr3[1] >> 1) & 1) +
                             ((byte)~(byte)(*(uint*)((int)listPtr3 + (4 - *listPtr3)) >> 1) & 1);
                }
            }

            // Call checkFreeList on the allocation context
            int freeListScore = checkFreeList(*(int*)(this + 0x440));
            score += freeListScore + (uint)(*(int*)(this + 0x488) < 0) +
                     (uint)(*(int*)(this + 0x490) < *(int*)(this + 0x488));
        }

        if (validationLevel > 2) {
            // Iterate over list at +0x4a8 again with different check
            for (int* listPtr4 = *(int**)(this + 0x4a8); listPtr4 != (int*)(this + 0x49c); listPtr4 = (int*)listPtr4[3]) {
                int iVar6 = checkSomething((int)listPtr4 - *listPtr4);
                score += iVar6;
            }

            // Iterate over regions list (at +0x464)
            uint* regionPtr = *(uint**)(this + 0x464);
            if (regionPtr != (uint*)(this + 0x448)) {
                do {
                    if (score != 0) break;
                    uint regionSize = regionPtr[1];
                    for (uint addr = *regionPtr; addr < (regionSize - 0x10) + (int)regionPtr; addr += (*(uint*)(addr + 4) & 0x7ffffff8)) {
                        if (!checkAllocation((int)this)) {
                            score = 1;
                            break;
                        }
                    }
                    regionPtr = (uint*)regionPtr[7];
                } while (regionPtr != (uint*)(this + 0x448));
            }
        }

        if (criticalSection != nullptr) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }

        return score;
    }
};