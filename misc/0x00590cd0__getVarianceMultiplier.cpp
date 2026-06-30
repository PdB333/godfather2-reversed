// FUNC_NAME: getVarianceMultiplier
float getVarianceMultiplier(void* unused, int settingsPtr) {
    // settingsPtr points to a structure with a byte at offset 1 representing difficulty level
    char level = *(char*)(settingsPtr + 1);
    
    if (level < 1) {
        return 1.0f;
    }
    
    float firstRoll = getRandomFloat01(); // FUN_00591160
    if (level < 2) {
        return firstRoll;
    }
    
    float secondRoll = getRandomFloat01(); // FUN_00591160
    return (firstRoll < secondRoll) ? firstRoll : secondRoll;
}