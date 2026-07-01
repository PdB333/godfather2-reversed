// FUNC_NAME: Player::setAimTarget
void __thiscall Player::setAimTarget(Player *this, const uint32_t *aimTarget) {
    // Copy 4 uint32 values (likely x, y, z, w of aim target or similar) into members at offsets +0xF44 to +0xF50
    *(uint32_t *)((uint8_t *)this + 0xF44) = aimTarget[0];  // +0xF44: aimTarget.x
    *(uint32_t *)((uint8_t *)this + 0xF48) = aimTarget[1];  // +0xF48: aimTarget.y
    *(uint32_t *)((uint8_t *)this + 0xF4C) = aimTarget[2];  // +0xF4C: aimTarget.z
    *(uint32_t *)((uint8_t *)this + 0xF50) = aimTarget[3];  // +0xF50: aimTarget.w (or padding)
}