// FUNC_NAME: GameConfig::loadConfig
void __thiscall GameConfig::loadConfig(GameConfig* this) {
    uint32* config = (uint32*)this;
    // Setting 0
    config[0] = readConfigValue(0);
    // Setting 1: boolean
    int setting1 = readConfigValue(1);
    *(char*)(config + 1) = (setting1 == 1) ? 1 : 0;
    // Settings 2-10
    for (int i = 2; i <= 10; i++) {
        config[i] = readConfigValue(i);
    }
    // Setting 11 is skipped
    readConfigValue(11);
    // Settings 12-19 stored at indices 11-18
    for (int i = 12; i <= 19; i++) {
        config[i - 1] = readConfigValue(i);
    }
    // Setting 20: boolean at index 19
    int setting20 = readConfigValue(20);
    *(char*)(config + 19) = (setting20 == 1) ? 1 : 0;
}