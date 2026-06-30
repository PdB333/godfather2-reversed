// FUNC_NAME: searchEntitiesInBounds
float searchEntitiesInBounds(float* searchBounds)
{
    // Constants from global memory
    float g_regionTweak = *(float*)0x00e3ac54; // global tweak for bounds expansion
    float* g_entityBase = (float*)0x012053cc;  // base pointer to entity array
    float g_initialBestScore = *(float*)0x00e2e50c; // starting score threshold

    float fOffset = searchBounds[3] - g_regionTweak;
    float bestReturnValue = 0.0f;
    float* pfIterator = g_entityBase + 0x68; // +0x68 in bytes? Actually 0x68 floats? but dereferenced as float* so it's +0x68*4 bytes
    int loop = 32; // 0x20 iterations
    float currentBestScore = g_initialBestScore;

    do {
        // --- Block 1: subobject at offsets -0x28 .. -0x44 from pfIterator (roughly) ---
        // checks: ID != 0, AABB test, and score
        if ( (pfIterator[-10] != 0.0f) &&
             (pfIterator[-0x1a] + fOffset < searchBounds[0]) && (searchBounds[0] < pfIterator[-0x16] - fOffset) &&
             (pfIterator[-0x19] + fOffset < searchBounds[1]) && (searchBounds[1] < pfIterator[-0x15] - fOffset) &&
             (pfIterator[-0x18] + fOffset < searchBounds[2]) && (searchBounds[2] < pfIterator[-0x14] - fOffset) &&
             (pfIterator[-0x12] < currentBestScore) )
        {
            bestReturnValue = pfIterator[-10];
            currentBestScore = pfIterator[-0x12];
        }

        // --- Block 2: subobject at offsets +0x00 .. +0x18 ---
        // Note: some offsets are reused from previous block but shifted by +0x18 floats
        if ( (pfIterator[0xe] != 0.0f) &&
             (pfIterator[-2] + fOffset < searchBounds[0]) && (searchBounds[0] < pfIterator[2] - fOffset) &&
             (pfIterator[-1] + fOffset < searchBounds[1]) && (searchBounds[1] < pfIterator[3] - fOffset) &&
             (pfIterator[0] + fOffset < searchBounds[2]) && (searchBounds[2] < pfIterator[4] - fOffset) &&
             (pfIterator[6] < currentBestScore) )
        {
            bestReturnValue = pfIterator[0xe];
            currentBestScore = pfIterator[6];
        }

        // --- Block 3: subobject at offsets +0x58 .. +0x78 (0x26*4 = 0x98? careful) ---
        // offsets are +0x16, +0x18, +0x17 for min; +0x1a, +0x1c, +0x1b for max; +0x1e for score; +0x26 for value
        if ( (pfIterator[0x26] != 0.0f) &&
             (pfIterator[0x16] + fOffset < searchBounds[0]) && (searchBounds[0] < pfIterator[0x1a] - fOffset) &&
             (pfIterator[0x17] + fOffset < searchBounds[1]) && (searchBounds[1] < pfIterator[0x1b] - fOffset) &&
             (pfIterator[0x18] + fOffset < searchBounds[2]) && (searchBounds[2] < pfIterator[0x1c] - fOffset) &&
             (pfIterator[0x1e] < currentBestScore) )
        {
            bestReturnValue = pfIterator[0x26];
            currentBestScore = pfIterator[0x1e];
        }

        // --- Block 4: subobject at offsets +0xB8 .. +0xD8 ---
        if ( (pfIterator[0x3e] != 0.0f) &&
             (pfIterator[0x2e] + fOffset < searchBounds[0]) && (searchBounds[0] < pfIterator[0x32] - fOffset) &&
             (pfIterator[0x2f] + fOffset < searchBounds[1]) && (searchBounds[1] < pfIterator[0x33] - fOffset) &&
             (pfIterator[0x30] + fOffset < searchBounds[2]) && (searchBounds[2] < pfIterator[0x34] - fOffset) &&
             (pfIterator[0x36] < currentBestScore) )
        {
            bestReturnValue = pfIterator[0x3e];
            currentBestScore = pfIterator[0x36];
        }

        pfIterator += 0x60; // advance to next entity (0x60 float stride)
        loop--;
    } while (loop != 0);

    return bestReturnValue;
}