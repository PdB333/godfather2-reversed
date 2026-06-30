// FUNC_NAME: Math::lerpPositionToTarget
// Address: 0x006dd4b0
// This function interpolates a 3D position (param_1) towards a target direction (param_3) over time.
// It computes a desired position based on a direction derived from param_3 (likely yaw/pitch angles),
// then checks if the distance from the current position to that desired point is within a threshold.
// If so, it snaps the position to the intermediate computed point (local_18/14/10).

void lerpPositionToTarget(float* position, float* timeDelta, float* targetAngles)
{
    float direction[3]; // local_24, local_20, local_1c
    float desiredPos[3]; // local_18, local_14, local_10
    float result[3];     // local_c (2 floats) + local_4 (1 float)
    float delta;

    // Convert the two angles (likely yaw and pitch from param_3) to a unit direction vector.
    Math::getDirectionFromAngles(direction, targetAngles[0], targetAngles[1]);

    // Delta time (global current time minus the stored time parameter)
    delta = G_currentTime - timeDelta[0];

    // Compute desired position = current position + direction * delta
    desiredPos[0] = direction[0] * delta + position[0];
    desiredPos[1] = direction[1] * delta + position[1];
    desiredPos[2] = direction[2] * delta + position[2];

    // Check game state (global entity manager pointer)
    int* managerPtr = *(int**)(*(int*)(G_entityManager + 4));
    if ((managerPtr == nullptr) || (managerPtr == (int*)0x1f30) || 
        ((*(uint*)(managerPtr + -0x1650) >> 25 & 1) == 0))
    {
        // Compute the actual target position from current and desired, store in result.
        float distSq = Math::distanceSquared(desiredPos, position, result);
        if ((double)G_minDistanceThreshold < distSq)
        {
            // If distance squared is larger than threshold, snap position to result.
            position[0] = result[0];
            position[1] = result[1];
            position[2] = result[2];
        }
    }
    return;
}