// FUNC_NAME: memoryPoolAllocateNode
void memoryPoolAllocateNode(void)
{
    // Global pool manager structure at 0x01205568
    // +0x00: unknown
    // +0x04: head of free list (PoolBlock*)
    // +0x08: current free pointer (PoolBlock*)
    // +0x0c: block size (0x50)
    // +0x10: total capacity (or end offset)
    int* poolBase = (int*)DAT_01205568;
    int magic = DAT_00e2b1a4; // constant used for initialization

    PoolBlock* freePtr = *(PoolBlock**)(poolBase + 2); // +0x08
    PoolBlock* nextFree = freePtr + 0x14; // advance by 20 bytes (header size?)

    // Check if there is room in the pre-allocated buffer
    // The end is computed as (poolBase[4] + poolBase[3]) cast to pointer
    if (nextFree <= (PoolBlock*)(poolBase[4] + poolBase[3])) {
        // Initialize the block at freePtr
        if (freePtr != NULL) {
            freePtr->field4 = 0;   // +0x10? Actually offset 4*4=16? No, puVar3[4] is at offset 16
            freePtr->field5 = 0;   // +0x14
            freePtr->field6 = 0;   // +0x18
            freePtr->field7 = magic; // +0x1c
            freePtr->field10 = 0;  // +0x28
            freePtr->field9 = 0;   // +0x24
            freePtr->field8 = 0;   // +0x20
            freePtr->field11 = magic; // +0x2c
            *(uint8*)((int)freePtr + 0x30) = 0; // +0x30
            *(uint8*)((int)freePtr + 0x31) = 0;
            *(uint8*)((int)freePtr + 0x32) = 0;
            *(uint8*)((int)freePtr + 0x33) = 0;
            freePtr->field13 = 0;  // +0x34
            freePtr->field14 = 0;  // +0x38
            freePtr->field15 = 0;  // +0x3c
            freePtr->field16 = 0;  // +0x40
            freePtr->field17 = 0;  // +0x44
        }
        // Set linked list pointers
        freePtr->next = *(PoolBlock**)(poolBase[0] + 4); // +0x00
        freePtr->prev = NULL; // +0x04
        *(uint8*)((int)freePtr + 8) = 0; // +0x08
        *(uint8*)((int)freePtr + 9) = 1; // +0x09
        *(uint16*)((int)freePtr + 10) = 0x50; // +0x0a
        freePtr->field3 = 0; // +0x0c

        // Insert into doubly linked list
        if (*(int*)(poolBase[0] + 4) != 0) {
            *(PoolBlock**)(*(int*)(poolBase[0] + 4) + 4) = freePtr;
        }
        *(PoolBlock**)(poolBase[0] + 8) = nextFree; // update free pointer
        *(PoolBlock**)(poolBase[0] + 4) = freePtr;  // update head
        return;
    }

    // No room in pre-allocated buffer; walk the free list to find a gap
    PoolBlock* current = *(PoolBlock**)(poolBase[0] + 4); // head of list
    PoolBlock* prev = current;
    while (true) {
        PoolBlock* candidate = current;
        int blockSize = *(int*)(poolBase[0] + 3); // +0x0c
        if (candidate != NULL) {
            blockSize = (uint16)*(ushort*)((int)candidate + 10) + (int)candidate;
        }
        // Check if gap is large enough ( > 0x4f )
        if (0x4f < (uint)((int)prev - blockSize)) break;
        if (candidate == NULL) return;
        current = (PoolBlock*)*candidate; // next
        prev = candidate;
    }

    // Allocate a new block from heap
    long long allocResult;
    if (blockSize == 0) {
        allocResult = (long long)(uint64)prev << 32; // zero extension
    } else {
        allocResult = FUN_0056f3c0(); // heap allocation
    }
    int highPart = (int)(allocResult >> 32);
    PoolBlock* newBlock = (PoolBlock*)(int)allocResult;

    // Initialize the new block
    newBlock->next = highPart;
    newBlock->prev = prev;
    *(uint8*)((int)newBlock + 8) = 0;
    *(uint8*)((int)newBlock + 9) = 1;
    *(uint16*)((int)newBlock + 10) = 0x50;
    newBlock->field3 = 0;

    // Insert into list
    if (highPart != 0) {
        *(int*)(highPart + 4) = blockSize;
    }
    *prev = blockSize;
}