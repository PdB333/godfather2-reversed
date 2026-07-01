// FUNC_NAME: SimManager::updateAllSims
// Address: 0x0088d640
// Role: Iterates over a list of sim objects (count at +0x148) and processes each via processOneSim(),
//       then finalizes with a global update/tick call (processManagerTick).

void __thiscall SimManager::updateAllSims(SimManager* this) {
    byte counter = 0; // byte counter, max 255 iterations (count likely small)
    int count = *(int*)((uintptr_t)this + 0x148); // +0x148: number of active sims to process

    if (count != 0) {
        do {
            this->processOneSim(); // calls FUN_0088b870 - processes each sim object
            counter = counter + 1;
        } while ((uint32_t)counter < (uint32_t)count);
    }

    this->processManagerTick(); // calls FUN_00429480 - final per-frame manager update
}