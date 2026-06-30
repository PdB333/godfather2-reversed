// FUNC_NAME: ObjectPoolManager::registerObject
void ObjectPoolManager::registerObject(void* object, uint32_t param2) {
    if (object != nullptr && poolBase != nullptr) {
        if (callbackVtable != nullptr) {
            char result = checkCallbackCondition(); // FUN_00514300, returns 0 if condition false
            if (result == 0) {
                // Call virtual function at vtable offset 8: likely onObjectAdd(object, param2)
                (*(void (**)(void*, uint32_t))(*(uint32_t*)callbackVtable + 8))(object, param2);
                return;
            }
        }
        // Get thread-local storage pointer (TEB->TLS array, then data at offset 8)
        // This yields a constant offset used to store the index within the object
        uint32_t* tlsBase = *(uint32_t**)__readfsdword(0x2c);  // TEB at FS:0, +0x2c gives TLS ptr
        uint32_t indexOffset = *(uint32_t*)((uint32_t)tlsBase + 8); // offset in object to write index
        // Store the current index into the object at the per-thread offset
        *(uint32_t*)((uint32_t)object + indexOffset) = currentIndex;
        // Compute the object's index relative to the pool base (each element is 0x2a0 bytes)
        uint32_t baseAddr = (uint32_t)poolBase;
        uint32_t objAddr  = (uint32_t)object;
        uint32_t index = (objAddr - baseAddr) / 0x2a0; // 0x2a0 = 672 bytes per structure
        // Update pool state
        usedCount++;                     // +0x18 (in_EAX[6])
        currentIndex = index;            // +0x14 (in_EAX[5])
    }
}