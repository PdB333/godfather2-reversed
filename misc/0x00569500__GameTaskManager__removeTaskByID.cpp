// FUNC_NAME: GameTaskManager::removeTaskByID
void __fastcall GameTaskManager::removeTaskByID(void* this, int taskID)
{
    int* taskPtrArray = (int*)this + 2; // offset +2: array of task pointers (int*)
    uint taskCount = *(uint*)((char*)this + 0x1C); // offset +7? Actually offset in dwords: unaff_ESI[7] => +0x1C
    uint index = 0;

    if (taskCount != 0) {
        // Search for the task with matching ID
        while (taskPtrArray[index] != taskID) {
            index++;
            if (index >= taskCount) {
                return;
            }
        }

        // Special handling when only one task remains
        if (taskCount == 1) {
            // Virtual call at vtable+8 (likely bool canRemove())
            bool (*canRemove)(void*) = (bool(*)(void*))(*(void***)this)[2];
            if (!canRemove(this)) {
                // Virtual call at vtable+0x10 (likely void removeSelf())
                void (*removeSelf)(void*) = (void(*)(void*))(*(void***)this)[4];
                removeSelf(this);

                // Global lock/unlock or queue maintenance
                FUN_00ab4db0(&DAT_00e2cbe8); // possibly critical section enter

                // Process additional array at +0x8a (size at +0xca)
                uint childCount = *(uint*)((char*)this + 0x328); // offset +0xca in bytes
                if (childCount != 0) {
                    int* childArray = (int*)((char*)this + 0x228); // offset +0x8a in bytes
                    for (uint i = 0; i < childCount; i++) {
                        // Virtual call at vtable+0x40 (likely void cleanupChild(void*))
                        void (*cleanupChild)(void*) = (void(*)(void*))(*(void***)this)[16];
                        cleanupChild((void*)childArray[i]);
                    }
                }

                FUN_00ab4e70(); // possibly critical section leave
            }
        }

        // Remove the element by shifting the array
        uint currentCount = *(uint*)((char*)this + 0x1C); // reload count after possible change
        if (index < currentCount) {
            if (index < currentCount - 1) {
                taskPtrArray[index] = taskPtrArray[currentCount - 1]; // shift last element into gap
            }
            *(uint*)((char*)this + 0x1C) = currentCount - 1; // decrement count
        }
    }
}