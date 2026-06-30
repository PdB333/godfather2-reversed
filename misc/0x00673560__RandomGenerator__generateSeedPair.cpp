// FUNC_NAME: RandomGenerator::generateSeedPair
// Address: 0x00673560
// Role: Generates a pair of seeds (e.g., for random number generation or object IDs).
//       If the internal flag at +0x1c (m_singleSeedMode) is zero, two random values are produced;
//       otherwise, the first seed is forced to zero and the second receives a single random value.
void __thiscall RandomGenerator::generateSeedPair(uint *outSeed1, uint *outSeed2)
{
    uint firstRandom = getRandomValue(); // FUN_00676010
    uint secondRandom;

    // Check single-seed mode flag at offset +0x1c
    if (*(int *)((char *)this + 0x1c) == 0)
    {
        // Normal mode: generate two fresh random seeds
        firstRandom = getRandomValue();
        secondRandom = getRandomValue();
        *outSeed1 = firstRandom;
        *outSeed2 = secondRandom;
        return;
    }

    // Single-seed mode: first seed is zero, second seed uses the original random value
    *outSeed1 = 0;
    *outSeed2 = firstRandom;
}