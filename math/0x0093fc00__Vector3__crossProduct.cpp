// FUNC_NAME: Vector3::crossProduct
void __fastcall Vector3::crossProduct(float *outResult, float *vec1, float *vec2)
{
    float x1 = vec1[0];
    float y1 = vec1[1];
    float z1 = vec1[2];
    float w1 = vec1[3]; // unused component (e.g. w in quaternion)
    
    float x2 = vec2[0];
    float y2 = vec2[1];
    float z2 = vec2[2];
    float w2 = vec2[3]; // unused component
    
    float oldW = outResult[3]; // preserve original w component
    
    // Cross product: out = vec1 x vec2
    outResult[0] = y1 * z2 - z1 * y2;   // x = y1*z2 - z1*y2
    outResult[1] = z1 * x2 - x1 * z2;   // y = z1*x2 - x1*z2
    outResult[2] = x1 * y2 - y1 * x2;   // z = x1*y2 - y1*x2
    outResult[3] = w2 * w1 - w2 * w1;   // w = w2*w1 - w2*w1 (always zero, then restored)
    outResult[3] = oldW;                 // restore original w component
}