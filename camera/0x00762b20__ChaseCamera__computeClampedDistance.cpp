// FUNC_NAME: ChaseCamera::computeClampedDistance
// Function at 0x00762b20: Calculates a clamped distance for camera based on dot product with forward vector and time comparison.
// Class offsets: +0xb8 = forward.x, +0xbc = forward.y, +0xc0 = forward.z, +0xd4 = targetDistance, +0xe8 = flags (bit0: smooth mode)

float __thiscall ChaseCamera::computeClampedDistance(float *this, float *cameraPos, float *targetPos, float paramA, float paramB) {
    float timeVal = (float)getCurrentTime();  // FUN_005fe710 returns extended precision time
    float diffX = cameraPos[0] - targetPos[0];
    float diffY = cameraPos[1] - targetPos[1];
    float diffZ = cameraPos[2] - targetPos[2];
    float temp;
    vec3Normalize(&diffX, &diffX);  // FUN_0056afa0 normalizes in place (assumes 3 floats)
    // Dot product of normalized diff with forward vector
    float dot = this->forward[0] * diffX + this->forward[1] * diffY + this->forward[2] * diffZ;
    float local2c;
    float local24;
    if (dot <= g_dotThreshold) { // _DAT_00d577a0
        local2c = paramB - paramA;
        paramB = paramA + paramB;
    } else {
        local2c = paramA + paramB;
        paramB = paramB - paramA;
    }
    if ((this->flags & 1) == 0) {
        local24 = this->targetDistance; // +0xd4
        if (timeVal <= local24 - paramB) {
            goto end;
        }
    } else {
        local24 = this->targetDistance; // +0xd4
        if ((local24 + local2c <= timeVal) || (local24 - paramB <= g_maxDistance - timeVal)) { // DAT_00e44564
            goto end;
        }
    }
    local2c = g_maxDistance - paramB; // _DAT_00e44564
end:
    return local24 + local2c;
}