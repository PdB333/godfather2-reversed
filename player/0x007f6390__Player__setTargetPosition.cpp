// FUNC_NAME: Player::setTargetPosition
void __thiscall Player::setTargetPosition(void *this, const Vector3 *target) {
    // +0x984: uint64 + uint32? Actually stores 8 bytes then 4 bytes.
    // Target is a 12-byte structure: 8 bytes at 0x984, 4 bytes at 0x98c.
    // Could be two floats (X,Y) in first 8 bytes and Z in last 4, but copying as uint64 + uint32.
    // For safety, treat as raw memory copy.
    *(uint64 *)((uint8 *)this + 0x984) = *(const uint64 *)target;
    *(uint32 *)((uint8 *)this + 0x98c) = *(const uint32 *)((const uint8 *)target + 8);
}