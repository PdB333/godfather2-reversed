// FUNC_NAME: GhostManager::ResetGhostObjects
// Address: 0x004cb8a0
// Resets all ghost objects in the list, zeroing flags and incrementing generation counter.

void __thiscall GhostManager::ResetGhostObjects()
{
    int count = this->ghostCount; // +0x0c: number of ghost objects
    int i = 0;
    if (count > 0) {
        do {
            GhostObject* obj = this->ghostList[i]; // +0x14: array of object pointers (size 4 each)
            if (obj != nullptr && obj->validFlag != 0) { // +0x1fc: non-zero means object is active
                obj->resetFlag1 = 0; // +0x208: first reset flag
                obj->resetFlag2 = 0; // +0x209: second reset flag
                ResetObject(obj); // FUN_00650be0: clean up object internals
                obj->generation++; // +0x20c: increment generation counter
                NotifyStateChange(); // FUN_00650de0: update state manager
            }
            i++;
        } while (i < count);
    }
}