// FUNC_NAME: findEntityInRange
// Address: 0x0074d690
// Role: Searches entity type list for an object within distance thresholds from a reference position.
// Uses EARS engine entity list structure: each node has flags at offset 0, next at offset 4.
// Entity position: x at +0x30, y at +0x34, z at +0x38.
// Returns a handle: lower byte = 1 if found, else 0; upper bytes = shifted list head pointer.

uint __fastcall findEntityInRange(float verticalThreshold, float radiusSquared, float* referencePos)
{
    // Get the list head for entity type 10 (e.g., character or vehicle)
    float* listHeadPtr = (float*)GetEntityTypeList(10);
    int currentNode = (int)*listHeadPtr;  // first node pointer

    while (currentNode != 0)
    {
        // Check if node's flags indicate an active entity
        if (*(int*)currentNode != 0)
        {
            int entityPtr = GetEntityFromNode(currentNode);
            float* entityPos = (float*)(entityPtr + 0x30); // x at +0x30, y at +0x34, z at +0x38

            // Compute absolute vertical difference (y-axis) using sign bit mask
            float rawYDiff = entityPos[1] - referencePos[1]; // y difference
            uint absYDiff = (uint)rawYDiff & 0x7FFFFFFF; // mask sign bit (DAT_00e44680 = 0x7FFFFFFF)
            if ((float)absYDiff < verticalThreshold)
            {
                // Compute squared planar distance (xz-plane)
                float dx = referencePos[0] - entityPos[0];
                float dz = referencePos[2] - entityPos[2];
                float dy = referencePos[1] - entityPos[1]; // already had, but computed again for squared total
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq <= radiusSquared)
                {
                    // Found: encode list pointer as handle with low byte = 1 (found flag)
                    return ((uint)listHeadPtr >> 8) | 1;
                }
            }
        }
        currentNode = *(int*)(currentNode + 4); // next node pointer
    }

    // Not found: return list head pointer with low byte cleared
    return (uint)listHeadPtr & 0xFFFFFF00;
}