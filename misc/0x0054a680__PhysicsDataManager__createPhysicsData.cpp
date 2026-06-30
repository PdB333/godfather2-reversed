// FUNC_NAME: PhysicsDataManager::createPhysicsData
/**
 * Address: 0x0054a680
 * Role: Creates a physics data wrapper object from either an existing physics data blob (param_2==0) or from a Havok root level container (param_2==1).
 * The function checks the pointer in EAX for a magic signature (0x57e0e057, 0x10c0c010) before proceeding.
 * Returns a pointer to a newly allocated wrapper object, or null on failure.
 */
PhysicsData* PhysicsDataManager::createPhysicsData(void* dataBlob, int mode) {
    // EAX holds a pointer to a structure that must contain the magic markers.
    int* signaturePtr = (int*)dataBlob;
    
    uint local_48[4]; // 0x40 bytes buffer, filled with 0xFF then pattern
    memset(local_48, 0xFF, 0x40);
    local_48[0] = 0x57e0e057;
    local_48[1] = 0x10c0c010;
    local_48[3] = 0; // ensure last word zero
    
    // Validate signature
    if (signaturePtr[0] != 0x57e0e057 || signaturePtr[1] != 0x10c0c010) {
        return nullptr;
    }
    
    // Lock Havok system
    havokLock();
    
    // Setup internal state using the validated pointer and the first explicit parameter
    validateAndSetPointer(signaturePtr, param1);
    
    if (mode == 0) {
        // Mode 0: Build from an existing physics world or data blob
        void* world = getPhysicsWorld();
        HavokContainer* container = havokFindObject(world);
        // Callback at offset 0x2c in global vtable (g_physicsCallbacks)
        int callbackResult = (*(int (**)())(g_physicsCallbacks + 0x2c))();
        
        int count = *(int*)(container + 0x0C);
        if (count > 0) {
            int* materialArray = *(int**)(container + 0x44);
            for (int i = 0; i < count; i++) {
                void* entry = *(void**)(container + 0x08);
                void* physicsProperty = *(void**)((int)entry + 0x70);
                int materialId = getMaterialIdFromPhysicsProperty(physicsProperty);
                materialArray[i] = materialId;
            }
        }
        
        // Allocate 12-byte wrapper object
        PhysicsData* data = (PhysicsData*)operatorNew(0x0C);
        if (data != nullptr) {
            data->vtable = &PTR_FUN_00e39c30; // vtable pointer
            data->field_4 = callbackResult;   // reference to callback or manager
            data->field_8 = container;        // Havok container
            
            // Check reference count at offset +4 in the callback object
            short* refCount = (short*)(callbackResult + 4);
            if (*refCount != 0) {
                *(short*)(callbackResult + 6) += 1; // increment sub-counter
            }
        }
        
        havokCleanup();
        return data;
    }
    else if (mode == 1) {
        // Mode 1: Build from a Havok root level container (e.g., hkx file)
        HavokContainer* rootContainer = havokFindObject("hkRootLevelContainer");
        int physicsData = havokFindComponent(rootContainer, "hkpPhysicsData", 0);
        if (physicsData != 0 && *(int*)(physicsData + 0x10) > 0) {
            int materialArray = havokFindComponent(rootContainer, "EAMaterialArray", 0);
            // Callback at offset 0x2c
            (*(void (**)())(g_physicsCallbacks + 0x2c))();
            
            // Allocate 16-byte wrapper object
            void* allocation = operatorNew(0x10);
            if (allocation != nullptr) {
                PhysicsData* data = constructPhysicsDataWithMaterials(allocation, materialArray);
                havokCleanup();
                return data;
            }
        }
    }
    
    havokCleanup();
    return nullptr;
}