// FUNC_NAME: BuildingManager::findNearestBuildingByTypeAndPosition
int __thiscall BuildingManager::findNearestBuildingByTypeAndPosition(BuildingManager* this, float* position, int buildingTypeId)
{
    int bestIndex = 0;
    int bestBuilding = 0;
    float bestDistSq = DAT_00d5f6f0; // global max distance threshold (float)

    int buildingCount = DAT_0112dac8; // number of buildings in global array
    int* buildingArray = DAT_0112da48; // array of pointers to Building objects

    if (buildingCount != 0) {
        for (int i = 0; i < buildingCount; i++) {
            int buildingPtr = buildingArray[i]; // Building* (offset 0x50 = typeId, 0x90 = posX, 0x94 = posY, 0x98 = posZ, 0xa8 = currentJob)

            // Check if building type matches
            if (*(int*)(buildingPtr + 0x50) == buildingTypeId) {
                // Check if building is not currently busy (job pointer is null or job is invalid or job is inactive)
                int jobPtr = *(int*)(buildingPtr + 0xa8);
                bool isAvailable = (jobPtr == 0) ||
                                   (FUN_006b0ee0(jobPtr) == 0) ||
                                   (FUN_006b48b0() == 0);
                if (isAvailable) {
                    // Compute squared distance from given position
                    float dx = position[0] - *(float*)(buildingPtr + 0x90);
                    float dy = position[1] - *(float*)(buildingPtr + 0x94);
                    float dz = position[2] - *(float*)(buildingPtr + 0x98);
                    float distSq = dy*dy + dx*dx + dz*dz;
                    if (distSq < bestDistSq) {
                        bestBuilding = buildingPtr;
                        bestDistSq = distSq;
                    }
                }
            }
        }
    }
    return bestBuilding; // returns the closest matching building pointer, or 0 if none found
}