// FUNC_NAME: Math::crossProductQuaternion
void __fastcall Math::crossProductQuaternion(float *outResult, float *vecA, float *vecB)
{
    float ax = *vecA;
    float ay = vecA[1];
    float az = vecA[2];
    float aw = vecA[3];
    float bx = *vecB;
    float by = vecB[1];
    float bz = vecB[2];
    float bw = vecB[3];
    float oldW = outResult[3]; // preserve original w component

    // Cross product of the vector parts (x,y,z) of two quaternions
    *outResult = by * az - bz * ay;          // out.x = by*az - bz*ay
    outResult[1] = bz * ax - bx * az;        // out.y = bz*ax - bx*az
    outResult[2] = bx * ay - by * ax;        // out.z = bx*ay - by*ax
    outResult[3] = bw * aw - bw * aw;        // w component: bw*aw - bw*aw = 0 (then overwritten)
    outResult[3] = oldW;                     // restore original w component
}