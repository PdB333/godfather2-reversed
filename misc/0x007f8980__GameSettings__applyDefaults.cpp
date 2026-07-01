// FUNC_NAME: GameSettings::applyDefaults
void GameSettings::applyDefaults() {
    // Copy global configuration values into member fields at offsets 0x424 and 0x42C
    // +0x424: 8-byte value (likely a double or pointer)
    // +0x42C: 4-byte value (likely an integer or float)
    *(uint64_t*)((uint8_t*)this + 0x424) = g_defaultConfigDouble;   // DAT_00d71c50
    *(uint32_t*)((uint8_t*)this + 0x42C) = g_defaultConfigInt;      // DAT_00d71c58
}