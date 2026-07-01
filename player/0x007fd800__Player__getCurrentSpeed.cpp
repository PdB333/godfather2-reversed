// FUNC_NAME: Player::getCurrentSpeed
float __thiscall Player::getCurrentSpeed(Player *this)
{
    // Check if player is in a specific state (state 4) and a flag bit is set (bit 1 of flags at +0x8e0)
    if ((this->state == 4) && ((this->flags & 0x2) != 0)) {
        return this->speedOverride; // +0x1ca8
    }
    return this->speedBase; // +0x1c90
}