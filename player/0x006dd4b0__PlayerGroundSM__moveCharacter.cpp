// FUNC_NAME: PlayerGroundSM::moveCharacter
void PlayerGroundSM::moveCharacter(float* position, float* lastUpdateTime, float* targetAngles)
{
    float direction[3];
    // Convert target angles (yaw, pitch) to a direction vector
    FUN_004a2540(direction, targetAngles[0], targetAngles[1]); // likely Math::eulerToDirection

    // Compute elapsed time since last update
    float deltaTime = DAT_00e44564 - *lastUpdateTime; // global game time - stored timestamp

    // Compute desired new position = currentPos + direction * deltaTime
    float newPosition[3];
    newPosition[0] = direction[0] * deltaTime + position[0];
    newPosition[1] = direction[1] * deltaTime + position[1];
    newPosition[2] = direction[2] * deltaTime + position[2];

    // Retrieve game state from singleton (pointer at DAT_012233a0 + 4)
    int gameState = **(int**)(DAT_012233a0 + 4);  // likely SimManager::someState
    if ((gameState == 0) || (gameState == 0x1f30) ||
        ((*(uint*)(gameState - 0x1650) >> 0x19 & 1) == 0))  // bit 25 check
    {
        // Check distance and apply movement if within threshold
        float10 distance = (float10)FUN_006ca5e0(newPosition, position, &position); // likely Math::distanceSq
        if ((float10)DAT_00d5cf70 < distance)
        {
            // Copy corrected position (from FUN_006ca5e0 output) back into position
            position[0] = *(float*)&someTemp; // local_c appears as 2 floats at position[0..2]
            position[1] = *(float*)((char*)&someTemp + 4);
            // Note: functional decompilation may not fully capture the exact semantics
        }
    }
}