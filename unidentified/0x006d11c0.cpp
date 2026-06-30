// FUN_NAME: Navigation::getNeighborPositions
extern float stepSize; // DAT_00d5ef70

// Checks if the given position is reachable from source (e.g., within navmesh)
extern bool isPositionValid(const float* source, const float* candidate);

// Generates up to 5 candidate positions (original + four cardinal offsets) from source.
// Returns number of valid positions (including original).
// output array must hold at least 20 floats (5 * 4-component vectors).
int Navigation::getNeighborPositions(float* output, const float* source)
{
    // Copy source to first slot (original position)
    output[0] = source[0];
    output[1] = source[1];
    output[2] = source[2];
    output[3] = source[3];

    // Pre-populate next four slots with same values (will be modified)
    for (int i = 1; i < 5; i++)
    {
        output[i*4 + 0] = source[0];
        output[i*4 + 1] = source[1];
        output[i*4 + 2] = source[2];
        output[i*4 + 3] = source[3];
    }

    int validCount = 1; // original always valid

    // Try right (+x)
    output[4] = source[0] + stepSize; // slot 1 x
    if (isPositionValid(source, &output[4]))
    {
        validCount++;
    }

    // Now attempt left (-x) — if +x failed, reuse slot 1; otherwise use next slot
    output[validCount * 4] = source[0] - stepSize;
    if (isPositionValid(source, &output[validCount * 4]))
    {
        validCount++;
    }

    // Try forward (+z)
    output[validCount * 4 + 2] = source[2] + stepSize;
    if (isPositionValid(source, &output[validCount * 4]))
    {
        validCount++;
    }

    // Try backward (-z)
    output[validCount * 4 + 2] = source[2] - stepSize;
    if (isPositionValid(source, &output[validCount * 4]))
    {
        validCount++;
    }

    return validCount;
}