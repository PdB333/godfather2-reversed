// FUNC_NAME: componentWiseMultiplyPreservingW
void __fastcall componentWiseMultiplyPreservingW(float* output, float* vectorA, float* vectorB)
{
    // Performs component-wise multiplication of two 4-element vectors.
    // Only the first three components (x, y, z) are updated in output.
    // The fourth component (w) of output is preserved unchanged.
    
    float ax = vectorA[0];
    float ay = vectorA[1];
    float az = vectorA[2];
    float aw = vectorA[3];
    
    float bx = vectorB[0];
    float by = vectorB[1];
    float bz = vectorB[2];
    float bw = vectorB[3];
    
    float outW = output[3]; // Save original w component
    
    output[0] = ax * bx;
    output[1] = ay * by;
    output[2] = az * bz;
    output[3] = aw * bw;  // Compute product for w, but then overwritten below
    
    output[3] = outW;     // Restore original w component, effectively ignoring the w product
}