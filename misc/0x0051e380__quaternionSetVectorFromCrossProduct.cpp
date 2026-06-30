// FUNC_NAME: quaternionSetVectorFromCrossProduct
void __fastcall quaternionSetVectorFromCrossProduct(float* outQuat, float* quatA, float* quatB)
{
    float ax = quatA[0]; // +0x00: x component
    float ay = quatA[1]; // +0x04: y component
    float az = quatA[2]; // +0x08: z component
    float aw = quatA[3]; // +0x0C: scalar w

    float bx = quatB[0]; // +0x00
    float by = quatB[1]; // +0x04
    float bz = quatB[2]; // +0x08
    float bw = quatB[3]; // +0x0C

    float outW = outQuat[3]; // preserve original scalar of output quaternion

    // Compute cross product of vector parts (vA × vB) and store in output's vector
    outQuat[0] = by * az - bz * ay;
    outQuat[1] = bz * ax - bx * az;
    outQuat[2] = bx * ay - by * ax;
    outQuat[3] = outW; // scalar unchanged
}