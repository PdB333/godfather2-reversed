// FUNC_NAME: Player::isInCutscene
bool __fastcall Player::isInCutscene(int this)
{
    bool result = false;
    // +0x160: pointer to some player state/manager object
    // +0x249c: bitfield in that object, bit 22 (0x400000) indicates cutscene active
    if (*(int *)(this + 0x160) != 0 &&
        (*(uint *)(*(int *)(this + 0x160) + 0x249c) >> 0x16 & 1) != 0)
    {
        result = true;
    }
    return result;
}