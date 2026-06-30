// FUNC_NAME: ChaseCamera::constrainPositionToSphere
void __thiscall ChaseCamera::constrainPositionToSphere(float *target)
{
    // target is a pointer to an array of 4 floats: [x, y, z, w or some extra]
    float targetX = target[0];
    float targetY = target[1];
    float targetZ = target[2];
    float targetExtra = target[3]; // extra component (e.g., roll, FOV multiplier)

    float dx = *(float *)(this + 0x10) - targetX; // this->posX
    float dy = *(float *)(this + 0x14) - targetY; // this->posY
    float dz = *(float *)(this + 0x18) - targetZ; // this->posZ
    float dist = sqrt(dx * dx + dy * dy + dz * dz);

    // Global camera distance constraints
    extern float g_cameraRadiusMult; // DAT_00e51178
    extern float g_cameraMaxRadius;   // DAT_00e5117c
    float maxAllowedDist = g_cameraMaxRadius * g_cameraRadiusMult;

    if (maxAllowedDist < dist) {
        float scale = maxAllowedDist / dist;
        // Clamp position to sphere around target
        *(float *)(this + 0x10) = scale * dx + targetX;
        *(float *)(this + 0x14) = scale * dy + targetY;
        *(float *)(this + 0x18) = scale * dz + targetZ;
        // Also adjust extra component (e.g., roll or w) toward targetExtra
        float thisExtra = *(float *)(this + 0x1c);
        *(float *)(this + 0x1c) = scale * (thisExtra - targetExtra) + targetExtra;
    }
}