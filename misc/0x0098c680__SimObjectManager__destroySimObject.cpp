// FUNC_NAME: SimObjectManager::destroySimObject
void __thiscall SimObjectManager::destroySimObject(void* pObject)
{
    uint currentIndex;         // uVar1
    uint newIndex;             // uVar3
    int* pFreedObject;         // iVar2
    PoolCallback callback;     // local_10[0] and local_4 combined as struct
    // callback.arg (local_10[0]) and callback.func (local_4)

    // Call destructors on the object being freed
    someBaseClassDestructor(pObject);           // FUN_004d3bc0
    anotherDestructor();                        // FUN_004d5570 (static cleanup?)

    currentIndex = *(uint *)(this + 0x244);     // Current free slot / next free index

    // Find or prepare the slot to free; returns new index and fills callback struct
    newIndex = findFreeSlotAndCallback(*(void **)(this + 0x240), currentIndex, &callback); // FUN_0098b000

    if (newIndex != currentIndex) {
        // If the new free slot is far enough, move data (likely coalesce free list)
        if (newIndex + 0x10 < currentIndex) {
            moveMemory((void *)(newIndex + 0x10), (void *)currentIndex, newIndex); // FUN_0098b2f0
        }

        // Update the free slot count (decrement by 0x10 = one object size)
        *(int *)(this + 0x244) = *(int *)(this + 0x244) - 0x10;

        // Dereference the pointer at the new free slot location
        pFreedObject = **(int **)(this + 0x244);
        if (pFreedObject != NULL) {
            // Call a member function (possibly destructor or release) via vtable at index 3
            (*(void (__thiscall **)(void *))(*(int **)(this + 0x244)[3]))(pFreedObject);
        }
    }

    // If a callback was registered, invoke it
    if (callback.arg != NULL) {
        callback.func(callback.arg);
    }
}