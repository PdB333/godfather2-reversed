// FUNC_NAME: SpatialManager::forEachEntityInSphere
// Function address: 0x005fcf80
// Iterates all entities in spatial hash, calls callback for those within sphere defined by position and radius.
// Uses a query object with virtual functions for begin/end and test.
// Global DAT_01223524 points to SpatialManager singleton.

void SpatialManager::forEachEntityInSphere(const float position[3], SpatialQuery* queryObj, float radius) {
    // Begin query, get initial data (e.g., cell index or context)
    int cellIndex = queryObj->vtable[2](); // offset +0x8: begin()
    SpatialManager* mgr = reinterpret_cast<SpatialManager*>(DAT_01223524);
    if (cellIndex == 0) {
        cellIndex = *(int*)((uint8_t*)mgr + 0x50); // fallback: some default index
    }

    // Get pointer to first element in the spatial list (linked list of cells/entities)
    SpatialNode** headPtr = reinterpret_cast<SpatialNode**>(*(uint32_t*)((uint8_t*)mgr + 0x28));
    SpatialNode* currentNode = *headPtr; // list head

    // Iterate over linked list
    while (true) {
        SpatialNode* listEnd = *reinterpret_cast<SpatialNode**>((uint8_t*)mgr + 0x28);
        if ((uint32_t)mgr == 0xFFFFFFF0) { // debug assertion for invalid manager
            debugAssert_FUN_00b97aea();
        }
        if (currentNode == listEnd) break;

        // Iterate within current node?
        // Actually each node holds a pointer to an entity at offset 8
        Entity* entity = reinterpret_cast<Entity*>(currentNode->entityPtr); // node->entity at +0x8
        if (entity != nullptr &&
            (*(int16_t*)((uint8_t*)entity + 0x3e) != 0) && // entity active flag
            queryObj->vtable[1](entity)) { // offset +0x4: test()
            // Get AABB (min/max) from entity at offset 0x48
            float* aabb = *reinterpret_cast<float**>((uint8_t*)entity + 0x48); // pointer to 6 floats
            float dx = 0.0f;
            if (position[0] < aabb[0])
                dx = position[0] - aabb[0];
            else if (position[0] > aabb[3])
                dx = position[0] - aabb[3];
            float dy = 0.0f;
            if (position[1] < aabb[1])
                dy = position[1] - aabb[1];
            else if (position[1] > aabb[4])
                dy = position[1] - aabb[4];
            float dz = 0.0f;
            if (position[2] < aabb[2])
                dz = position[2] - aabb[2];
            else if (position[2] > aabb[5])
                dz = position[2] - aabb[5];
            float distSq = dx*dx + dy*dy + dz*dz;
            if (distSq <= radius * radius) {
                // Callback: add entity to result set
                onEntityWithinRadius_FUN_005fcce0();
            }
        }

        // Move to next node in list
        if (currentNode == listEnd) {
            debugAssert_FUN_00b97aea();
        }
        currentNode = reinterpret_cast<SpatialNode*>(currentNode->next); // node->next at offset 0
    }

    // End query, get additional data
    void* endData = queryObj->vtable[3](); // offset +0xc: end()
    // Final processing with cellIndex and endData
    processQueryCompletion_FUN_006021f0(position, queryObj, cellIndex, radius, endData);
}