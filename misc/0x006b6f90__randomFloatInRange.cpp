// FUNC_NAME: randomFloatInRange
// Address: 0x006b6f90
// Role: Returns a random float in [0, param_1) using rand() and a global reciprocal of RAND_MAX.
// DAT_00e44590 is likely 1.0f / RAND_MAX (e.g., 0.0000305185f for RAND_MAX=32767)
float randomFloatInRange(float param_1)
{
    int randomInt = _rand();
    // Multiply by reciprocal of RAND_MAX to get [0,1), then scale by param_1
    return (float)randomInt * DAT_00e44590 * param_1;
}