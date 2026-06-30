// FUNC_NAME: EntityManager::releaseAll
void __thiscall EntityManager::releaseAll(void)
{
    // Offset +0x210: pointer to an array of object pointers (size 0x1000 bytes, 1024 slots)
    int *objectArray = *(int **)((int)this + 0x210);

    if (objectArray != nullptr) {
        for (int i = 0; i < 0x1000; i += 4) {   // iterate over each 4-byte pointer slot
            int *obj = *(int **)((int)objectArray + i);
            if (obj != nullptr) {
                // Call virtual method at vtable offset 0x14 (e.g., "release" or "onDestroy")
                (**(code **)(*obj + 0x14))();

                // Delete object via virtual destructor at vtable+4 (deleting destructor)
                (**(code **)(*obj + 4))(1);

                // Clear the slot
                *(int *)((int)objectArray + i) = 0;
            }
        }
    }
}