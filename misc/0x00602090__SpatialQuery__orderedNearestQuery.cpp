// FUNC_NAME: SpatialQuery::orderedNearestQuery
// Address: 0x00602090
// This function iterates through an array of points (9 floats each) in order of increasing distance
// from a query point, invoking a callback for each point found within a distance threshold.
// The threshold is given as a float value (condition parameter as a float pointer).
void SpatialQuery::orderedNearestQuery(float *queryData, int *callback, float *threshold)
{
    // Virtual call on condition object at offset 4 to check if query may proceed
    bool proceed = (*(bool (__thiscall **)(float *))(*(void **)threshold + 4))(queryData);
    if (!proceed)
        return;

    uint16_t pointCount = *(uint16_t *)(queryData + 3); // Number of points in the array
    float *queryPos = queryData;                         // Query point (x at +0, y at +1, z at +2)
    float *pointsArray = *(float **)(queryData + 8);     // Pointer to array of 9-float points

    float lastDist = 0.0f; // Distance of the last reported point
    int lastIndex = -1;     // Index of the last reported point
    uint16_t found = 0;     // Counter of reported points

    do {
        if (!proceed)
            return;

        int bestIndex = -1;
        float bestDist = DAT_00e2e50c; // Large initial value ( ~3.4e38 )

        // Find the next nearest point that hasn't been reported
        for (uint16_t i = 0; i < pointCount; i++)
        {
            float *pt = pointsArray + i * 9; // Each point has 9 floats (position, normal, etc.)
            float dx = pt[1] - queryPos[1];
            float dy = pt[0] - queryPos[0];
            float dz = pt[2] - queryPos[2];
            float distSq = dx * dx + dy * dy + dz * dz;

            if (distSq <= lastDist)
            {
                // If distance equals last reported distance, only consider if index is greater
                if (distSq == lastDist && lastIndex < i)
                {
                    bestIndex = i;
                    bestDist = distSq;
                }
            }
            else if (distSq < bestDist)
            {
                bestIndex = i;
                bestDist = distSq;
            }
        }

        // Compare against threshold (dereference threshold pointer)
        float thresholdVal = *threshold;
        if (bestDist <= thresholdVal)
        {
            // Call result callback's first virtual function
            proceed = (*(bool (__thiscall **)(float *, float *, float *))(*(void **)callback))(callback, pointsArray + bestIndex * 9, queryData);
            lastDist = bestDist;
            lastIndex = bestIndex;
            found++;
        }
        else
        {
            proceed = false; // Stop because distance exceeds threshold
        }
    } while (found < pointCount);
}