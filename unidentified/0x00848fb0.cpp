// FUN_00848fb0: Entity::clamp2DVector

// Clamps the first (x) and third (z) components of a 3‑element float vector
// (presumably position or velocity) to the min/max bounds stored in this object.
// Offsets:
//   +0x00A0 : minX
//   +0x00A4 : maxX
//   +0x00A8 : minZ
//   +0x00AC : maxZ
// The y component (vec[1]) is not affected.
void __thiscall Entity::clamp2DVector(float *vec)
{
    // Clamp x component
    float minX = *(float *)(this + 0xa0);
    if (vec[0] <= minX && minX != vec[0]) {
        vec[0] = minX;
    }
    float maxX = *(float *)(this + 0xa4);
    if (maxX < vec[0]) {
        vec[0] = maxX;
    }

    // Clamp z component
    float minZ = *(float *)(this + 0xa8);
    if (vec[2] <= minZ && minZ != vec[2]) {
        vec[2] = minZ;
    }
    float maxZ = *(float *)(this + 0xac);
    if (maxZ < vec[2]) {
        vec[2] = maxZ;
    }
}