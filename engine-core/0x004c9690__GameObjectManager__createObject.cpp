// FUNC_NAME: GameObjectManager::createObject
void GameObjectManager::createObject(uint param) {
    // Global singleton pointer to the game object manager (DAT_01223404)
    GameObjectManager* mgr = sGameObjectManager;
    if (!mgr) return;
    
    // Check required internal lists (offsets +0x10 and +0x14)
    if (!mgr->objectList || !mgr->someOtherList) {
        return;
    }
    
    // Allocate memory for a new game object (size 0x37c = 892 bytes)
    void* rawMemory = ::operator new(0x37c);
    if (!rawMemory) {
        rawMemory = nullptr;
    }
    
    // Construct the object if allocation succeeded
    GameObject* newObj = nullptr;
    if (rawMemory) {
        newObj = ::new (rawMemory) GameObject(param);
    }
    
    // Build an object handle pair: (pointer, objectID at offset +8)
    // The original code concatenates newObj and *(uint*)(newObj + 8) into a 64-bit value.
    ObjectPair pair;
    pair.ptr = newObj;
    pair.id = (newObj) ? *(uint*)((char*)newObj + 8) : 0;
    
    // Register the object with the scene manager
    // First arg: mgr->objectList (offset +0x10) - likely a container pointer
    // Second arg: output handle buffer (local_14, uninitialized; ignored here)
    // Third arg: pointer to the pair
    ObjectHandle outputHandle; // unused result buffer
    AddResult* result = mgr->registerObject(mgr->objectList, &outputHandle, &pair);
    
    // Read the result: first 8 bytes are the pair copy, next 4 bytes include a status byte
    ObjectPair resultPair = result->pair;
    char status = result->statusByte;
    
    if (status == '\0') {
        // Registration failed: destroy the newly created object
        if (newObj) {
            newObj->~GameObject();
            ::operator delete(newObj);
        }
    }
    // If successful, the object is now owned by the manager.
}