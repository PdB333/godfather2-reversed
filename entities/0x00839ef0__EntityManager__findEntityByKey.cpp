// FUNC_NAME: EntityManager::findEntityByKey
uint __thiscall EntityManager::findEntityByKey(int *key, int *outEntity) {
    uint result = 0; // default failure (in_EAX & 0xffffff00 assumed 0)
    uint count = *(uint *)(this + 0x14); // number of entities in array
    if (count != 0) {
        int **array = *(int ***)(this + 0x10); // pointer to array of entity pointers
        for (uint i = 0; i < count; i++) {
            int *entity = array[i];
            // Compare four 32-bit fields at offsets 0x11c, 0x120, 0x124, 0x128
            // These likely form a unique identifier (e.g., GUID or hash)
            if (*(int *)(entity + 0x11c) == key[0] &&
                *(uint *)(entity + 0x120) == key[1] &&
                *(uint *)(entity + 0x124) == key[2] &&
                *(uint *)(entity + 0x128) == key[3]) {
                *outEntity = (int)entity; // store found entity pointer
                // Return the last field with low byte set to 1 (success indicator)
                return (*(uint *)(entity + 0x128) & 0xFFFFFF00) | 1;
            }
        }
    }
    return result; // 0 on failure
}