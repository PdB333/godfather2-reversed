// FUN_00422d40: EARSNode::setTransformMatrix
void EARSNode::setTransformMatrix(const float (&srcMatrix)[16], bool bApplyInit)
{
    // Copy 16 floats (4x4 matrix) from source to this->m_transform at offset +0x40
    // Each assignment copies 4 consecutive floats (quads) for efficiency
    float *dst = reinterpret_cast<float *>(this + 0x40 / sizeof(float));
    for (int i = 0; i < 16; i += 4)
    {
        dst[i + 0] = srcMatrix[i + 0];
        dst[i + 1] = srcMatrix[i + 1];
        dst[i + 2] = srcMatrix[i + 2];
        dst[i + 3] = srcMatrix[i + 3];
    }

    // If bApplyInit is true, free previous resources? (call to 0x56c640)
    if (bApplyInit)
    {
        FUN_0056c640(); // Possibly memFree or releaseRef
    }

    // Call engine update for this node (e.g., notify matrix changed)
    FUN_00423900(); // likely EARSNode::onTransformChanged()

    // If the engine's initialization flag is not set (e.g., not in multiplayer/game world?)
    // then call a secondary copy/method
    // The check dereferences FS:0x2c to get TEB, then reads a global offset +0x34
    if (*(int *)(**(int **)(__readfsdword(0x2c) + 0x34)) == 0)
    {
        FUN_00422c50(this, reinterpret_cast<const float *>(srcMatrix), bApplyInit); // alternative path
    }
}