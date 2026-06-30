// FUN_0042c1f0: TNLConnection::init
// This function initializes a TNLConnection object, including setting up a fixed-size block allocator (pool of 256 blocks of 36 bytes each).
// It is called as a constructor helper, taking multiple configuration parameters.
// The object layout includes fields at various offsets, documented in comments.

int TNLConnection::init(void* heapMgr, int param3, int param4, int param5, int param6, int param7, int param8, int param9, int flags)
{
    int* freeListHead;
    int* freeNode;
    int* bufferPtr;
    uint poolSize;
    int index;
    int* node;
    int i;
    undefined4* poolHeader;
    bool globalFlag;

    // Zero out fields from +0x60 to +0x78 (8 qwords)
    *(undefined8*)(this + 0x60) = 0;
    *(undefined8*)(this + 0x68) = 0;
    *(undefined8*)(this + 0x70) = 0;
    *(undefined8*)(this + 0x78) = 0;

    // Zero out a large array from offset +0x88 to +0x1088 (256 entries of 16 bytes each)
    // This likely stores indices or metadata for the pool or an array of objects.
    index = 0xff;
    poolHeader = (undefined4*)(this + 0x90);
    do {
        poolHeader[-2] = 0;  // +0x88
        poolHeader[-1] = 0;  // +0x8C
        *poolHeader = 0;     // +0x90
        poolHeader[1] = 0;   // +0x94
        poolHeader += 4;     // move by 16 bytes
        index--;
    } while (index >= 0);
    *(undefined4*)(this + 0x1088) = 0;

    // Call some init function 6 times (probably for subsystems)
    for (i = 5; i >= 0; i--) {
        FUN_004c4430();
    }

    // Set various configuration fields
    *(undefined4*)(this + 0x3a0c) = 0xffffffff;  // -1
    *(undefined4*)(this + 0x3a10) = 0;
    *(undefined4*)(this + 0x3a24) = 0;
    *(undefined4*)(this + 0x3a28) = 0;
    *(undefined4*)(this + 0x3a3c) = 0;
    *(undefined4*)(this + 0x3a40) = 0;
    *(undefined4*)(this + 0x3a54) = 0;
    *(undefined4*)(this + 0x3a58) = 0;
    *(undefined4*)(this + 0x3a6c) = 0;
    *(undefined1*)(this + 0x3a70) = 0;   // byte
    *(undefined4*)(this + 0x3af4) = 0;   // count of something
    *(undefined4*)(this + 0x3af8) = flags;

    // Initialize external resources (likely manager references)
    FUN_004c4270(heapMgr, 1);
    FUN_004c4270(param3, 1);
    FUN_004c4270(param4, 0);
    FUN_004c4270(param5, 1);
    FUN_004c4270(param8, 1);
    FUN_004c4270(param7, 1);

    // Store the return value of the last call (maybe a pointer to the allocator)
    *(undefined4*)(this + 0x39fc) = in_EAX;  // +0x39fc points to a vtable-based allocator

    FUN_004c7470();  // Additional initialization

    globalFlag = DAT_01205358 != '\0';

    *(undefined4*)(this + 0x3a04) = 0;
    *(undefined4*)(this + 0x3a08) = 0;
    *(undefined1*)(this + 0x84) = 0;  // byte
    *(undefined1*)(this + 0x85) = 0;  // byte

    if (globalFlag) {
        // Traverse a linked list (PTR_PTR_011285b0) and add entries to array at +0x3a74, then call their virtual init method
        undefined** listPtr = &PTR_PTR_011285b0;
        undefined* current = PTR_PTR_011285b0;
        while (current != (undefined*)0x0) {
            int** obj = (int**)*listPtr;
            if (*(uint*)(this + 0x3af4) < 0x20) {
                *(int***)(this + 0x3a74 + *(uint*)(this + 0x3af4) * 4) = obj;
                *(int*)(this + 0x3af4) = *(int*)(this + 0x3af4) + 1;
            }
            (**(code**)(*obj + 4))();  // call virtual function at offset 4 (init)
            listPtr++;
            current = *listPtr;
        }

        // Traverse another linked list (PTR_PTR_01128620) and call their virtual init methods
        if (DAT_01205358 != '\0') {
            listPtr = &PTR_PTR_01128620;
            int** obj = (int**)PTR_PTR_01128620;
            while (obj != (int**)0x0) {
                (**(code**)(*obj + 4))();  // call virtual function at offset 4
                listPtr++;
                obj = (int**)*listPtr;
            }
        }
    }

    // Check flags (bit 2) and possibly enable profiling
    poolSize = *(uint*)(this + 0x3af8) & 4;
    if ((int)(&DAT_00f15a4c)[*(int*)(**(int**)(offset_of_FS + 0x2c) + 0x34) == 0] < 1) {
        poolSize = 0;
    }
    FUN_0041cf70(poolSize);

    // Set up a fixed-size block allocator inside a buffer
    // First allocate a large buffer (0x2400 bytes) via the allocator interface
    int allocArgs1[] = { 2, 4, 0 };
    bufferPtr = (int*)(**(code**)**(undefined4**)(this + 0x39fc))(0x2400, &allocArgs1);

    // Then allocate a header structure (0x20 bytes) from the same allocator
    int allocArgs2[] = { 0 };
    poolHeader = (undefined4*)(**(code**)**(undefined4**)(this + 0x39fc))(0x20, &allocArgs2);
    if (poolHeader == (undefined4*)0x0) {
        poolHeader = (undefined4*)0x0;
    } else {
        // Initialize the pool header
        poolHeader[4] = 4;                    // +0x10: block size? Or flags
        poolHeader[0] = (int)bufferPtr;       // +0x00: pointer to the buffer
        poolHeader[1] = 0x2400;               // +0x04: buffer size
        poolHeader[2] = 0;                    // +0x08: current free list head (will be set later)
        poolHeader[3] = 0x24;                 // +0x0C: block size in bytes (36)
        poolHeader[7] = 0;                    // +0x1C: available blocks
        poolHeader[6] = 0x100;                // +0x18: max blocks (256)
        poolHeader[5] = 0x100;                // +0x14: total blocks (256)

        // Initialize free list: each block is 9 ints (36 bytes), linked via first int
        freeListHead = 0;
        i = 0x100;  // 256 blocks
        do {
            node = bufferPtr;
            *node = (int)freeListHead;  // previous block's address (or use as next)
            i--;
            bufferPtr = node + 9;       // move to next block
            freeListHead = node;
        } while (i != 0);
        poolHeader[2] = (int)node;      // set free list head to the last block (or first?)
    }
    // Store the pool header
    *(undefined4**)(this + 0x3a00) = poolHeader;

    // Call final initialization (likely sets up vtable or finishes initialization)
    FUN_0042c4a0(this);

    return this;
}