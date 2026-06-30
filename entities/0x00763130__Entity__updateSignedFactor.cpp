// FUNC_NAME: Entity::updateSignedFactor
// Address: 0x00763130
// Called from: 0x007642b0 (likely within Entity update loop)
// Computes a signed factor (speed/force) based on a stored factor (offset +0xA4) and a global time step.
// Updates a sign flag at offset +0xE8 (bit0 = 1 for non-negative, 0 for negative).

__thiscall float Entity::updateSignedFactor(void) {
    // +0x78: pointer to active component (null if inactive)
    if (*(int*)(this + 0x78) == 0) {
        return 0.0f;
    }

    // +0xA4: stored factor (e.g., acceleration or speed scale)
    float factor = *(float*)(this + 0xA4);

    // Global function returning time step or similar (0x005FE710)
    double timeStep = FUN_005FE710();

    double result = timeStep * (double)factor;

    // +0xE8: flags (bit0 = sign flag)
    if (result < 0.0) {
        *(unsigned int*)(this + 0xE8) &= ~1;   // Clear bit0 (negative)
    } else {
        *(unsigned int*)(this + 0xE8) |= 1;    // Set bit0 (non-negative)
    }

    return (float)result;
}