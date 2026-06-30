// FUNC_NAME: generateCandidatePositions
int generateCandidatePositions(float* outCandidates, const float* inCenter)
{
    float x = inCenter[0];
    float y = inCenter[1];
    float z = inCenter[2];
    float w = inCenter[3]; // w component, likely unused but preserved

    // Copy the center position as the first candidate (index 0)
    outCandidates[0] = x;
    outCandidates[1] = y;
    outCandidates[2] = z;
    outCandidates[3] = w;

    // Pre-fill all 5 candidate slots with the center position
    for (int i = 1; i < 5; ++i)
    {
        int base = i * 4;
        outCandidates[base + 0] = x;
        outCandidates[base + 1] = y;
        outCandidates[base + 2] = z;
        outCandidates[base + 3] = w;
    }

    // Spacing between candidate positions
    const float spacing = DAT_00d5ef70;

    int validCount = 1; // Center is always valid

    // Candidate 1: right (x + spacing)
    outCandidates[4] = x + spacing;
    if (FUN_006d0ee0(inCenter, &outCandidates[4], 0))
    {
        validCount = 2;
    }

    // Candidate 2: left (x - spacing)
    outCandidates[validCount * 4] = x - spacing;
    if (FUN_006d0ee0(inCenter, &outCandidates[validCount * 4], 0))
    {
        validCount++;
    }

    // Candidate 3: forward (y + spacing)
    outCandidates[validCount * 4 + 2] = y + spacing;
    if (FUN_006d0ee0(inCenter, &outCandidates[validCount * 4], 0))
    {
        validCount++;
    }

    // Candidate 4: backward (y - spacing)
    outCandidates[validCount * 4 + 2] = y - spacing;
    if (FUN_006d0ee0(inCenter, &outCandidates[validCount * 4], 0))
    {
        validCount++;
    }

    return validCount;
}