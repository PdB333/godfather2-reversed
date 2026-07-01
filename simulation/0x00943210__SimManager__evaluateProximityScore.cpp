// FUNC_NAME: SimManager::evaluateProximityScore
// Address: 0x00943210
// This method calculates a proximity/visibility score for the current entity (this) relative to a set of reference points
// Defined in SimManager, part of EA EARS engine (The Godfather 2)
// The score is the minimum of per-reference evaluations, with a default sentinel value (DAT_00d8b374) if none found

void SimManager::evaluateProximityScore(int thisPtr, uint flags, int referenceTransform, float* outScore, bool useAlternateCheck) {
    int iVar1;
    int listHeader;
    bool bFound;
    char cVar4;
    uint uIndex;
    int elementOffset;
    float fScore;
    float fVar8;
    float localPosX, localPosY, localPosZ; // from world-to-local conversion
    float diffX, diffY, diffZ;
    float local_a0[39]; // 156 bytes, likely a transform matrix

    // Retrieve world transform from this entity (likely position & orientation)
    getWorldTransform(thisPtr, local_a0);
    // Convert using referenceTransform into local coordinate system (outputs 3-vector)
    worldToLocal(local_a0, referenceTransform, &localPosX, &localPosY, &localPosZ);

    // If bit0 of flags is set, add an offset to the local Y component (heuristic bias)
    if ((flags & 1) != 0) {
        localPosY = localPosY + globalVerticalOffset; // DAT_00d8b270
    }

    // Access the list header at offset +0x90 from this
    listHeader = *(int*)(thisPtr + 0x90); // +0x90: pointer to reference list container
    int elementCount = *(int*)(listHeader + 0x34); // +0x34: number of elements
    int* elementArray = *(int**)(listHeader + 0x50); // +0x50: pointer to array of structures (size 0xB0 each)

    *outScore = defaultScore; // DAT_00d8b374, sentinel value
    bFound = false;

    if (elementCount != 0) {
        for (uIndex = 0; uIndex < elementCount; uIndex++) {
            elementOffset = uIndex * 0xB0;
            int* elementPtr = (int*)((int)elementArray + elementOffset);

            // Extract reference Y (vertical) difference, use it as initial score component
            float refY = *(float*)(*elementArray + 0x14 + elementOffset); // elementPtr[0x14] -> local reference Y
            float rawDiff = localPosY - refY;
            // Convert raw difference to absolute value (cast to uint then mask with 0x7FFFFFFF)
            float absDiff = (float)((uint)(rawDiff) & absoluteMask); // DAT_00e44680 = 0x7FFFFFFF
            fScore = maxVerticalDistance - absDiff; // DAT_00e44564 - absDiff

            if ((flags & 1) == 0) {
                // Standard distance check: compute 2D horizontal distance squared
                float refX = *(float*)(elementPtr + 0x10); // elementPtr[0x10]
                float refZ = *(float*)(elementPtr + 0x18); // elementPtr[0x18]
                diffX = localPosX - refX;
                diffY = localPosY - refY; // already have refY
                diffZ = localPosZ - refZ;
                float distSq = diffX * diffX + diffY * diffY + diffZ * diffZ;
                float radiusSq = *(float*)(elementPtr + 0x1c); // elementPtr[0x1c] -> squared radius

                if (distSq < radiusSq) {
                    goto insideRadius;
                }
            } else {
insideRadius:
                fScore = fScore + insideRadiusBonus; // DAT_00d61ae8

                if ((flags & 1) == 0) {
                    // Call additional processing for standard mode
                    processReference(*(int*)(elementPtr + 0x20)); // elementPtr[0x20] -> handle
                    cVar4 = checkVisibility(&localPosX, &localPosY, &localPosZ); // 3D point visibility test
                    if (cVar4 != 0) {
                        fScore = fScore + visibilityBonus; // DAT_00d61b40
                        bFound = true;
                    }
                } else {
                    // Alternative mode: use angle/distance evaluation functions
                    float fVar7;
                    if (useAlternateCheck == 0) {
                        fVar7 = evaluateAngleDistance_1(elementPtr, &localPosX, &localPosY, &localPosZ); // FUN_00941d80
                    } else {
                        fVar7 = evaluateAngleDistance_2(elementPtr, &localPosX, &localPosY, &localPosZ); // FUN_00941e40
                    }
                    if (fVar7 < angleDistanceThreshold) { // DAT_00d5f6f0
                        fScore = (insideRadiusBonus - fVar7) + fScore;
                        bFound = true;
                    }
                }
            }

            // Keep the minimum score across all references (sentinel defaults to large value)
            if (*outScore > fScore && fScore != *outScore) {
                *outScore = fScore;
            }
        }

        if (bFound) {
            return;
        }
    }

    // If no references found or none matched, return default sentinel
    *outScore = defaultScore;
    return; // no explicit return in decompiled, but flow implies
}