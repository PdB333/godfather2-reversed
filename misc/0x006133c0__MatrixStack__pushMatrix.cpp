// FUNC_NAME: MatrixStack::pushMatrix
// Function at 0x006133c0 pushes a 4x4 matrix (16 floats, 0x40 bytes) onto a fixed-size stack of 8 matrices.
// Parameters: 
//   ecx - source matrix (const float*)
//   edx - pointer to current stack count (int*)
//   stack - pointer to stack buffer base (float*)
// If count < 8, copies the matrix to stack[count] and increments count.

struct MatrixStack {
    static const int kMaxMatrices = 8;
    static const int kMatrixSize = 16; // 4x4 float matrix (64 bytes)
};

void __fastcall MatrixStack::pushMatrix(const float* source, int* count, float* stack) {
    if (*count < 8) {
        // Destination offset: count * 16 floats
        float* dest = stack + (*count * 16);

        // Copy 16 floats (64 bytes) from source to dest
        for (int i = 0; i < 16; ++i) {
            dest[i] = source[i];
        }

        // Increment stack count
        *count = *count + 1;
    }
    // If stack is full (count >= 8), do nothing
}