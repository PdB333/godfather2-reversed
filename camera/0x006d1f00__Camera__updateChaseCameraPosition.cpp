// FUNC_NAME: Camera::updateChaseCameraPosition
void __thiscall Camera::updateChaseCameraPosition(Camera* this) {
    // get pointer to target data (player/camera target transform)
    TargetData* targetData = (TargetData*)GetChaseCameraTargetData();
    float unknownGlobal1 = DAT_00e44564;        // some global constant (e.g., player height offset)
    float speedFactor = _DAT_00d5780c;          // speed/damping factor
    float targetPosX = targetData->m_field[0];  // index 0: x position
    float targetPosY = targetData->m_field[1];  // index 1: y position
    float targetPosZ = targetData->m_field[2];  // index 2: z position

    // copy target offset vector (indices 12-15) to camera velocity/offset
    this->m_targetOffsetX = targetData->m_field[12]; // +0x90
    this->m_targetOffsetY = targetData->m_field[13]; // +0x94
    this->m_targetOffsetZ = targetData->m_field[14]; // +0x98
    this->m_targetOffsetW = targetData->m_field[15]; // +0x9C

    // adjust Y offset by a global constant (camera height offset)
    this->m_targetOffsetY += DAT_0112a870;

    // compute horizontal distance to target
    float dx = unknownGlobal1 - targetPosX;
    float dz = unknownGlobal1 - targetPosZ;  // note: second subtraction uses same global? might be different target component
    // Actually: fVar6 = fVar6 - pfVar2[2]; so it's unknownGlobal1 - targetPosZ
    float distSq = dx * dx + dz * dz;
    float invDist = 0.0f;
    if (distSq > DAT_00d5f2b4) {  // threshold to avoid division by zero
        invDist = speedFactor / sqrt(distSq);
    }

    // compute new camera position
    float newY = this->m_targetOffsetY + DAT_00e51128;  // additional Y offset
    float newX = DAT_00e51124 * invDist * dx + this->m_targetOffsetX; // +0xc0
    float newZ = DAT_00e51124 * invDist * dz + this->m_targetOffsetZ; // +0xc8 (200 decimal)
    this->m_cameraPosX = newX;    // +0xc0
    this->m_cameraPosY = newY;    // +0xc4
    this->m_cameraPosZ = newZ;    // +0xc8
    this->m_cameraPosW = speedFactor; // +0xcc (probably some blend factor)

    // final camera position with relative offset from target
    float offsetX = targetData->m_field[8] * DAT_00e51178;
    float offsetZ = targetData->m_field[10] * DAT_00e51178;
    this->m_finalPosX = this->m_cameraPosX - offsetX; // +0x70
    this->m_finalPosY = newY + _DAT_00e5112c;          // +0x74
    this->m_finalPosZ = newZ - offsetZ;                // +0x78
    this->m_finalPosW = speedFactor;                   // +0x7c
}