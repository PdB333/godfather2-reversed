// FUNC_NAME: rollChance
// Address: 0x007227f0
// Check if a random value normalized to [0,1) is less than a stored probability threshold at [this+0x124].
// The global constant DAT_00e44590 is the reciprocal of RAND_MAX (0x7FFF), converting rand() to a float in [0,1).

int __fastcall rollChance(int thisPtr) {
    int randValue = _rand();
    float normalizedRand = (float)randValue * (1.0f / 32767.0f);  // DAT_00e44590
    float probabilityThreshold = *(float *)(thisPtr + 0x124);       // +0x124: chance (0..1)
    return (normalizedRand < probabilityThreshold) ? 1 : 0;
}