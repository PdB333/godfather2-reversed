// FUNC_NAME: Player::getDamageMultiplier
float __fastcall Player::getDamageMultiplier(int this)
{
    return *(float *)(*(int *)(this + 0xc) + 0x1d8) * *(float *)(this + 0x20);
}