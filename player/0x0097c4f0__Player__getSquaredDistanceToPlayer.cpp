// FUNC_NAME: Player::getSquaredDistanceToPlayer
float Player::getSquaredDistanceToPlayer(float *otherPos) // param_2: other player's position (x, z)
{
    float distSq = DAT_00d5f6f0; // Default distance value (likely a global constant, e.g., 0.0f or a large sentinel)
    float *myPos = (float *)FUN_00950b20(); // Likely returns pointer to this player's position (x, z) - e.g., Player::getPosition()
    if (myPos != nullptr) {
        // Compute squared distance in 2D (x, z) - typical for game world ignoring y
        float dx = myPos[0] - otherPos[0]; // +0x00: x coordinate
        float dz = myPos[2] - otherPos[2]; // +0x08: z coordinate (index 2, since floats are 4 bytes)
        distSq = dx * dx + dz * dz;
    }
    return (float10)distSq; // Cast to 80-bit extended precision float (x87 FPU)
}