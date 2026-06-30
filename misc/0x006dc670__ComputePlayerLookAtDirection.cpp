// FUNC_NAME: ComputePlayerLookAtDirection

// Function at 0x006dc670: Computes a direction vector from the player's position to a target point,
// then applies a 90-degree rotation and possibly a constant offset.
// Uses global player transform (from GetPlayerTransform) and a vector length squared function.
void ComputePlayerLookAtDirection(float *outDirection, float *targetPos)
{
    // Get pointer to player's transform structure (likely from a global manager)
    auto *playerTransform = (uint8_t *)FUN_00471610(); // returns pointer to player transform

    // Extract player position (x and z only, y assumed 0)
    float dx = targetPos[0] - *(float *)(playerTransform + 0x30); // player position x
    float dz = targetPos[2] - *(float *)(playerTransform + 0x38); // player position z
    float dy = 0.0f;
    int unused = 0; // local_14, not used

    // Compute squared length of the 2D direction vector (dx, 0, dz)
    float lengthSq = FUN_0056afa0(&dx, &dx); // dot product of (dx, 0, dz) with itself

    if (lengthSq != 0.0f) {
        // Non-zero: produce rotated direction: (constant - dz, 0, dx)
        // DAT_00e44564 is a global constant (likely 0.0f or 1.0f)
        outDirection[0] = DAT_00e44564 - dz;
        outDirection[1] = 0.0f;
        outDirection[2] = dx;
        return;
    }

    // Zero-length (player and target coincide): fallback to player's own forward direction
    // The player transform structure has a 3-float vector at offset 0 (likely forward)
    auto *playerForward = (uint64_t *)playerTransform; // treat as 8-byte pointer for first 8 bytes
    *(uint64_t *)outDirection = *playerForward; // copy first two floats (x, y)
    outDirection[2] = *(float *)(playerForward + 1); // third float (z) from offset 8
}