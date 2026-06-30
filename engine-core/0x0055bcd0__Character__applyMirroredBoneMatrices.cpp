// FUNC_NAME: Character::applyMirroredBoneMatrices
void __fastcall Character::applyMirroredBoneMatrices(int *this) {
    // this[0x121] is a flag indicating if mirroring is enabled? Check at offset 0x484
    if (this[0x121] != 0) {
        return; // skip if mirroring not needed
    }

    // local_64 points to an array of 4 bone transform structures (each 12 ints = 48 bytes) at offset 0x3D8
    int *boneTransforms = this + 0xf6; // this->boneTransforms[4]
    // piVar2 points to an array of 4 bone flags (each 40 ints = 160 bytes) at offset 0x520
    int *boneFlags = this + 0x148; // this->boneFlags[4]

    for (uint i = 0; i < 4; i++) {
        // Check if this bone is active: either global mirror flag (this[0x120]) is non-zero or specific flag is non-zero
        if (this[0x120] != 0 || boneFlags[i] != 0) {
            // Virtual call: getBoneWorldMatrix(i, &matrix)
            // matrix is 8 floats: likely a 4x4 matrix (rotation+scale? Actually 8 floats suggests two quaternions or a 4x2? We'll treat as 2x4)
            float matrix[8]; // local_50, fStack_4c, etc.
            (*(void (__thiscall **)(int, uint, float *))(*(int *)this + 0x254))((int)this, i, matrix);

            // If the bone flag indicates mirroring (bit 0 set), apply mirror transform
            if (boneFlags[i] != 0 && (i & 1) != 0) {
                // Mirror along X? Assume DAT_00e44564 is 1.0f or a mirror constant
                // The subtraction from a constant might represent negation or reflection
                matrix[0] = DAT_00e44564 - matrix[0];
                matrix[1] = DAT_00e44564 - matrix[1];
                matrix[2] = DAT_00e44564 - matrix[2];
                matrix[3] = DAT_00e44564 - matrix[3];
                matrix[4] = DAT_00e44564 - matrix[4];
                matrix[5] = DAT_00e44564 - matrix[5];
                matrix[6] = DAT_00e44564 - matrix[6];
                matrix[7] = DAT_00e44564 - matrix[7];
            }

            // If global mirror flag is set, process the matrix further
            if (this[0x120] != 0) {
                // FUN_00aa3930: likely converts quaternion/transform to matrix or applies transformation
                FUN_00aa3930(&matrix);
                // FUN_0055ab30: copies from boneTransforms[-6] (previous bone?) to temp buffer
                // boneTransforms[-2..0] are copied to a temporary structure on stack
                int temp[4]; // auStack_60, but actually 16 bytes (4 ints)
                FUN_0055ab30(temp, boneTransforms - 6);
                // Write back to current bone transform structure
                boneTransforms[-2] = temp[0];
                boneTransforms[-1] = temp[1];
                boneTransforms[0] = temp[2];
                boneTransforms[1] = DAT_00e2b1a4; // Some constant or time stamp
            }
        }
        // Advance to next bone
        boneTransforms += 12; // 12 ints = 48 bytes
        boneFlags += 40;      // 40 ints = 160 bytes
    }
    return;
}