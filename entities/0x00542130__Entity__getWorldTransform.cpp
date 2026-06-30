// FUNC_NAME: Entity::getWorldTransform
void __thiscall Entity::getWorldTransform(float *posOut, float *orientOut)
{
    // Check if the transform node exists (offset 0x260: m_pTransformNode)
    if (this->m_pTransformNode != 0) {
        float buf[6]; // Local buffer for transform data (position + orientation)
        // Call virtual function at vtable offset 0x1c on an interface obtained from m_pTransformNode+0x10
        // Parameters: (this+0xe0, 0, &buf)
        // This likely retrieves a world transform into buf (e.g., 3 position floats + 3 orientation floats)
        (*(code **)(**(int **)(*(int *)this->m_pTransformNode + 0x10) + 0x1c))
            (this->m_pTransformNode + 0xe0, 0, buf);
        // Copy position from buf[0..2]
        posOut[0] = buf[0];
        posOut[1] = buf[1];
        posOut[2] = buf[2];
        // Copy orientation (e.g., euler angles or forward vector) from buf[3..5]
        orientOut[0] = buf[3];
        orientOut[1] = buf[4];
        orientOut[2] = buf[5];
        return;
    }
    // No transform node: zero outputs
    posOut[0] = 0.0f;
    posOut[1] = 0.0f;
    posOut[2] = 0.0f;
    orientOut[0] = 0.0f;
    orientOut[1] = 0.0f;
    orientOut[2] = 0.0f;
}