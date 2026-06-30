// FUNC_NAME: MemoryManager::allocateBlock
// Function address: 0x00647e90
// Purpose: Allocates a memory block from a custom heap, handling splitting, alignment, and critical section locking.
// The heap structure (at this pointer +0x448) uses a linked list of free/used blocks with metadata embedded.

#include <windows.h> // for CRITICAL_SECTION, VirtualQuery, etc.

// Heap block header layout (fields at offsets within block):
// +0x00: pointer to next block (or special value)
// +0x04: size of block? (param_2[1])
// +0x08: size of block? (param_2[2])
// +0x0C: flags byte? param_2[3] (byte)
// +0x0D-0x0F: two bytes? (param_4, param_5)
// +0x10: arg6 (param_2[4])
// +0x14: arg7 (param_2[5])
// +0x18: previous block pointer? (param_2[6])
// +0x1C: pointer to heap base? (param_2[7]) offset into block: 0x1C = 7*4
// Also: at block+0x4 (?) used for alignment trick: param_2[0] points to itself+0x27 masked.

class MemoryManager {
public:
    // +0x4D4: alignment constant
    // +0x4E0? no, +0x4E8: critical section pointer
    // +0x460: head of free list? (pointer to block)
    // +0x440: condition? (used for some check)

    // Internal helper functions (called from this function):
    int FUN_006482d0(int) const;  // checks if allocation from pool is needed?
    void FUN_00644a80(int);       // updates some state (maybe set flag)

    // The main allocator: returns 1 on success, 0 on failure.
    int __thiscall allocateBlock(uint* blockPtr, uint size, uchar paramFlag1, uchar paramFlag2, uint param6, uint param7) {
        LPCRITICAL_SECTION critSec = *(LPCRITICAL_SECTION*)((uint)this + 0x4E8);
        if (critSec != 0) {
            EnterCriticalSection(critSec);
            // The debug fields manipulation is likely a side effect; ignore for reconstruction.
        }

        if (blockPtr == 0) {
            // If block pointer is null, try to allocate from a pool? (size != 0 condition)
            if (size != 0) {
                int result = FUN_006482d0(1);
                if (result != 0) {
                    FUN_00644a80(1);
                    if (critSec != 0) {
                        LeaveCriticalSection(critSec);
                    }
                    return 1;
                }
            }
        }
        else if (size > 0x3F) { // size > 63? Only process large blocks
            // Align size to heap granularity (+0x4D4)
            uint alignment = *(uint*)((uint)this + 0x4D4);
            if (size % alignment != 0) {
                size = size & ~(alignment - 1);
            }
            // 16-byte alignment
            if ((size & 0xF) != 0) {
                size = size & 0xFFFFFFF0;
            }

            // Setup block header (param_2 is the block pointer)
            *blockPtr = ((uint)blockPtr + 0x27) & 0xFFFFFFF8;  // special address for next pointer?

            // Write flags
            *(uchar*)((uint)blockPtr + 0x0D) = paramFlag1;
            *(uchar*)((uint)blockPtr + 0x0E) = paramFlag1;
            *(uchar*)((uint)blockPtr + 0x0F) = paramFlag2;

            // Write heap base pointer (+0x448)
            blockPtr[7] = (uint)this + 0x448;

            // Set size fields
            blockPtr[1] = size; // total size? 
            blockPtr[2] = size; // used size?
            *(uchar*)((uint)blockPtr + 0x0C) = 0; // flags byte zero

            blockPtr[4] = param6;
            blockPtr[5] = param7;

            // Link into free list (or allocated list)
            blockPtr[6] = *(uint*)((uint)this + 0x460); // previous head
            *(uint**)((uint)this + 0x460) = &blockPtr;   // new head
            *(uint**)(blockPtr[6] + 0x1C) = &blockPtr;   // update back link of previous head

            // If param6 == 0, check memory state using VirtualQuery
            if (param6 == 0) {
                MEMORY_BASIC_INFORMATION mbi;
                VirtualQuery(blockPtr, &mbi, 0x1C);
                if (mbi.State == MEM_COMMIT) { // 0x2000
                    blockPtr[1] = 0; // mark as free? 
                }
            }

            // Update internal state
            uint* nextBlock = (uint*)*blockPtr; // first field is pointer to next block?
            uint available = (uint)blockPtr + (size - (uint)nextBlock);
            uint alignedAvail = available & 0x7FFFFFF8;
            uint splitSize = alignedAvail - 0x10;

            // Set up split block (for free part)
            nextBlock[1] = (alignedAvail & 0x80000007) | 1 | splitSize; // flags? 
            nextBlock[0] = 0;
            *(uint*)((uint)nextBlock + splitSize + 0x4 - 0x10?) ... // unclear, but it sets some sentinel values

            // The code sets:
            // *(undefined4 *)((alignedAvail - 0xC) + (int)nextBlock) = 8;
            // *(uint *)(splitSize + (int)nextBlock) = splitSize;
            // *(undefined4 *)((alignedAvail - 8) + (int)nextBlock) = 8;
            // *(undefined4 *)((alignedAvail - 4) + (int)nextBlock) = 9;
            // This is likely splitting the block and setting boundary tags.

            FUN_00644a80(*(int*)((uint)this + 0x440) != (uint)(this + 0x30));

            if (critSec != 0) {
                LeaveCriticalSection(critSec);
            }
            return 1;
        }

        // Failure case
        if (critSec != 0) {
            LeaveCriticalSection(critSec);
        }
        return 0;
    }
};