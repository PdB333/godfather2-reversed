// FUNC_NAME: PoolAllocator::PoolAllocator
// Function address: 0x004401e0
// Constructor for a fixed-size object pool manager.
// Allocates a buffer of size (numBufferBlocks * 32) and creates an array of pool objects.

PoolAllocator * __thiscall PoolAllocator::PoolAllocator(
    PoolAllocator *this, uint numBufferBlocks, ushort numObjectsInit)
{
    ushort uVar1;
    bool bTempUsed = false;
    int iVar3;
    undefined4 uVar4;
    int blockIndex = 0;
    int *poolManagerPtr;
    int local_18; // temp result from poolManager function
    undefined4 local_14[3]; // temporary object for pool manager calls

    // Store this instance in a global for access
    gCurrentPool = this;

    // Set vtable pointers (two vtables - base and derived?)
    this->vtable1 = &VTABLE_BASE_00e31088;
    this->vtable2 = &VTABLE_DERIVED_00e3108c;
    this->field_8 = 0x1;
    this->field_12 = 0x0;
    this->numBufferBlocks = numBufferBlocks;

    // Reference count/logic for a global mutex or object
    if (gSomeMutex != 0) {
        gObjectCounter++;
        iVar3 = lockMutex(); // FUN_00407da0
        if (iVar3 == 0) {
            releaseMutex(&gSomeMutex, 0xffff); // FUN_004084d0
        } else {
            uVar1 = *(ushort *)(iVar3 + 0x14);
            *(ushort *)(iVar3 + 0x14) =
                (ushort)(((((uVar1 * 2) >> 1) + 1) ^ uVar1) & 0x7fff) ^ uVar1;
        }
    }

    // Possibly attach to a list or register
    if (gSomeList != 0) {
        addToList((int *)&this->vtable2, &gSomeList); // FUN_00407e60
    }

    // Allocate the main buffer: size = numBufferBlocks * 32
    this->buffer = (byte *)allocateMemory(numBufferBlocks << 5); // FUN_009c8e80

    // Allocate the pool manager structure (size 0x28 = 40 bytes)
    PoolManager *manager = (PoolManager *)allocateObject(0x28); // FUN_009c8e50
    if (manager != nullptr) {
        manager->vtable = &VTABLE_POOLMANAGER_00e30fc0;
        initBuffer(this->buffer, numBufferBlocks << 5, 0x20, 4); // FUN_004abe90
        manager->field_36 = 1;
        manager->field_32 = 0;
    }
    this->poolManager = manager;

    // Store number of initial objects (ushort)
    *(ushort *)(&this->numObjectsInit) = numObjectsInit;
    this->objectArray = (PoolObjectHandle *)allocateMemory(numObjectsInit * 4); // array of handles
    *(ushort *)((byte *)this + 0x16) = 0; // some additional field

    // Loop to create initial objects
    blockIndex = 0;
    if ((short)numObjectsInit > 0) {
        do {
            // Allocate a new pool object (size 0x20)
            iVar3 = (int)allocateObject(0x20); // FUN_009c8e50
            if (iVar3 != 0) {
                // Use the pool manager's vtable to add object to free list
                poolManagerPtr = (int *)this->poolManager;
                local_14[0] = 0;
                local_14[1] = 0;
                local_14[2] = 0;
                (**(code **)(*poolManagerPtr + 8))();  // virtual func vtable+8
                local_18 = produceResult(&local_14, poolManagerPtr); // FUN_004265d0
                bTempUsed = true;

                // Initialize the pool object (size 0x20) and get its handle
                uVar4 = createPoolObject(iVar3); // FUN_00440c70
            }
            // Store handle in object array
            this->objectArray[blockIndex] = uVar4;

            // Clean up temporary if used
            if (bTempUsed) {
                bTempUsed = false;
                if (local_18 != 0) {
                    (**(code **)(*poolManagerPtr + 4))(local_18, 0); // virtual func vtable+4
                    local_18 = 0;
                }
                (**(code **)(*poolManagerPtr + 0xc))(); // virtual func vtable+12
            }
            blockIndex++;
        } while (blockIndex < (short)numObjectsInit);
    }

    return this;
}