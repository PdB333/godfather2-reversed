// FUNC_NAME: ChaseCamera::clampTargetPosition
bool ChaseCamera::clampTargetPosition(void)
{
    // Fetch the reference point (center of sphere) from an internal position buffer
    Vector3* refPos = (Vector3*)CameraSystem::getReferencePosition();
    float radius = g_followRadius; // DAT_01206804, base radius

    // Unpack the reference position into a local vector (the decompiler misread as double)
    Vector3 targetPos;
    targetPos.x = refPos->x;
    targetPos.y = refPos->y;
    targetPos.z = refPos->z;

    // Compute offset from reference to this object's position (offsets +0xA4, +0xA8, +0xAC)
    float dx = *(float*)((char*)this + 0xA4) - targetPos.x;
    float dy = *(float*)((char*)this + 0xA8) - targetPos.y;
    float dz = *(float*)((char*)this + 0xAC) - targetPos.z;

    // Adjust radius if base radius is negative (likely a sign flag)
    if (g_followRadius < 0.0f)
    {
        radius = radius + g_radiusAdjust; // DAT_00e44578
    }
    radius = radius * g_smoothingFactor; // _DAT_00d69c4c, possibly time delta

    float dist = sqrtf(dx*dx + dy*dy + dz*dz);
    Vector3 newPos;

    if (dist <= radius)
    {
        // Inside sphere – keep original position
        newPos.x = *(float*)((char*)this + 0xA4);
        newPos.y = *(float*)((char*)this + 0xA8);
        newPos.z = *(float*)((char*)this + 0xAC);
    }
    else
    {
        // Clamp to surface of the sphere along the direction from reference to object
        float scale = radius / dist;
        newPos.x = dx * scale + targetPos.x;
        newPos.y = dy * scale + targetPos.y;
        newPos.z = dz * scale + targetPos.z;
    }

    // Set the object's position to the clamped value
    CameraSystem::setPosition(&newPos); // FUN_00790c80

    return (dist <= radius);
}