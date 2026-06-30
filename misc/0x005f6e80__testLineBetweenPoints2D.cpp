// FUNC_NAME: testLineBetweenPoints2D
// Function address: 0x005f6e80
// Role: Wrapper that extracts x and z components from two 3D points (ignoring y) and delegates to FUN_005f6ee0
// Assumes point structures have floats at offsets: +0x00 = x, +0x04 = y, +0x08 = z

extern void FUN_005f6ee0(/* unknown */);

void testLineBetweenPoints2D(undefined4 *pointA, undefined4 *pointB,
                             undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Extract points: x at [0], z at [2] (skipping y at [1])
    undefined4 local_vars[4]; // layout: [0]=x2, [1]=z2, [2]=x1, [3]=z1? see assignments
    undefined4 local_x2, local_z2, local_x1, local_z1; // more explicit

    uint32_t* p = (uint32_t*)pointA;
    uint32_t x1 = p[0];   // +0x00
    uint32_t z1 = p[2];   // +0x08

    p = (uint32_t*)pointB;
    uint32_t x2 = p[0];   // +0x00
    uint32_t z2 = p[2];   // +0x08

    // Place them on stack exactly as decompiled: x2, z2, x1, z1
    local_vars[0] = x2;   // local_18
    local_vars[1] = z2;   // local_14
    local_vars[2] = x1;   // local_10
    local_vars[3] = z1;   // local_c

    // Call the target function with pointers to local_10 and local_18
    FUN_005f6ee0(&local_vars[2], &local_vars[0], param3, param4, param5);

    return;
}