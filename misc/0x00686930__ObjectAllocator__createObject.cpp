// FUNC_NAME: ObjectAllocator::createObject
uint32 ObjectAllocator::createObject(uint32 param_1, uint32 param_2) {
    uint32 local_c = 2;        // heapID
    uint32 local_8 = 0x10;     // alignment
    uint32 local_4 = 0;        // flags
    // Allocate 576 bytes (0x240) using the descriptor (heapID, alignment, flags) and context param_2
    int iVar1 = allocateMemory(0x240, &local_c, param_2);
    if (iVar1 != 0) {
        // Initialize the object with param_1
        uint32 uVar2 = initializeObject(param_1);
        return uVar2;
    }
    return 0;
}