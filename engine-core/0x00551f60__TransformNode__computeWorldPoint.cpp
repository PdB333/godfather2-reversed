// FUNC_NAME: TransformNode::computeWorldPoint
void __thiscall TransformNode::computeWorldPoint(float *inPoint, float *outPoint)
{
    // This function transforms a local point to world space using a rotation 
    // represented by a cross product with an axis vector stored in the object.
    // Offsets:
    // +0x60, +0x64, +0x68 : local position (parent space)
    // +0xd0, +0xd4, +0xd8 : world translation
    // +0xdc : fourth component (scale or w)
    // +0xe0, +0xe4, +0xe8 : rotation axis (possibly angular velocity or axis-angle)

    float *localPos = &this->m_localPosX; // +0x60
    float *worldPos = &this->m_worldPosX; // +0xd0
    float *rotAxis  = &this->m_rotAxisX;  // +0xe0

    float dx = inPoint[0] - localPos[0];
    float dy = inPoint[1] - localPos[1];
    float dz = inPoint[2] - localPos[2];

    float axisX = rotAxis[0]; // +0xe0
    float axisY = rotAxis[1]; // +0xe4
    float axisZ = rotAxis[2]; // +0xe8

    // Cross product: axis × (inPoint - localPos)
    float crossX = axisY * dz - axisZ * dy;
    float crossY = axisZ * dx - axisX * dz;
    float crossZ = axisX * dy - axisY * dx;

    // Output is world translation plus cross product
    outPoint[0] = worldPos[0] + crossX;
    outPoint[1] = worldPos[1] + crossY;
    outPoint[2] = worldPos[2] + crossZ;
    outPoint[3] = this->m_worldW; // +0xdc
}