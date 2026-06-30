// FUNC_NAME: MemoryManager::allocateFromPool
undefined4* __thiscall MemoryManager::allocateFromPool(int this, int pool)
{
    undefined4* allocatedBlock;
    undefined4* poolFreeBlock; // Pointer to a free block in the pool
    int* allocationNode; // 12-byte allocation tracking node
    int masterListHead; // Head of the master allocation list for this pool size
    undefined4 local_20[3]; // Temporary storage for stack-based buffer if no existing node
    undefined4* freeListFromThis; // this+0x14 content, possibly a free node list head

    // Retrieve the free block from the pool's free list
    // pool+0x14: offset of freeList pointer
    poolFreeBlock = *(undefined4**)(pool + 0x14); 

    // Update pool's next free pointer (possibly for double-linked free list)
    // pool+0x1c: offset of nextFree pointer (or tail)
    *(undefined4**)(pool + 0x1c) = poolFreeBlock;

    // Initialize return value to 0 (failure)
    allocatedBlock = (undefined4*)0x0;

    // Check if the free block is valid: must be aligned to 16 bytes and have size field at +8 equal to 0x10 (size 16 bytes)
    // poolFreeBlock[2] is typically the size or magic number.
    if ((((uint)poolFreeBlock & 0xf) == 0) && (poolFreeBlock[2] == 0x10))
    {
        // Mark the block as used (set to 0) and assign vtable pointer
        poolFreeBlock[1] = 0;
        *poolFreeBlock = &PTR_FUN_00e40838; // vtable for the allocated object

        // Call some initialization routine (maybe clears block or sets initial state)
        FUN_00601c80(); // TODO: Identify proper name

        // Copy data from pool's source data (pool+4) into the allocated block
        // pool+4: offset of source data buffer
        undefined4* sourceData = *(undefined4**)(pool + 4);
        undefined4 src0 = sourceData[0];
        undefined4 src1 = sourceData[1];
        undefined4 src3 = sourceData[3];
        poolFreeBlock[4] = src0;
        poolFreeBlock[5] = src1;
        poolFreeBlock[6] = sourceData[2]; // Note: order is src[2] first, then src[0], src[1], src[3]
        poolFreeBlock[7] = src3;

        // Retrieve master list head for this pool size from the memory manager
        // this+0x28 points to a table/array of size classes; dereference twice to get the head
        // This assumes (this+0x28) -> array of size class descriptors, each with a linked list at offset 4
        masterListHead = *(int*)(*(int*)(this + 0x28) + 4);

        // Get pointer to a free allocation node from the manager's own pool (this+0x14)
        freeListFromThis = *(undefined4**)(this + 0x14);
        if (freeListFromThis == (undefined4*)0x0)
        {
            // If no free nodes available, use a local stack buffer as temporary node
            local_20[0] = 0;
            local_20[1] = 0;
            local_20[2] = 0;
            freeListFromThis = local_20;
        }

        // Allocate a 12-byte allocation tracking node using a custom allocator (size 0xc = 12)
        // The allocator function is at **(this+0x10)
        allocationNode = (int*)(**(code**)**(undefined4**)(this + 0x10))(0xc, freeListFromThis);

        if (allocationNode != (int*)0x0)
        {
            // Initialize node fields:
            // Node[0] = masterListHead (identifier for the size class)
            *allocationNode = masterListHead;
        }
        if (allocationNode + 1 != (int*)0x0) // Always true if allocationNode != 0, but safety check
        {
            // Node[1] = unaff_ESI (likely a global or passed pointer, possibly the manager itself)
            allocationNode[1] = unaff_ESI;
        }
        if ((uint*)(allocationNode + 2) != (uint*)0x0)
        {
            // Node[2] = pointer to the allocated block
            allocationNode[2] = (int)poolFreeBlock;
        }

        // Insert the allocation node into the master linked list for this size class
        // The list is represented as a head pointer at masterListHead+4? Or is masterListHead itself the head?
        // Typically: node->next = old_head; old_head->prev = node; head = node;
        // Here we see:
        // *(int**)(masterListHead + 4) = allocationNode;  // Set head's next to new node (or set list head to new node)
        // *(int**)allocationNode[1] = allocationNode;     // Set whatever allocationNode[1] points to (maybe old head's prev) to new node
        // This is a common pattern for inserting at the front of a doubly linked list.
        // We assume masterListHead+4 is a pointer to the current head, and allocationNode[1] is the address of the head pointer.
        // Or allocationNode[1] points to the 'prev' field of the old head.
        *(int**)(masterListHead + 4) = allocationNode;
        *(int**)allocationNode[1] = allocationNode;

        // Update the manager's free node list (this+0x14) with this newly inserted node?
        // No, the function proceeds with debug logging.

        // Log allocation event
        // Use global string DAT_01222228 as format/message
        // local_1c = DAT_01222228
        // uStack_14 = 0
        // local_18 = poolFreeBlock
        // FUN_00408a00 => likely debugOutput or assert
        local_20[1] = DAT_01222228; // reinterpretation: local_1c is offset 4 in local_20? Actually local_20 is array of 3; local_1c is separate? Decompiler shows local_20, local_1c, local_18, uStack_14 as separate locals. Need to be careful.
        // But in the decompiled, they used &local_1c to call FUN_00408a00. So probably a struct.
        // We'll just note the call.
        // It is likely: debugPrintAllocation(DAT_01222228, 0, poolFreeBlock);

        allocatedBlock = poolFreeBlock; // Success, return the allocated block
    }

    return allocatedBlock;
}