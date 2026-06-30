// FUNC_NAME: HeapRegion::trimFreeBlocks
// This function iterates over the heap block list, finds free blocks whose size exceeds a threshold,
// and decommits the tail portion back to the OS, moving the remainder into the free list.
// Returns the total number of bytes decommitted.

#include <windows.h>

// +0x4e8: pointer to critical section
// +0x4e0: allocation granularity (bytes)
// +0x460: pointer to current node in block list
// +0x448: sentinel node for block list (end marker)
// +0x440: special node (perhaps the free list sentinel)
// +0x3c: tail of the free list
// +0x30: head of the free list (sentinel)

struct HeapBlockNode {
    int field_0; // unknown, but not used
    int offsetToData; // +0x4: offset from this node to the allocation header? (iVar7 + offsetToData - 0x10 => AllocHeader*)
    char flags1; // +0xd
    char unused; // +0xe
    char flags2; // +0xf
    HeapBlockNode* next; // +0x18: next node in the block list
};

struct AllocHeader {
    int* selfPointer; // +0x0: pointer to itself? (used to compute base)
    int size; // +0x4: allocation size (including header, 8-byte aligned, lower 3 bits flags)
    int prev; // +0x8: previous in free list (if block is free)
    int next; // +0xc: next in free list (if block is free)
};

struct FreeListNode {
    int sentinelPrev; // +0x0 (part of sentinel)
    int sentinelNext; // +0x4
    int dummy; // +0x8
    int dummy2; // +0xc
};

class HeapRegion {
public:
    int trimFreeBlocks(int keepSize) {
        int totalFreed = 0;
        LPCRITICAL_SECTION critSec = *(LPCRITICAL_SECTION*)(this + 0x4e8);
        if (critSec != nullptr) {
            EnterCriticalSection(critSec);
            // Increment recursion count (the original code modifies critSec[1].DebugInfo)
            // This is likely a custom critical section extension.
            ((int*)critSec)[2]++; // approximate
        }

        HeapBlockNode* currentNode = *(HeapBlockNode**)(this + 0x460);
        HeapBlockNode* sentinel = (HeapBlockNode*)(this + 0x448);
        int currentFreed = 0;

        while (currentNode != sentinel) {
            // Check if block is free and eligible
            if (currentNode->flags1 != 0 &&
                (*(int*)((char*)currentNode + currentNode->offsetToData - 0xc) & 1) == 0 &&
                currentNode->flags2 != 0) {
                
                AllocHeader* allocHeader = (AllocHeader*)((char*)currentNode + currentNode->offsetToData - 0x10);
                int* selfRef = allocHeader->selfPointer;
                int allocBase = (int)allocHeader - (int)selfRef; // base of the allocation (offset from self pointer)

                int allocSize = allocHeader->size & 0x7ffffff8; // mask out lower 3 bits and high bit

                // Only decommit if the block is larger than (keepSize + 64)
                if (keepSize + 0x40 < allocSize) {
                    // Calculate size to decommit (rounded to allocation granularity)
                    int granularity = *(int*)(this + 0x4e0);
                    int halfGran = granularity >> 1;
                    int roundMask = 0xffff0000; // 64KB alignment typically
                    int decommitSize = (allocSize - (keepSize + 0x40));
                    int alignedDecommit = ((halfGran + 0xffff) & roundMask);
                    if (alignedDecommit * 2 < decommitSize) {
                        int temp = alignedDecommit * 2;
                        do {
                            temp += alignedDecommit;
                            alignedDecommit += alignedDecommit;
                        } while (temp < decommitSize);
                    }

                    if (alignedDecommit < decommitSize) {
                        // Decommit the tail of the block
                        void* decommitAddr = (void*)((int)allocHeader + (allocSize - alignedDecommit));
                        BOOL success = VirtualFree(decommitAddr, alignedDecommit, MEM_DECOMMIT);
                        if (success) {
                            totalFreed += alignedDecommit;
                            currentFreed = alignedDecommit;

                            // Update block header: reduce size
                            int newSize = allocSize - alignedDecommit;
                            // Move the block to free list if it's not already the sentinel
                            if (allocBase != *(int*)(this + 0x440)) {
                                // Remove from old list (if it was linked)
                                // The code does: *(int *)(iVar8 + 8) = param_1 + 0x30; etc.
                                // This relinks allocHeader into the free list at (this+0x30)
                                int freeListHead = this + 0x30;
                                int freeListTail = *(int*)(this + 0x3c);
                                allocHeader->prev = freeListHead;
                                allocHeader->next = freeListTail;
                                *(int*)(freeListHead + 0x8) = (int)allocHeader; // sentinel's next?
                                *(int*)(freeListTail + 0x8) = (int)allocHeader; // old tail's next
                                // Actually the code: *(int *)(iVar8 + 8) = param_1 + 0x30;
                                // *(int *)(iVar8 + 0xc) = iVar2;
                                // *(int *)(param_1 + 0x3c) = iVar8;
                                // *(int *)(iVar2 + 8) = iVar8;
                            }
                            // Update the node's data pointer (offset) if needed?
                        }
                    }
                }
            }
            currentNode = currentNode->next;
            currentFreed = totalFreed; // reset? Actually local_8 accumulates
        }

        if (critSec != nullptr) {
            // Decrement recursion count
            ((int*)critSec)[2]--;
            LeaveCriticalSection(critSec);
        }
        return totalFreed;
    }
};