// FUNC_NAME: PacketStream::PacketStream (constructor)
// Address: 0x0065e100
// Role: Initializes a PacketStream object with two data blocks (send/receive or similar) and a memory pool.
// The object manages a pool (0x38-byte block) and two DataBlock objects (0x18-byte each) that hold serialized data.

void __thiscall PacketStream::PacketStream(void *thisPtr, uint someParam)
{
    int *poolBlock;
    uint temp;
    int *prevBlock;
    uint allocSize;
    int *newBlock;
    void *dataCopy;
    uint *this_ = (uint *)thisPtr;   // this as 32-bit pointer array

    // Initialize basic fields
    this_[0] = &PTR_LAB_00e43124;   // vtable
    this_[1] = 0;                   // field +0x04
    this_[2] = 0;                   // field +0x08
    this_[6] = 0;                   // field +0x18 (first data block pointer, initially null)
    this_[7] = 0;                   // field +0x1C (second data block pointer, initially null)
    *(uint8 *)((uint8 *)this_ + 0x20) = 0; // field +0x20 (flag byte)

    // Get memory pool pointer from some global or allocator
    poolBlock = (int *)FUN_006607b0();  // probably returns a memory manager or pool
    allocSize = 0x38;
    temp = (*(code *)PTR__malloc_00f0cd88)(allocSize);  // allocate 0x38 bytes

    // Initialize static memory pool if not already done
    if (DAT_0120588f == '\0')
    {
        DAT_0120588f = '\x01';
        FUN_00662100(&DAT_01203740);  // init pool structure
        FUN_006622a0(&DAT_01203740);  // init pool structure
    }

    // Allocate a block from the pool; iVar5 == 0 means success
    if (FUN_00663200(&DAT_01203740, temp) == 0)
    {
        this_[4] = someParam;               // field +0x10
        this_[3] = (uint)temp;              // field +0x0C (store pool block)

        // Prepare a 4-byte value in a global buffer (DAT_01204978..7c) for serialization
        DAT_01204978 = 0;
        DAT_01204979 = (uint8)(someParam >> 24);
        DAT_0120497a = (uint8)(someParam >> 16);
        DAT_0120497b = (uint8)(someParam >> 8);
        DAT_0120497c = (uint8)someParam;

        // Call some pack/serialize function with flag 0
        FUN_00663850(&DAT_0120497d, &poolBlock, 0, temp);

        // Create first DataBlock (0x18 bytes) and assign to field +0x1C
        newBlock = (int *)FUN_009c8e50(0x18);
        if (newBlock != (int *)0x0)
        {
            newBlock[4] = (int)poolBlock + 5;    // offset +0x10: size = poolBlock+5?
            newBlock[1] = 0;                     // offset +0x04: some counter
            newBlock[2] = 0;                     // offset +0x08: reference count
            *newBlock = (int)&PTR_LAB_00e42d64;  // vtable
            newBlock[3] = (int)&DAT_01204978;    // offset +0x0C: pointer to global buffer
            *(uint8 *)((uint8 *)newBlock + 0x14) = 0; // offset +0x14: flag
        }

        // Manage reference count on previous block at field +0x1C (should be null initially)
        prevBlock = (int *)this_[7];
        if (prevBlock != (int *)0x0)
        {
            int *refCount = prevBlock + 2;
            *refCount = *refCount - 1;
            if (*refCount == 0)
            {
                (**(code **)(*prevBlock + 8))();  // call destructor via vtable
            }
        }
        this_[7] = (uint)newBlock;
        if (newBlock != (int *)0x0)
        {
            newBlock[2] = newBlock[2] + 1;  // increment reference count
        }

        // Ensure the first DataBlock's data is copied to a local buffer if needed
        int blockAddr = this_[7];
        if (*(uint8 *)(blockAddr + 0x14) == '\0')
        {
            dataCopy = (void *)(*(code *)PTR__malloc_00f0cd88)(*(uint *)(blockAddr + 0x10));
            _memcpy(dataCopy, *(void **)(blockAddr + 0x0C), *(size_t *)(blockAddr + 0x10));
            *(void **)(blockAddr + 0x0C) = dataCopy;
            *(uint8 *)(blockAddr + 0x14) = 1;
        }

        // Now process second DataBlock (field +0x18) similarly with flag 1
        DAT_01204978 = 1;
        DAT_01204979 = (uint8)(someParam >> 24);
        DAT_0120497a = (uint8)(someParam >> 16);
        DAT_0120497b = (uint8)(someParam >> 8);
        DAT_0120497c = (uint8)someParam;
        FUN_00663850(&DAT_0120497d, &poolBlock, 1, temp);

        newBlock = (int *)FUN_009c8e50(0x18);
        if (newBlock != (int *)0x0)
        {
            newBlock[4] = (int)poolBlock + 5;
            newBlock[1] = 0;
            newBlock[2] = 0;
            *newBlock = (int)&PTR_LAB_00e42d64;
            newBlock[3] = (int)&DAT_01204978;
            *(uint8 *)((uint8 *)newBlock + 0x14) = 0;
        }

        prevBlock = (int *)this_[6];
        if (prevBlock != (int *)0x0)
        {
            int *refCount = prevBlock + 2;
            *refCount = *refCount - 1;
            if (*refCount == 0)
            {
                (**(code **)(*prevBlock + 8))();
            }
        }
        this_[6] = (uint)newBlock;
        if (newBlock != (int *)0x0)
        {
            newBlock[2] = newBlock[2] + 1;
        }

        blockAddr = this_[6];
        if (*(uint8 *)(blockAddr + 0x14) == '\0')
        {
            dataCopy = (void *)(*(code *)PTR__malloc_00f0cd88)(*(uint *)(blockAddr + 0x10));
            _memcpy(dataCopy, *(void **)(blockAddr + 0x0C), *(size_t *)(blockAddr + 0x10));
            *(void **)(blockAddr + 0x0C) = dataCopy;
            *(uint8 *)(blockAddr + 0x14) = 1;
        }

        // Set flags indicating initialization complete
        *(uint8 *)((uint8 *)this_ + 0x14) = 1;  // field +0x14 flag
        *(uint8 *)((uint8 *)this_ + 0x20) = 1;  // field +0x20 flag
    }
    return;
}