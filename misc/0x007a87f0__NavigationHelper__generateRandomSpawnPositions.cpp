// FUNC_NAME: NavigationHelper::generateRandomSpawnPositions
int NavigationHelper::generateRandomSpawnPositions(bool bValidate, SpawnCandidate* outScratchPos, DynamicFloatArray* outPosArray, uint numSamples, void* pTarget)
{
    // Get random engine and initial random position/direction sample
    uint randomSeed = Engine::getRandomSeed();  // FUN_007ff880
    RandomSample sample;
    Engine::getRandomSample(&sample, randomSeed);  // FUN_00799630 -> fills base position and direction

    uint usedCount = 0;
    uint iterIndex = 0;

    if (numSamples != 0) {
        do {
            // Mark this iteration as used (bitmask)
            Engine::markSampleUsed(randomSeed, 1 << (iterIndex & 0x1f));  // FUN_007996e0

            // Compute candidate position: base + direction * radius
            float radius = *(float*)((int)pTarget + 0x30c8);   // +0x30C8 spawn/search radius
            float posX = sample.dirX * radius + sample.baseX;
            float posY = sample.dirY * radius + sample.baseY;
            float posZ = sample.dirZ * radius + sample.baseZ;

            if (!bValidate || Engine::isValidPosition(posX, posY, posZ, 1, 1)) {  // FUN_006c0050
                // Store candidate to scratch buffer
                outScratchPos->x = posX;
                outScratchPos->y = posY;
                outScratchPos->z = posZ;

                // Get reference position (likely player/camera) for distance calculation
                Vector3* refPos = (Vector3*)Engine::getReferencePosition();  // FUN_00471610
                float dx = posX - refPos->x;
                float dy = posY - refPos->y;
                float dz = posZ - refPos->z;
                outScratchPos->distSq = dx*dx + dy*dy + dz*dz;

                // Grow dynamic array if needed
                if (outPosArray->count == outPosArray->capacity) {
                    int newCapacity = (outPosArray->capacity == 0) ? 1 : outPosArray->capacity * 2;
                    Engine::reallocateDynamicArray(newCapacity);  // FUN_0079af20
                }

                // Copy candidate to output array
                float* dest = &outPosArray->buffer[outPosArray->count * 4];
                dest[0] = outScratchPos->x;
                dest[1] = outScratchPos->y;
                dest[2] = outScratchPos->z;
                dest[3] = outScratchPos->distSq;
                outPosArray->count++;

                usedCount++;
                outScratchPos++;
            }
            iterIndex++;
        } while (iterIndex < numSamples);
    }
    return usedCount;
}