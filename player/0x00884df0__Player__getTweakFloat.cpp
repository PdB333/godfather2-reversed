// FUNC_NAME: Player::getTweakFloat
float Player::getTweakFloat() const {
    float ret;
    // Check bit 1 of flags at this+0x70
    if ( (*(uint32_t*)((uint8_t*)this + 0x70) & 2) != 0 ) {
        // DAT_00d5eee4
        ret = *(float*)0x00d5eee4;
    } else {
        // _DAT_00d5780c
        ret = *(float*)0x00d5780c;
    }
    return ret;
}