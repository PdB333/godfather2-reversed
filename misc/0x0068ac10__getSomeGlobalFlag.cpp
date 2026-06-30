// FUNC_NAME: getSomeGlobalFlag
uint8_t getSomeGlobalFlag() {
    // Returns a byte from global data at 0x01129a71
    // Likely a game state flag or setting
    return *reinterpret_cast<uint8_t*>(0x01129a71);
}