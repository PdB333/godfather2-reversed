// FUNC_NAME: getGameStateByte2
// Address: 0x00433ce0
// Role: Extracts the second byte (bits 8-15) from a packed global game state value.
uint getGameStateByte2(void) {
    uint packedState = getPackedGameState();
    return packedState >> 8;
}