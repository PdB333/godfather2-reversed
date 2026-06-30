// FUNC_NAME: getGlobalTimeScale
float getGlobalTimeScale(void)
{
    // Returns the global time scale value stored at 0x00e51120
    // This is used to control the overall game speed (e.g., slow motion effects)
    return *(float*)0x00e51120;
}