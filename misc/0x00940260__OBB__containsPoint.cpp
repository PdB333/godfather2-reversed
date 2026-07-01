// FUNC_NAME: OBB::containsPoint
// Function address: 0x00940260
// Checks if a point is inside an oriented bounding box (OBB).
// OBB structure: minCorner (3 floats), maxCorner (3 floats), three axis normals (9 floats).
// Offsets: +0x00 minCorner, +0x0C maxCorner, +0x18 axis0, +0x24 axis1, +0x30 axis2.

bool __thiscall OBB::containsPoint(const float* point) const
{
    float dxMin = point[0] - this->minCorner[0];
    float dyMin = point[1] - this->minCorner[1];
    float dzMin = point[2] - this->minCorner[2];

    float dxMax = point[0] - this->maxCorner[0];
    float dyMax = point[1] - this->maxCorner[1];
    float dzMax = point[2] - this->maxCorner[2];

    // Check against the three planes through the min corner (outward normals)
    if ((this->axis0[0] * dxMin + this->axis0[1] * dyMin + this->axis0[2] * dzMin <= 0.0f) &&
        (this->axis1[0] * dxMin + this->axis1[1] * dyMin + this->axis1[2] * dzMin <= 0.0f) &&
        (this->axis2[0] * dxMin + this->axis2[1] * dyMin + this->axis2[2] * dzMin <= 0.0f))
    {
        // Check against the three planes through the max corner (inward normals, i.e., opposite direction)
        if ((this->axis0[0] * dxMax + this->axis0[1] * dyMax + this->axis0[2] * dzMax >= 0.0f) &&
            (this->axis1[0] * dxMax + this->axis1[1] * dyMax + this->axis1[2] * dzMax >= 0.0f) &&
            (this->axis2[0] * dxMax + this->axis2[1] * dyMax + this->axis2[2] * dzMax >= 0.0f))
        {
            return true;
        }
    }
    return false;
}