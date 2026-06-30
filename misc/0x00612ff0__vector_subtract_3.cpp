// FUNC_NAME: vector_subtract_3
void __fastcall vectorSubtract3(float* out, const float* a, const float* b) // out in EAX, a in EDX, b on stack (param_3)
{
    // Load b components
    float by = b[1];
    float bz = b[2];
    float bw = b[3];
    // Load a components
    float ay = a[1];
    float az = a[2];
    float aw = a[3];
    // Save original out.w
    float origW = out[3];
    // Perform component-wise subtraction (x,y,z) only; w is restored later
    out[0] = a[0] - b[0];
    out[1] = ay - by;
    out[2] = az - bz;
    out[3] = aw - bw; // This is overwritten below, effectively preserving w
    out[3] = origW;   // Restore original w component
    return;
}