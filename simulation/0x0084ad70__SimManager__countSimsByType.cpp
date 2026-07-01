// FUNC_NAME: SimManager::countSimsByType
int __thiscall SimManager::countSimsByType() {
    int count = 0;
    unsigned int numSims = *(unsigned int*)(this + 0xC); // +0x0C: number of sims in the list
    if (numSims != 0) {
        // Array of Sim* starts at +0x10 (assumed based on typical manager structure)
        Sim** simList = reinterpret_cast<Sim**>(this + 0x10);
        for (unsigned int i = 0; i < numSims; ++i) {
            Sim* sim = simList[i];
            int typeId = sim->getTypeID(); // Calls FUN_0084a410: returns type identifier
            if (typeId == 0x637b907) { // Hardcoded desired type ID (likely an NPC or entity type)
                ++count;
            }
        }
    }
    return count;
}