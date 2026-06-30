// FUNC_NAME: getWorldTransformOrAABB
void __thiscall getWorldTransformOrAABB(int this, int param2, uint32 *param3, uint32 *param4) {
    // locals for temporary transform data (two 4-vectors)
    // initialized to identity-like: first vector (0,0,0,1), second vector (0,0,0,1)
    uint32 local_30 = 0; // +0x00 of first vector (x)
    uint32 local_2c = 0; // +0x04 (y)
    uint32 local_28 = 0; // +0x08 (z)
    uint32 local_24 = DAT_00e2b1a4; // +0x0c (w = 1.0f)

    uint32 local_20 = 0; // +0x10 of second vector (x)
    uint32 local_1c = 0; // +0x14 (y)
    uint32 local_18 = 0; // +0x18 (z)
    uint32 local_14 = DAT_00e2b1a4; // +0x1c (w = 1.0f)

    // Check if child transform object exists at offset 0x218
    if (*(int*)(this + 0x218) != 0) {
        // Call virtual function at vtable offset 0x18 on the child object.
        // This likely fills the local arrays with actual transform data (e.g., position and rotation).
        (**(code **)(**(int **)(this + 0x218) + 0x18))();

        // Write output to param3 and param4 (decompiled pattern retained for correctness)
        *param3 = param2;                           // store identifier
        param3[1] = (uint32)&local_30;              // store pointer to first vector
        param3[2] = local_30;                       // x of first vector
        param3[3] = local_2c;                       // y of first vector

        *param4 = local_28;                         // z of first vector
        param4[1] = local_24;                       // w of first vector
        param4[2] = local_20;                       // x of second vector
        param4[3] = local_1c;                       // y of second vector
    }
    // If no child, outputs are left unchanged (return without writing)
}