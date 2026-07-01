// FUNC_NAME: PlayerCCTVariables::setTargetOrientation
void PlayerCCTVariables::setTargetOrientation() {
    // Read two 8-byte values that together form a 16-byte orientation (likely a quaternion) from this+0x253c
    // +0x253c: targetOrientation (16 bytes, e.g. quaternion x,y,z,w as 4 floats but loaded as two uint64)
    uint64_t orientLow = *(uint64_t *)(this + 0x253c);    // first 8 bytes (x,y as floats or double?)
    uint64_t orientHigh = *(uint64_t *)(this + 0x2544);   // next 8 bytes (z,w)
    // Apply the orientation fully (weight = 1.0f)
    FUN_0077eaa0(&orientLow, this, 1.0f);                 // internal helper to set smoothed target
    return;
}