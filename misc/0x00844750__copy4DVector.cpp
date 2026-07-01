// FUNC_NAME: copy4DVector
// Address: 0x00844750
// Role: Copies 4 consecutive 32-bit values (16 bytes) from source to destination.
// Likely used for 4D vectors (e.g., quaternions, colors) or 4-element structs.
void __cdecl copy4DVector(float* src, float* dst) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}