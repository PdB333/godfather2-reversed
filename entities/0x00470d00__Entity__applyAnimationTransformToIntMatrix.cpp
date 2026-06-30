// FUNC_NAME: Entity::applyAnimationTransformToIntMatrix
// Address: 0x00470d00
// Role: Takes a 4x4 input matrix (float, row-major), scales the x/y/z components
//       of rows 0-2 by internal scale factors, stores result as integers into a
//       member matrix, zeros the w components of rows 0-2, sets row3.w to a global
//       constant, then triggers a virtual update method.

void __thiscall Entity::applyAnimationTransformToIntMatrix(int *this, float *inputMatrix)
{
    // Internal scale factors stored as floats at offsets +0x134, +0x138, +0x13C
    float scaleX = *(float *)&this[0x4d]; // +0x134
    float scaleY = *(float *)&this[0x4e]; // +0x138
    float scaleZ = *(float *)&this[0x4f]; // +0x13C

    // Copy input 4x4 matrix (16 floats) into local array
    float local[16];
    float *src = inputMatrix;
    float *dst = local;
    for (int i = 0; i < 16; i++) {
        *dst++ = *src++;
    }

    // Scale the x,y,z components of the first three rows
    local[0] *= scaleX; // row0.x
    local[1] *= scaleY; // row0.y
    local[2] *= scaleZ; // row0.z
    local[4] *= scaleX; // row1.x
    local[5] *= scaleY; // row1.y
    local[6] *= scaleZ; // row1.z
    local[8] *= scaleX; // row2.x
    local[9] *= scaleY; // row2.y
    local[10] *= scaleZ;// row2.z

    // Store as truncated integers into member int matrix at +0xD0 (offset 0x34)
    this[0x34] = (int)local[0];  // row0.x
    this[0x35] = (int)local[1];  // row0.y
    this[0x36] = (int)local[2];  // row0.z
    this[0x37] = (int)local[3];  // row0.w
    this[0x38] = (int)local[4];  // row1.x
    this[0x39] = (int)local[5];  // row1.y
    this[0x3a] = (int)local[6];  // row1.z
    this[0x3b] = (int)local[7];  // row1.w
    this[0x3c] = (int)local[8];  // row2.x
    this[0x3d] = (int)local[9];  // row2.y
    this[0x3e] = (int)local[10]; // row2.z
    this[0x3f] = (int)local[11]; // row2.w
    this[0x40] = (int)local[12]; // row3.x
    this[0x41] = (int)local[13]; // row3.y
    this[0x42] = (int)local[14]; // row3.z
    this[0x43] = (int)local[15]; // row3.w (will be overwritten below)

    // Force w components of first three rows to zero (affine transformation)
    this[0x37] = 0; // row0.w
    this[0x3b] = 0; // row1.w
    this[0x3f] = 0; // row2.w

    // Set row3.w to a global constant (likely 1.0f as integer)
    this[0x43] = DAT_00e2b1a4;

    // Unknown helper call (possibly matrix normalization or validation)
    FUN_006101b0();

    // Virtual method call at vtable offset 0x68 (e.g., markDirty, sendUpdate)
    (*(void (**)(void))(*this + 0x68))();

    return;
}