// FUNC_NAME: getMinimumDistanceToValidObject

// Function at 0x00941d80: Iterates through objects, checks a condition, computes a float (likely distance),
// returns the minimum value found, initialized to global INFINITY (DAT_00d5f6f0).
// param_2: likely an index or filter parameter passed to the condition and compute functions.
// Uses three global arrays (DAT_011305d0, DAT_011305e0, DAT_011305f0) that are passed to helper functions.

float getMinimumDistanceToValidObject(uint sourceIndex)
{
    // Global infinity value (likely a large float like FLT_MAX)
    float bestDistance = DAT_00d5f6f0;

    // Iterate while there are more objects
    while (hasMoreObjects())
    {
        // Check if the object meets a condition (e.g., valid target)
        if (checkObjectCondition(&DAT_011305d0, &DAT_011305e0, &DAT_011305f0, sourceIndex, 1))
        {
            // Compute a distance (or other float) for this object
            float distance = computeObjectDistance(&DAT_011305d0, &DAT_011305e0, &DAT_011305f0, sourceIndex);
            if (distance < bestDistance)
            {
                bestDistance = distance;
            }
        }
    }
    return bestDistance;
}