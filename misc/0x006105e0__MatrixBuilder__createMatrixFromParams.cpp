// FUNC_NAME: MatrixBuilder::createMatrixFromParams
// Function at 0x006105e0: Allocates and initializes a 4x4 matrix (16 floats) using constant globals and four parameters.

extern float CONST_FLOAT_ONE;   // DAT_00e2eff4
extern float CONST_FLOAT_ZERO;  // DAT_00e2b1a4

// Internal allocator: first arg = count, second = size, returns 16-byte aligned block
void* __fastcall earsAllocate(uint count, uint size);
// Post‑initialization hook (likely increments refcount or sets up vtable)
void earsPostConstruct(void* ptr);

void createMatrixFromParams(float a, float b, float c, float d)
{
    float* matrix = (float*)earsAllocate(0xd, 4);  // 13 * 4 = 52 bytes, but writes 16 floats? Possibly over‑allocated or index mis‑analysis.
    // We treat as 4x4 matrix (16 floats) – the alloc probably gives more.
    if (matrix == nullptr) return;

    // Fill the matrix with constant identity values and parameters.
    // Offsets in bytes (assuming float[4][4] row‑major):
    // +0x00: row0 col0
    // +0x04: row0 col1
    // +0x08: row0 col2
    // +0x0C: row0 col3
    // +0x10: row1 col0 ...
    matrix[0]  = CONST_FLOAT_ONE;   // +0x00
    matrix[1]  = CONST_FLOAT_ZERO;  // +0x04
    matrix[2]  = a;                 // +0x08
    matrix[3]  = c;                 // +0x0C
    matrix[4]  = CONST_FLOAT_ZERO;  // +0x10
    matrix[5]  = CONST_FLOAT_ZERO;  // +0x14
    matrix[6]  = b;                 // +0x18
    matrix[7]  = c;                 // +0x1C
    matrix[8]  = CONST_FLOAT_ZERO;  // +0x20
    matrix[9]  = CONST_FLOAT_ONE;   // +0x24
    matrix[10] = b;                 // +0x28
    matrix[11] = d;                 // +0x2C
    matrix[12] = CONST_FLOAT_ONE;   // +0x30
    matrix[13] = CONST_FLOAT_ONE;   // +0x34
    matrix[14] = a;                 // +0x38
    matrix[15] = d;                 // +0x3C

    earsPostConstruct(matrix);
}