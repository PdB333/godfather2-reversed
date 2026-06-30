// FUNC_NAME: Player::checkInteractionRange
uint __fastcall Player::checkInteractionRange(int thisPtr)
{
    float distanceSq;
    uint result;
    int tempVar1;
    int tempVar2;
    int *interactionPtr;
    float rangeSq;
    float dx, dy, dz;

    // Check if bit 3 of flags at offset 0x80 is set
    result = *(uint *)(thisPtr + 0x80) >> 3;
    if ((result & 1) != 0) {
        // Get the local player (or some primary entity)
        result = getLocalPlayer(); // FUN_00800a90

        // Choose which interaction target field to use: 0xa4 or 0x9c
        interactionPtr = (int *)(thisPtr + 0xa4);
        if ((*(int *)(thisPtr + 0xa4) == 0) || (*(int *)(thisPtr + 0xa4) == 0x48)) {
            interactionPtr = (int *)(thisPtr + 0x9c);
        }

        // Adjust the interaction value (subtract constant 0x48)
        if (*interactionPtr == 0) {
            tempVar1 = 0;
        } else {
            tempVar1 = *interactionPtr - 0x48;
        }

        // Additional conditions: a bit flag in some manager at 0x98 + 0x8e0, and non-null results
        if ((((*(uint *)(*(int *)(thisPtr + 0x98) + 0x8e0) >> 10 & 1) != 0) && (result != 0)) &&
            (tempVar1 != 0)) {
            // Get the range from the primary entity (offset 0x34c)
            rangeSq = *(float *)(result + 0x34c);

            // Get positions of two objects (likely the player and something else)
            tempVar1 = getPositionComponent(); // FUN_00471610
            tempVar2 = getPositionComponent(); // FUN_00471610

            // Compute distance squared between their positions (3D)
            dx = *(float *)(tempVar2 + 0x30) - *(float *)(tempVar1 + 0x30);
            dy = *(float *)(tempVar2 + 0x34) - *(float *)(tempVar1 + 0x34);
            dz = *(float *)(tempVar2 + 0x38) - *(float *)(tempVar1 + 0x38);
            distanceSq = dz*dz + dy*dy + dx*dx;

            // If within range, return a packed handle (combining address of tempVar2's position with a flag)
            if (distanceSq < rangeSq * rangeSq) {
                // Construct a 4-byte value: high 24 bits = (tempVar2+0x30) >> 8, low byte = 1
                result = ((uint)(tempVar2 + 0x30) >> 8) | 1;
                return result;
            }
        }
    }
    // Return masked value (clear low byte)
    return result & 0xffffff00;
}