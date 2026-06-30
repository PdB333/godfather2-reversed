// FUNC_NAME: computeModularInverse28
int computeModularInverse28(uint *outResult) {
    // Read the value to invert from this->dataPointer (offset +0x0C)
    uint value = **(uint **)(this + 0x0C);

    // Bit 0 must be set (value must be odd), otherwise fail with -3
    if ((value & 1) == 0) {
        return -3;
    }

    // Newton's method for modular inverse modulo 2^28
    uint inv = (value * 2 + 4) & 8;     // Cheap initial approximation step
    inv = inv + value;                  // initial guess

    // Two Newton-Raphson iterations: inv = inv * (2 - value * inv)
    inv = (2 - inv * value) * inv;
    inv = (2 - inv * value) * inv;

    // Final result = -inv & 0xFFFFFFF (modulo 2^28 with sign flip)
    *outResult = -inv & 0xFFFFFFF;
    return 0;
}