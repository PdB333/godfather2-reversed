// FUNC_NAME: EntityManager::addObject
void __thiscall EntityManager::addObject(EntityManager* this, void* obj) {
    uint count = this->m_objectCount;
    uint i = 0;
    if (count != 0) {
        int** entries = this->m_objects;
        do {
            if (*entries == obj) goto found;
            i++;
            entries += 3; // Each entry is 3 ints: [object*, backPtr, flags]
        } while (i < count);
    }
    // Not found – allocate or get a new slot
    int newIndex = (count == 0) ? 0 : count - 1;
    int* slot = this->getSlot(newIndex); // FUN_0071b300 returns pointer to entry at index
    slot[2] = g_globalFlags; // DAT_01205228 – some global state
    if (*slot != obj) {
        if (*slot != 0) {
            this->releaseObject(*slot); // FUN_004daf90 – release old object
        }
        *slot = obj;
        if (obj != 0) {
            slot[1] = *(int*)((char*)obj + 4); // back‑link, assume object has +4 pointer field
            *(int**)((char*)obj + 4) = slot;   // point object back to this entry
        }
    }
found:
    // If obj is the current object, release it and clear current
    if (this->m_current == obj && obj != 0) {
        this->releaseObject(obj);
        this->m_current = 0;
    }
}