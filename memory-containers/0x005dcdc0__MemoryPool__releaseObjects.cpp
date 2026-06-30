// FUNC_NAME: MemoryPool::releaseObjects
void MemoryPool::releaseObjects()
{
    uint count;
    undefined4 *objPtr;
    int i;
    MemoryPool *pool;
    uint idx;

    pool = gMemoryManager; // DAT_01223508
    count = *(uint *)(this + 0x274); // number of objects in array
    idx = 0;
    if (count != 0) {
        do {
            objPtr = *(undefined4 **)(*(int *)(this + 0x270) + idx * 4); // get pointer from array
            if (objPtr != (undefined4 *)0x0) {
                *objPtr = *(undefined4 *)(pool + 0x44); // store old free list head
                *(int *)(pool + 0x20) = *(int *)(pool + 0x20) - 1; // decrease used count
                *(int *)(pool + 0x1c) = *(int *)(pool + 0x1c) + 1; // increase free count
                *(undefined4 **)(pool + 0x44) = objPtr; // push onto free list
            }
            idx = idx + 1;
        } while (idx < count);
    }
    *(undefined4 *)(this + 0x274) = 0; // clear count
    func_009c8f10(*(undefined4 *)(this + 0x270)); // free array memory
    *(undefined4 *)(this + 0x270) = 0; // null pointer
    *(undefined4 *)(this + 0x278) = 0; // probably capacity, also cleared

    if (*(int *)(this + 0x2a0) != 0) {
        (**(code **)(this + 0x2ac))(*(int *)(this + 0x2a0)); // call destructor on optional object
    }

    // Redundant check: this+0x270 is already 0, but preserved from original binary
    if (*(int *)(this + 0x270) != 0) {
        func_009c8f10(*(int *)(this + 0x270));
    }
    return;
}