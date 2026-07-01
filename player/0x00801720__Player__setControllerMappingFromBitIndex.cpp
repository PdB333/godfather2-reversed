//FUNC_NAME: Player::setControllerMappingFromBitIndex
uint __thiscall Player::setControllerMappingFromBitIndex(uint bitIndex)
{
    // Write a 4-byte value from a global lookup table into member at offset 0x854.
    // The table index is derived from bitIndex: ((bitIndex >> 3) - 1) & 0xF, giving 0-15.
    // This likely maps a bit number (0-127) to a controller slot or action index.
    *(uint32_t *)(this + 0x854) = *(uint32_t *)(&g_controllerMappingTable + (((bitIndex >> 3) - 1) & 0xF) * 4);

    // Call a global function (likely GetTickCount or similar) and return its value with low byte cleared.
    // This might be used for timing or frame counting.
    uint32_t result = FUN_007fbdf0(g_someGlobalPointer); // DAT_00e53b08
    return result & 0xFFFFFF00;
}