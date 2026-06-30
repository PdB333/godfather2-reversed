// FUNC_NAME: EARSObject::~EARSObject
void* __thiscall EARSObject::destructor(byte deletionFlag) {
    // Set vtable to destruction vtable (0x00e37110)
    this->vtable = (void**)&PTR_FUN_00e37110;

    int* listNode = *(int**)(this + 0x10); // +0x10: list node pointer (for free list)
    if (listNode != 0) {
        // Push node onto EA EARS free list stack (global +0x14 holds free list head)
        int** freeListHead = (int**)(g_memoryManager + 0x14); // global base +0x14 is pointer to free list head
        *freeListHead = &PTR_LAB_01123be8;                 // sentinel marking end of free list
        freeListHead = freeListHead + 4;                    // advance to next slot
        *freeListHead = (int*)listNode;                     // store node pointer
        *(int*)(this + 0x10) = 0;                          // clear node pointer
        *(int*)(this + 0x14) = 0;                          // clear previous node pointer (offset +0x14)
    }

    // If deletion flag is set, call operator delete (FUN_009c8eb0)
    if (deletionFlag & 1) {
        operatorDelete(this);
    }

    return this;
}