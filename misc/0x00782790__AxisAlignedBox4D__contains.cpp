// FUNC_NAME: AxisAlignedBox4D::contains
// Function at 0x00782790: Checks if a 4D point (array of 4 floats) is inside this axis-aligned bounding box.
// The bounding box stores min and max for 4 dimensions, each as float pairs at:
//   +0x74: min X, +0x78: max X
//   +0x7c: min Y, +0x80: max Y
//   +0x84: min Z, +0x88: max Z
//   +0x8c: min W, +0x90: max W
// Returns 1 if point is inside (inclusive of boundaries), 0 otherwise.

bool __thiscall AxisAlignedBox4D::contains(const float* point) const
{
    // Compare each component of the point to the corresponding min/max
    if (point[0] < m_minX || point[0] > m_maxX)
        return false;
    if (point[1] < m_minY || point[1] > m_maxY)
        return false;
    if (point[2] < m_minZ || point[2] > m_maxZ)
        return false;
    if (point[3] < m_minW || point[3] > m_maxW)
        return false;
    return true;
}