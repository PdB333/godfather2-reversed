// FUNC_NAME: randomIntFromRange
// Function at 0x005fe000: Returns a random integer computed as (rand() * g_scaleFactor1 * g_scaleFactor2)
// The two global floats (DAT_00e44590 and _DAT_00e44670) are likely normalization and range multipliers.
int randomIntFromRange(void)
{
    int randVal = _rand(); // Standard C rand() returning [0, RAND_MAX]
    // Multiply by two global scaling factors to produce an integer in a specific range.
    // DAT_00e44590 and _DAT_00e44670 are presumably set elsewhere to control the output range.
    return (int)((float)randVal * DAT_00e44590 * _DAT_00e44670);
}