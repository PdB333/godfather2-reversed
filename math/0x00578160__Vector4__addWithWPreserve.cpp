// FUNC_NAME: Vector4::addWithWPreserve
void __fastcall Vector4::addWithWPreserve(float *thisOut, float *vecA, float *vecB)
{
    // Adds two 4-component vectors but preserves the W component of the output
    // thisOut[0..3] = vecA[0..3] + vecB[0..3], then thisOut[3] = original thisOut[3]
    float aY = vecA[1];
    float aZ = vecA[2];
    float aW = vecA[3];
    float bY = vecB[1];
    float bZ = vecB[2];
    float bW = vecB[3];
    float outW = thisOut[3]; // save original W

    thisOut[0] = vecA[0] + vecB[0];
    thisOut[1] = aY + bY;
    thisOut[2] = aZ + bZ;
    thisOut[3] = aW + bW;
    thisOut[3] = outW; // restore original W (overrides the sum)
}