// FUNC_NAME: Player::getAimTargetPosition
// Address: 0x0085f340
// Role: Computes the target position for aiming, relative to the player's camera or transform.
// Returns 1 if successful, 0 if no valid target.

bool __thiscall Player::getAimTargetPosition(float *outPosition)
{
    int aimState = *(int *)(this + 0x110c); // +0x110c: current aiming state (0=none, 1=stored, 2=camera)
    bool result = false;

    if (aimState > 0 && aimState < 3) {
        float targetX, targetY, targetZ;

        if (aimState == 2) {
            // Use camera aim position
            if (!getCameraAimPosition(&targetX)) { // FUN_005fe020
                return false;
            }
        } else {
            // Use stored target position from this object
            targetX = *(float *)(this + 0x1080); // +0x1080: stored target X
            targetY = *(float *)(this + 0x1084); // +0x1084: stored target Y
            targetZ = *(float *)(this + 0x1088); // +0x1088: stored target Z
        }

        result = true;
        void *playerTransform = getPlayerTransform(); // FUN_00471610: returns pointer to transform struct
        // Compute relative position: target - player position
        outPosition[0] = targetX - *(float *)(playerTransform + 0x30); // +0x30: player position X
        outPosition[1] = targetY - *(float *)(playerTransform + 0x34); // +0x34: player position Y
        outPosition[2] = targetZ - *(float *)(playerTransform + 0x38); // +0x38: player position Z
    }

    return result;
}