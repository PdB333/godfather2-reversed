// FUNC_NAME: Matrix4x4::setIdentity
// Function address: 0x00844a40
// Purpose: Initializes a 4x4 row-major matrix to identity (diagonal = 1.0)
// The global _DAT_00d5780c is the float constant 1.0f.

void Matrix4x4::setIdentity()
{
    const float identity = 1.0f; // from _DAT_00d5780c

    // Row 0
    m[0] = identity;  // (0,0)
    m[1] = 0;         // (0,1)
    m[2] = 0;         // (0,2)
    m[3] = 0;         // (0,3)

    // Row 1
    m[4] = 0;         // (1,0)
    m[5] = identity;  // (1,1)
    m[6] = 0;         // (1,2)
    m[7] = 0;         // (1,3)

    // Row 2
    m[8] = 0;         // (2,0)
    m[9] = 0;         // (2,1)
    m[10] = identity; // (2,2)
    m[11] = 0;        // (2,3)

    // Row 3
    m[12] = 0;        // (3,0)
    m[13] = 0;        // (3,1)
    m[14] = 0;        // (3,2)
    m[15] = identity; // (3,3)
}