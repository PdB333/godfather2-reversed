// FUNC_NAME: EARSObject::writeDwordConstant
void EARSObject::writeDwordConstant(EARSObject* this, uint32_t param) {
    uint32_t constantValue = 0x78; // 120 dec - likely a specific game state constant (time, health, etc.)
    writeToDataBuffer(this, param, &constantValue, 1); // writes a single DWORD to the game stream/buffer
}