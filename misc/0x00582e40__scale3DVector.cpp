// FUNC_NAME: scale3DVector
void __fastcall scale3DVector(float *dest, float *src, float scale) {
    dest[0] = scale * src[0];
    dest[1] = scale * src[1];
    dest[2] = scale * src[2];
    // Overwrite w component with a global constant (likely 1.0f or 0.0f)
    dest[3] = DAT_00e2b1a4; // Typically w = 1.0f for 3D vector scaling
}