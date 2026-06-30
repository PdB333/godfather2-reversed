// FUNC_NAME: TaskManager::processTasks
void TaskManager::processTasks() {
    // +0x0c: flags bitmask
    uint flags = *(uint *)(this + 0xc);

    // Check if bit 19 (0x80000) is not set
    if ((flags & 0x80000) == 0) {
        // Set bit 19 and clear bits 12-16? (0x7ff7ffff mask)
        *(uint *)(this + 0xc) = (flags & 0x7ff7ffff) | 0x80000;

        // Get count of task entries (+0x80 is a short)
        short count = *(short *)(this + 0x80);
        if (count > 0) {
            uint *currentEntry = (uint *)(this + 0xf0); // +0xf0: start of task array
            int index = 0;
            do {
                // Check if the owner object (+0x10) is null or the task's target is null
                // +0x10: owner object pointer
                // currentEntry[1]: target object pointer (second dword in entry)
                if (*(int *)(this + 0x10) == 0 || (int *)currentEntry[1] == nullptr) {
                    // Set bit 28 (0x10000000) on task flags
                    *currentEntry |= 0x10000000;
                } else {
                    // Call virtual function at vtable offset 0x1c on the target object
                    (*(void (__thiscall **)(void *))(*(int *)currentEntry[1] + 0x1c))();
                }

                // Always set bit 27 (0x8000000) on task flags
                *currentEntry |= 0x8000000;

                index++;
                currentEntry += 5; // Each task entry is 20 bytes (5 uint32)
            } while (index < count);
        }
    }
}