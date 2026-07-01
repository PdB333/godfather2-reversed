// FUNC_NAME: EntityManager::findClosestEntity
// Address: 0x0088dbf0
// Role: Finds the nearest entity from a list to a given position, using a filter.
// The function iterates over entities (count at this+0x148) and calls a helper
// to retrieve each candidate. It computes squared distance to the candidate's
// position (stored in a sub-structure at entity+0x14, with floats at +0x14, +0x18, +0x1c)
// and returns the index of the closest match, or 0 if none.

int __thiscall EntityManager::findClosestEntity(int this, int filterType, float* position)
{
    int closestIndex = 0;
    byte loopCounter = 0;
    float closestDistSq = 0.0f;

    int entityCount = *(int*)(this + 0x148); // +0x148: number of entities in list
    if (entityCount != 0) {
        do {
            // Retrieve a candidate entity pointer based on filter and position.
            // Note: The loop counter is not passed; the helper may use internal state.
            int entityPtr = getEntityByFilter(filterType, position);
            if (entityPtr != 0) {
                // entityPtr+0x14 points to a sub-structure containing position data
                int posStruct = *(int*)(entityPtr + 0x14);
                float dx = position[0] - *(float*)(posStruct + 0x14); // +0x14: x
                float dz = position[2] - *(float*)(posStruct + 0x1c); // +0x1c: z (note: z is at +0x1c, y at +0x18)
                float dy = position[1] - *(float*)(posStruct + 0x18); // +0x18: y
                float distSq = dx*dx + dz*dz + dy*dy;
                if (closestIndex == 0 || distSq < closestDistSq) {
                    closestIndex = entityPtr;
                    closestDistSq = distSq;
                }
            }
            loopCounter = loopCounter + 1;
        } while ((uint)loopCounter < (uint)entityCount);
    }
    return closestIndex;
}