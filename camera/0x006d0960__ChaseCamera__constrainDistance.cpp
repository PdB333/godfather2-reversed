// FUNC_NAME: ChaseCamera::constrainDistance
void __thiscall ChaseCamera::constrainDistance(float* targetPosAndAngle) {
    float dx = this->position.x - targetPosAndAngle[0];
    float dy = this->position.y - targetPosAndAngle[1];
    float dz = this->position.z - targetPosAndAngle[2];
    float distance = sqrtf(dx * dx + dy * dy + dz * dz);
    float minDistance = _DAT_00d577a0; // Global minimum distance threshold
    float maxDistance = this->maxDesiredDistance; // +0x88

    // Only adjust if distance is within the valid range (avoid divide-by-zero and excessive pull)
    if (distance > minDistance && distance < maxDistance) {
        float scale = maxDistance / distance;
        // Push position outward to exactly maxDistance from target
        this->position.x = targetPosAndAngle[0] + dx * scale;
        this->position.y = targetPosAndAngle[1] + dy * scale;
        this->position.z = targetPosAndAngle[2] + dz * scale;
        // Interpolate angular component (likely yaw or rotation) similarly
        this->angle = targetPosAndAngle[3] + (this->angle - targetPosAndAngle[3]) * scale; // +0x1c
    }
}