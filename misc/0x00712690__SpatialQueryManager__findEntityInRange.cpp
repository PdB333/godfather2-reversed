// FUNC_NAME: SpatialQueryManager::findEntityInRange
uint SpatialQueryManager::findEntityInRange(float* queryPoint) {
    float* listHandle = (float*)FUN_0043c2c0(10); // Get entity list handle
    int* currentNode = (int*)*listHandle; // First node in linked list
    if (currentNode == nullptr) {
        return (uint)listHandle & 0xffffff00; // No list, return failure
    }
    do {
        if (currentNode[0] != 0) { // Active flag at offset 0
            int entityBase = FUN_00471610(); // Get current entity base pointer
            // Entity position at offsets 0x30 (x), 0x34 (y), 0x38 (z)
            float* entityPos = (float*)(entityBase + 0x30);
            // Temporal check: absolute difference in y (used as time?) masked with sign bit
            float yDelta = *(float*)(entityBase + 0x34) - queryPoint[1];
            uint absDelta = (uint)yDelta & DAT_00e44680; // Mask for absolute value (0x7FFFFFFF)
            if (absDelta < DAT_00d61964) { // Time tolerance
                float dx = queryPoint[0] - *entityPos;
                float dy = queryPoint[1] - *(float*)(entityBase + 0x34);
                float dz = queryPoint[2] - *(float*)(entityBase + 0x38);
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq <= DAT_00d61960) { // Distance squared threshold
                    // Success: set low byte of listHandle to 1 and return
                    return ((uint)listHandle & 0xffffff00) | 1;
                }
            }
        }
        currentNode = (int*)currentNode[1]; // Next node at offset 4
    } while (currentNode != nullptr);
    // No entity found, return listHandle with low byte zero
    return (uint)listHandle & 0xffffff00;
}