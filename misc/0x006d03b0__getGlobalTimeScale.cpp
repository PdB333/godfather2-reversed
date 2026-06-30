// FUNC_NAME: getGlobalTimeScale
float getGlobalTimeScale(void)
{
    // Returns the global time scale factor stored at 0x00e51118
    // Used by the game's time management system to control simulation speed
    return *(float*)0x00e51118;
}