// FUNC_NAME: getTimeDelta
// Function address: 0x0054eb00
// Returns a global float value (likely the engine's frame time delta).
float getTimeDelta(void)
{
    // Global variable at address 0x00e2cb90, read as float
    return *(float*)0x00e2cb90;
}