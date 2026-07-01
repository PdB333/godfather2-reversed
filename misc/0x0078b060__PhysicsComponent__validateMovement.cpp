// FUNC_NAME: PhysicsComponent::validateMovement
// Address: 0x0078b060
// Fastcall member function of PhysicsComponent or similar.
// Checks movement speed against a threshold and returns a packed status code.

int __fastcall PhysicsComponent::validateMovement(int thisPtr)
{
    int tempPtr;
    // Offset 0x58 - likely current speed magnitude or component
    float currentValue = *(float *)(thisPtr + 0x58);
    // Dereference global singleton pointer at 0x012233a0+4 to get object pointer
    tempPtr = **(int **)(DAT_012233a0 + 4);
    if (tempPtr != 0) {
        tempPtr = tempPtr + -0x1f30; // Offset to some sub-structure
        if (tempPtr != 0) {
            // Compute scaled sum of two velocities (0x54 + 0x58) using global factor
            float scaledSum = (*(float *)(thisPtr + 0x54) + currentValue) * _DAT_00d5c458;
            // The next line is effectively a no-op (currentValue = currentValue - scaledSum + scaledSum)
            // Likely a decompilation artifact; original may have been subtraction.
            currentValue = (currentValue - scaledSum) + scaledSum;
            // Clamp to global maximum (DAT_00d5e288)
            if (DAT_00d5e288 < currentValue) {
                currentValue = DAT_00d5e288;
            }
        }
    }
    // Extract upper 24 bits from tempPtr (after shift) to form status flags
    uint3 upperBits = (uint3)((uint)tempPtr >> 8);
    if (currentValue < *(float *)(thisPtr + 0x40)) {
        // Below threshold (0x40): set low byte to 1
        return CONCAT31(upperBits, 1);
    }
    // Above threshold: low byte = 0
    return (uint)upperBits << 8;
}