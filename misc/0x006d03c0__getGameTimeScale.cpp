// FUNC_NAME: getGameTimeScale
// Function address: 0x006d03c0
// Role: Returns a global float (time scale multiplier) stored at 0x00e5111c
float getGameTimeScale(void)
{
    return *(float*)0x00e5111c;
}