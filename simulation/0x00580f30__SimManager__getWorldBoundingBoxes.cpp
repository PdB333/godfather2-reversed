// FUNC_NAME: SimManager::getWorldBoundingBoxes
void SimManager::getWorldBoundingBoxes(float* outBounds, const SimManager* simMgr) {
    // outBounds: output array of 8 floats per entity (minX, minY, minZ, w=1, maxX, maxY, maxZ, w=1)
    // simMgr->count at +0x1c : number of child entities to process
    float tempBounds[8]; // temporary bounding box storage
    int count = *(int*)((char*)simMgr + 0x1c);
    for (int i = 0; i < count; i++) {
        // Initialize local bounds with zeros and set w components to constant (likely 1.0f)
        tempBounds[0] = 0.0f;
        tempBounds[1] = 0.0f;
        tempBounds[2] = 0.0f;
        tempBounds[3] = *(float*)0x00e2b1a4; // constant (e.g., 1.0f)
        tempBounds[4] = 0.0f;
        tempBounds[5] = 0.0f;
        tempBounds[6] = 0.0f;
        tempBounds[7] = *(float*)0x00e2b1a4; // constant
        // Compute the bounding box for the i-th entity (transform local bounds to world)
        FUN_00581220(tempBounds);
        // Copy result to output array
        for (int j = 0; j < 8; j++) {
            outBounds[i * 8 + j] = tempBounds[j];
        }
    }
    // Initialization call (likely resets some internal state)
    FUN_00581080();
}