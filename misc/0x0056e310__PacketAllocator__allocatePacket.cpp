// FUNC_NAME: PacketAllocator::allocatePacket
// Address: 0x0056e310
// Role: Allocates a packet from a pre-allocated buffer pool, setting up sub-blocks for header, data, and optional extra data.
// This function manages a free list of fixed-size blocks, splitting them into chunks as needed.

bool __thiscall PacketAllocator::allocatePacket(int thisPtr, const PacketInfo* info)
{
    int* currentBlock;      // piVar3
    int* basePtr;           // iVar6
    uint flags;             // uVar5
    int extraSize;          // iVar9
    int headerSize;         // uVar10
    int totalSize;          // iVar9
    int padBeforeBase;      // local_8
    int alignedBaseOffset;  // local_4
    char success;           // cVar4
    int* alignedBase;       // param_2 reassigned
    int* blockHeader;       // puVar7
    int* freeListHead;      // puVar1
    int* prevBlock;         // iVar8
    int unknownField;       // uVar2

    // If the buffer base pointer is null, we can't allocate
    if (*(int*)(thisPtr + 0x10) == 0)
    {
        return false;
    }

    currentBlock = info;
    // info fields: 
    //   info[0] = base pointer (some data array)
    //   info[1] = type index (used to store allocated block in a per-type list)
    //   info[2] = ?
    //   info[3] = block count (number of subblocks?)
    //   info[4] = ?
    //   info[5] = extra block size (in elements of 4 bytes?)
    basePtr = info[0];          // +0x00
    int blockCount = info[3];   // +0x0C
    int extraElemCount = info[5]; // +0x14

    // Determine header size: either from +0x20 or +0x28 based on flags byte in base[1]
    // base[1] is low byte of base[1]? Actually base[1] is basePtr[1] (offset 4)
    uint flagByte = *(uint*)(basePtr + 4) & 0xff;
    if (flagByte < 10)
    {
        headerSize = *(int*)(basePtr + 0x20); // base[8]
    }
    else
    {
        headerSize = *(int*)(basePtr + 0x28); // base[10]
    }
    int headerBlockSize = blockCount * 0x20 + 0x10; // uVar10 = blockCount * 32 + 16

    // Compute total size for aligned allocation
    totalSize = 0;
    if (headerSize >= 0 && blockCount > 0)
    {
        totalSize = (blockCount + 1) * 0x10; // each sub-block header is 16 bytes?
    }
    // totalSize += headerBlockSize? Actually param_2 (alignedBase) starts at headerBlockSize
    alignedBase = (int*)headerBlockSize; // param_2 initially set to headerBlockSize value

    padBeforeBase = 0;
    // Again get flags, but use uint
    if (flagByte < 10)
    {
        uint baseFlags = *(uint*)(basePtr + 0x20);
    }
    else
    {
        uint baseFlags = *(uint*)(basePtr + 0x28);
    }
    // Check if flag 0x40000000 is clear and extraElemCount > 0
    uint baseFlags2 = flagByte < 10 ? *(uint*)(basePtr + 0x20) : *(uint*)(basePtr + 0x28);
    if ((baseFlags2 & 0x40000000) == 0 && extraElemCount > 0)
    {
        padBeforeBase = extraElemCount * 4 + 0x10; // 4 bytes per element plus 16 header
        alignedBase = (int*)((int)alignedBase + padBeforeBase);
    }

    // Align to 16-byte boundary
    if (((uint)alignedBase & 0xf) != 0)
    {
        int alignment = 0x10 - ((uint)alignedBase & 0xf);
        padBeforeBase = (short)padBeforeBase + (short)alignment;
        alignedBase = (int*)((int)alignedBase + alignment);
    }

    // Call an alignment function to get the actual base offset for the block
    success = FUN_0056e5e0(alignedBase, &alignedBaseOffset); // likely returns whether successful
    if (success == 0)
    {
        return false;
    }

    // Get the free list head and the block pointer
    blockHeader = (int*)(*(int*)(thisPtr + 0x20) + alignedBaseOffset); // base + offset
    freeListHead = *(int**)(thisPtr + 0x10); // current free block

    // Initialize the block header (first sub-block?)
    freeListHead[8] = (int)blockHeader;           // +0x20: pointer to first sub-block
    *(short*)((int)blockHeader + 10) = (short)headerBlockSize; // sub-block total size
    blockHeader[0] = 0;   // next pointer?
    blockHeader[1] = 0;   // prev?
    *(char*)(blockHeader + 2) = 1;   // some flag
    *(char*)((int)blockHeader + 9) = 0; // another flag
    blockHeader[3] = blockCount;      // number of sub-blocks

    // Setup second sub-block (data portion)
    int* dataBlock = blockHeader + blockCount * 8 + 4; // skip header sub-block and its sub-blocks
    // Determine if we need a data block
    if (headerSize >= 0 && blockCount >= 1) // condition: iVar8 >= 0 && piVar3[3] >= 1
    {
        freeListHead[9] = (int)dataBlock;   // +0x24: pointer to data block
        dataBlock[0] = 0;
        dataBlock[1] = 0;
        *(char*)(dataBlock + 2) = 1;
        *(char*)((int)dataBlock + 9) = 0;
        *(short*)((int)dataBlock + 10) = (short)totalSize; // total sub-block size
        dataBlock[3] = blockCount;
        dataBlock = (int*)((int)dataBlock + totalSize); // advance
    }
    else
    {
        freeListHead[9] = 0; // no data block
    }

    // Setup third sub-block (extra data)
    int* extraBlock = dataBlock; // reuse
    uint baseFlags3 = flagByte < 10 ? *(uint*)(basePtr + 0x20) : *(uint*)(basePtr + 0x28);
    if ((baseFlags3 & 0x40000000) == 0 && extraElemCount > 0)
    {
        freeListHead[10] = (int)extraBlock;   // +0x28: pointer to extra block
        extraBlock[0] = 0;
        extraBlock[1] = 0;
        *(char*)(extraBlock + 2) = 1;
        *(char*)((int)extraBlock + 9) = 0;
        *(short*)((int)extraBlock + 10) = (short)padBeforeBase;
        extraBlock[3] = extraElemCount;
    }
    else
    {
        freeListHead[10] = 0;
    }

    // Save the old head pointer
    unknownField = freeListHead[0]; // original next
    // Store the aligned base pointer
    freeListHead[0xb] = (int)alignedBase; // +0x2C

    // Copy the packet info into the block (first 24 bytes of info)
    *(undefined8*)(freeListHead + 2) = *(undefined8*)info; // bytes 0-7
    *(undefined8*)(freeListHead + 4) = *(undefined8*)(info + 2); // 8-15
    *(undefined8*)(freeListHead + 6) = *(undefined8*)(info + 4); // 16-23

    // Update free list
    *(int*)(thisPtr + 0x1c) = *(int*)(thisPtr + 0x1c) - 1; // decrement free count
    *(int*)(thisPtr + 0x10) = unknownField; // new head is old next

    // Reset the current node's next and set prev
    freeListHead[0] = 0;
    freeListHead[1] = *(int*)(thisPtr + 0x18); // set prev to current tail

    // Insert into the all-blocks list (if tail is null, this is first)
    if (*(int*)(thisPtr + 0x14) == 0) // head of all blocks?
    {
        *(int**)(thisPtr + 0x14) = freeListHead; // new head
    }
    else
    {
        **(int**)(thisPtr + 0x18) = (int)freeListHead; // current tail's next = new node
    }

    // Increment total allocated count
    *(int*)(thisPtr + 0x1030) = *(int*)(thisPtr + 0x1030) + 1;

    // Update tail to new node
    *(int**)(thisPtr + 0x18) = freeListHead;

    // Insert into per-type list (info[1] is the type index)
    int typeIndex = info[1]; // +0x04
    prevBlock = *(int*)(thisPtr + 0x30 + typeIndex * 4); // old head of type list
    *(int**)(thisPtr + 0x30 + typeIndex * 4) = freeListHead; // new head
    freeListHead[0xd] = 0; // +0x34: next in type list?
    if (prevBlock == 0)
    {
        freeListHead[0xc] = 0; // +0x30: prev in type list?
    }
    else
    {
        *(int**)(prevBlock + 0x34) = freeListHead; // prevBlock->nextType = new node
        freeListHead[0xc] = (int)prevBlock; // new node->prevType = prevBlock
    }

    // Call some post-allocation functions (likely debug/statistics)
    FUN_0056f680();
    FUN_0056f6e0();
    FUN_0056f740();

    return true;
}