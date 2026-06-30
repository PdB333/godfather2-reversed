// FUNC_NAME: getRandomFloat
// Address: 0x006b6f70
// Role: Returns a random float in [0.0, 1.0) by scaling rand() with RAND_MAX reciprocal.
// Global DAT_00e44590 is likely 1.0f / RAND_MAX (32767 for MSVC).

extern float g_randomScale; // DAT_00e44590

float getRandomFloat(void)
{
    int r = rand();
    return (float)r * g_randomScale;
}