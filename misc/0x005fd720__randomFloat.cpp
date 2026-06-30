// FUNC_NAME: randomFloat
// Function address: 0x005fd720
// Returns a random float in [0, 1) by multiplying rand() result by inverse of RAND_MAX.
float randomFloat(void)
{
    int randVal = _rand();                                 // Standard C rand() returns 0..32767
    float invRandMax = *(float*)0x00e44590;                // DAT_00e44590 = 1.0f / RAND_MAX
    return (float)randVal * invRandMax;                    // Scale to [0.0, 1.0)
}