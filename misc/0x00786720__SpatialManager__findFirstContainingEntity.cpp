// FUNC_NAME: SpatialManager::findFirstContainingEntity
int __thiscall SpatialManager::findFirstContainingEntity(int this, float* point) {
    uint index = 0;
    int entityPtr = 0;
    
    // entityCount at +0x1a3c (uint)
    uint entityCount = *(uint*)(this + 0x1a3c);
    if (entityCount != 0) {
        // entityArray at +0x193c (array of pointers to entities)
        int* entityArray = (int*)(this + 0x193c);
        while (true) {
            entityPtr = *entityArray;
            // entity position at +0x10 (float3)
            float dx = *point - *(float*)(entityPtr + 0x10);
            float dy = point[1] - *(float*)(entityPtr + 0x14);
            float dz = point[2] - *(float*)(entityPtr + 0x18);
            // entity radius at +0x1c (float)
            float radiusSq = *(float*)(entityPtr + 0x1c) * *(float*)(entityPtr + 0x1c);
            if (radiusSq >= (dz * dz + dy * dy + dx * dx)) {
                // Point is inside this entity's sphere
                return entityPtr;
            }
            index++;
            entityArray++;
            if (index >= entityCount) {
                return 0;
            }
        }
    }
    return 0;
}