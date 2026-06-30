// FUNC_NAME: Vector4::scaleByDotProduct
void __thiscall Vector4::scaleByDotProduct(float *thisVector, const float *vecA, const float *vecB)
{
    // Reads vecA as a 4-component vector (x,y,z,w) and vecB as 3-component vector (x,y,z)
    // Computes dot product: dot = vecB.x * vecA.x + vecB.y * vecA.y + vecB.z * vecA.z
    // Then stores thisVector.xyz = dot * vecA.xyz, preserving thisVector.w
    float ax = vecA[1];
    float ay = vecA[2];
    float aw = vecA[3];
    float savedW = thisVector[3]; // save original w component

    float dotBxAx = vecB[0] * vecA[0];
    float dotByAy = vecB[1] * ax;
    float dotBzAz = vecB[2] * ay;

    float dot = dotBxAx + dotByAy + dotBzAz;

    thisVector[0] = dot * vecA[0];
    thisVector[1] = dot * ax;
    thisVector[2] = dot * ay;
    thisVector[3] = dot * aw; // this will be overwritten
    thisVector[3] = savedW;   // restore original w
}