// FUNC_NAME: Player::getMinPlayerStat
float __fastcall Player::getMinPlayerStat(void) {
    // Offset +0x2C88: pointer to PlayerMovementData (or similar sub-object)
    // PlayerMovementData:
    //   +0x50: float stat1
    //   +0x54: float stat2
    float result;
    float* movementData = *(float**)((char*)this + 0x2C88);
    result = *(float*)(movementData + 0x50); // stat1
    float val2 = *(float*)(movementData + 0x54); // stat2
    if (val2 < result) {
        result = val2;
    }
    return result;
}