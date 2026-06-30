// FUNC_NAME: EntityManager::findMatchingEntity
int __thiscall EntityManager::findMatchingEntity(EntityManager* this, Iterator* iter) {
    int result = 0;
    int candidateObj;

    // Dereference iterator to get current list node pointer (at +4)
    // If null, no more elements
    if (*(int*)(iter + 4) == 0) {
        candidateObj = 0;
    } else {
        // Intrusive list: the node is embedded at offset 0x48 from the containing object
        candidateObj = *(int*)(iter + 4) - 0x48;
    }

    // Compare four unique identifiers from this entity with those of the candidate
    // Offsets in 'this': +0x60, +0x64 (+100d), +0x68, +0x6c
    // Offsets in candidate: +0x20, +0x24, +0x28, +0x2c
    if (candidateObj != 0 &&
        *(int*)(this + 0x60) == *(int*)(candidateObj + 0x20) &&
        *(int*)(this + 0x64) == *(int*)(candidateObj + 0x24) &&
        *(int*)(this + 0x68) == *(int*)(candidateObj + 0x28) &&
        *(int*)(this + 0x6c) == *(int*)(candidateObj + 0x2c)) {
        result = candidateObj;
    }

    return result;
}