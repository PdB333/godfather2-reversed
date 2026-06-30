// FUNC_NAME: ChaseCamera::updateCameraTransform
void __thiscall ChaseCamera::updateCameraTransform(void *thisParam, void *outputMatrix)
{
    float deltaTime;
    float targetX, targetY, targetZ, targetW;
    float interpX, interpY, interpZ, interpW;
    bool flag;
    int unusedId;

    // Dereference chain: this->m_pSceneNode->m_pTransform->m_position
    // Offsets: this+0x14 -> scene node, +0x30 -> transform pointer, +0x18 -> position array
    int transformPtr = *(int *)(*(int *)(*(int *)((int)thisParam + 0x14) + 0x30) + 0x18);
    float positionX = *(float *)(transformPtr + 0x30);
    float positionY = *(float *)(transformPtr + 0x34);
    float positionZ = *(float *)(transformPtr + 0x38);

    // Global constants (likely zero offset values)
    const float g_constantA = *(float *)0x00e2b334; // Some Y offset
    const float g_constantB = *(float *)0x00e2b1a4; // Some W offset
    const float g_constantC = *(float *)0x00e44564; // Reference time

    // Compute time delta from this->m_lastTimestamp (offset +0xB4)
    deltaTime = g_constantC - *(float *)((int)thisParam + 0xb4);

    // Build first row of output structure: world position + offset
    targetX = positionX;
    targetY = positionY + g_constantA;
    targetZ = positionZ;
    targetW = g_constantB;

    // Store something from this->m_pSomePointer->m_value (offset +0x18->+0x2C)
    unusedId = *(int *)(*(int *)((int)thisParam + 0x18) + 0x2c);

    // Interpolate from this->m_velocity (offsets +0x90, +0x94, +0x98, +0x9C)
    interpX = targetX + *(float *)((int)thisParam + 0x90) * deltaTime;
    interpY = targetY + *(float *)((int)thisParam + 0x94) * deltaTime;
    interpZ = targetZ + *(float *)((int)thisParam + 0x98) * deltaTime;
    interpW = targetW + *(float *)((int)thisParam + 0x9c) * deltaTime;

    flag = true; // Some toggle or identity flag

    // Call function to set the final matrix (likely a render camera transform)
    // This builds a 4x4 or 3x4 matrix from the local floats and writes to outputMatrix
    FUN_009e69d0(&targetX, outputMatrix);
}