// FUNC_NAME: PlayerActionableTargetSM::testPoint
// Function at 0x006e5bb0 - Tests if a world point is inside the volume defined by this object.
// Volume types: 2 = sphere/cylinder (threshold global), 4 = cone (dot > 0).
// Returns 0 (true) if inside, 1 (false) otherwise.

bool __thiscall PlayerActionableTargetSM::testPoint(float *worldPoint)
{
    // +0x88: volume type (0x02 = sphere/cylinder, 0x04 = cone)
    char volumeType = *(char *)(this + 0x88);
    if ((volumeType != 0x04) && (volumeType != 0x02))
        return true; // unknown type, treat as outside

    // +0x44, 0x48, 0x4c: position (float3)
    float *pos = (float *)(this + 0x44);
    float deltaX = worldPoint[0] - pos[0];
    float deltaY = worldPoint[1] - pos[1];
    float deltaZ = worldPoint[2] - pos[2];

    // Build delta vector (local_24, local_1c)
    // The decompiler shows a CONCAT44 hack - we keep as two separate values
    // but the vector is 3D.
    float delta[3] = { deltaX, deltaY, deltaZ };

    // +0x2c: orientation data (8 bytes, likely a quaternion or rotation matrix)
    // This function rotates the delta vector into local space.
    float localDelta[3];
    FUN_004a07f0(localDelta, delta, (undefined8 *)(this + 0x2c));
    // FUN_004a07f0 is a local rotation helper; results in localDelta[0..2]

    // +0x20 and +0x28: local direction axis (3 floats packed as:
    //   low32 of +0x20 = dir.x, high32 of +0x20 = dir.y, float at +0x28 = dir.z)
    float dirX = *(float *)(this + 0x20);
    float dirY = *(float *)((int)this + 0x24); // high32 of the 8-byte value at +0x20
    float dirZ = *(float *)(this + 0x28);

    // Dot product of local space delta with the local direction axis
    float dot = dirX * localDelta[0] + dirY * localDelta[1] + dirZ * localDelta[2];

    if (volumeType == 0x04) {
        // Cone: must be in front of the axis (positive projection)
        if (dot <= 0.0f)
            return true; // outside
    }
    else if (volumeType == 0x02) {
        // Sphere/cylinder: check projection against global threshold
        extern float g_volumeThreshold; // _DAT_00d577a0
        if (g_volumeThreshold <= dot)
            return true; // outside
    }

    return false; // inside
}