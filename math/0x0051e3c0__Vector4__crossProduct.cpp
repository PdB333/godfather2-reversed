// FUNC_NAME: Vector4::crossProduct
void __thiscall Vector4::crossProduct(const float* other, float* result) const
{
    float thisX = this[0];
    float thisY = this[1];
    float thisZ = this[2];
    float thisW = this[3];
    float otherX = other[0];
    float otherY = other[1];
    float otherZ = other[2];
    float otherW = other[3];
    result[0] = thisY * otherZ - thisZ * otherY;  // cross product x: y*oz - z*oy
    result[1] = thisZ * otherX - thisX * otherZ;  // cross product y: z*ox - x*oz
    result[2] = thisX * otherY - thisY * otherX;  // cross product z: x*oy - y*ox
    result[3] = 0.0f;                              // w component always zero for 3D cross product
}