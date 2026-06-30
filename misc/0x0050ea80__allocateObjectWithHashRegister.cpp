// FUNC_NAME: allocateObjectWithHashRegister
void allocateObjectWithHashRegister(uint id, uint flags, int parentObj, uint param4, uint param5, uint param6)
{
    short count = (short)(flags >> 16);
    uint allocSize = (count * 8 + 0x8f) & 0xfffffff0;
    if (*(char *)(parentObj + 0x154) == 0x06) {
        allocSize += count * 0x20;
    }

    void* allocator = reinterpret_cast<void*>(FUN_009c8f80()); // GetMemoryManager singleton
    uint allocParams[3] = {2, 0x10, 0}; // allocation flags / alignment

    // vtable call: (*(void*(__thiscall**)(void*,uint,uint*))(*allocator))(allocator, allocSize, allocParams)
    void* allocation = (**(code**)*allocator)(allocSize, &allocParams);
    if (allocation == 0) {
        allocSize = 0;
    } else {
        allocSize = FUN_0050e790(param5, param6); // returns pointer to object memory
    }

    uint* object = reinterpret_cast<uint*>(allocSize);

    // Zero out array at object + 0x80 (pairs of uint32)
    uint* arrayA = object + 0x20; // 0x80 / 4 = 0x20
    for (int i = 0; i < count; i++) {
        arrayA[i * 2] = 0;
        arrayA[i * 2 + 1] = 0;
    }

    // Type check in high byte of id (as passed in ESI register)
    if ((id >> 24) == 0x06) {
        int* extraArray = reinterpret_cast<int*>(object + 0x15); // +0x54 / 4 = 0x15
        *extraArray = reinterpret_cast<int>(allocation) + unaff_EBX; // unaff_EBX is unknown register value
        for (int i = 0; i < count * 8; i++) {
            *(*extraArray + i) = 0;
        }
    }

    // Global hash table at DAT_01223398 + 8
    int* hashTable = *(int**)(DAT_01223398 + 8);
    uint hashIndex = id % *(hashTable + 2); // +0x08
    if (*(char*)(hashTable + 6) != 0 && *(hashTable + 4) >= *(hashTable + 2) * 2) {
        FUN_00423fa0(); // rehash / grow table
        hashIndex = id % *(hashTable + 2);
    }

    uint* hashNode = reinterpret_cast<uint*>(FUN_00423f20()); // allocate node
    hashNode[1] = reinterpret_cast<uint>(object);
    hashNode[0] = id;
    hashNode[2] = *(uint*)(*(hashTable + 1) + hashIndex * 4);
    *(uint**)(*(hashTable + 1) + hashIndex * 4) = hashNode;
}