// FUNC_NAME: Player::isDriving

bool Player::isDriving()
{
    // Dereference the vehicle pointer at this+0x360, then read bit 1 (mask 0x2) of the flags at vehicle+0x110.
    return ( *(uint32_t*)(*(int*)( (uintptr_t)this + 0x360 ) + 0x110) >> 1 ) & 1;
}