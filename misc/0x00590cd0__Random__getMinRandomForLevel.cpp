// FUNC_NAME: Random::getMinRandomForLevel
// Address: 0x00590cd0
// Role: Returns a random float with level-dependent minimum-of-two logic.
//       Byte at levelData+0x01 is a threshold: 0 returns 1.0, 1 returns one random, >=2 returns min of two randoms.
float Random::getMinRandomForLevel(RandomLevelData* levelData) {
    // +0x01: m_level (uint8) - probability bias level
    if (levelData->m_level < 1) {
        return 1.0f;
    }
    float firstRandom = this->randomFloat(); // FUN_00591160: generate random float in [0,1]?
    if (levelData->m_level < 2) {
        return firstRandom;
    }
    float secondRandom = this->randomFloat();
    return (firstRandom < secondRandom) ? firstRandom : secondRandom;
}