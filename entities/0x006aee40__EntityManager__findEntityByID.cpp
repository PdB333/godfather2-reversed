// FUNC_NAME: EntityManager::findEntityByID
bool EntityManager::findEntityByID(void* container, int targetId) {
    // global pointer to a hash table manager (likely EntityManager instance)
    EntityManager* manager = reinterpret_cast<EntityManager*>(DAT_0122337c);
    
    int iterData[18]; // iterator state (72 bytes)
    char found = 0;
    int local_98 = 0;
    
    // start iteration over the container (e.g., list of active entity handles)
    FUN_00405e40(iterData, container, 0);
    
    do {
        void* currentHandle = FUN_00405f20(iterData + 72); // some offset, likely current element handle
        bool valid = FUN_00405f90(currentHandle);
        if (!valid || found) {
            break;
        }
        
        uint hashKey = FUN_00405f40(); // get hash of current element
        
        // look up hash in global entity hash table
        uint bucketIndex = hashKey % manager->hashTableSize; // manager+0x54
        uint** bucketPtr = reinterpret_cast<uint**>(reinterpret_cast<uint*>(manager) + 0x50);
        uint* entry = bucketPtr[bucketIndex];
        
        while (entry != nullptr) {
            if (entry[0] == hashKey) { // hash match
                if (entry[1] != 0) {
                    // entry[1] points to an entity, offset 0x2c is the entity ID
                    int entityId = *(int*)(entry[1] + 0x2c);
                    local_98 = entityId;
                    goto check_id;
                }
                break;
            }
            entry = reinterpret_cast<uint*>(entry[2]); // next in chain
        }
        
        // hash not found – use sentinel value
        local_98 = -0x1e98fd1; // unlikely to match
        
check_id:
        if (local_98 == targetId) {
            found = 1;
        }
        
        // advance iterator to next element
        typedef void (*NextFunc)(int*);
        NextFunc next = *reinterpret_cast<NextFunc*>(iterData[0] + 4);
        next(iterData);
        
    } while (true);
    
    return found != 0;
}