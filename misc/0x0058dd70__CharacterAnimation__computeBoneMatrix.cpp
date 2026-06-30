// FUNC_NAME: CharacterAnimation::computeBoneMatrix

int __thiscall CharacterAnimation::computeBoneMatrix(int thisPtr, int characterData, float* outMatrix44, int otherMatrix) {
    float* pfVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    short sVar6;
    int boneIndex; // in_EAX initially
    int iVar7;
    int iVar8;
    int extraout_ECX;
    float fVar9;
    float fVar10;
    char local_50[48]; // temp matrix storage?
    float local_20[4]; // for matrix transformation
    float local_14;

    float const fOne = DAT_00e2b1a4; // 1.0f

    // Get animation node pointer (bone hierarchy)
    int animNode = *(int*)(thisPtr + 0x70);
    // Validate: animNode exists, its array length > 0, and the bone index is within bounds
    if (animNode == 0 || *(int*)(animNode + 0x18) < 1 || *(int*)(animNode + 0x1c) == 0) {
        iVar7 = 0;
    } else {
        sVar6 = *(short*)(thisPtr + 0x76);
        if (sVar6 < 0 || *(int*)(animNode + 0x18) <= (int)sVar6) {
            iVar7 = 0;
        } else {
            iVar7 = *(int*)(animNode + 0x1c) + sVar6 * 0x18; // pointer to bone data
        }
    }

    // Initialize output matrix to identity
    outMatrix44[0] = fOne;
    outMatrix44[1] = 0.0f;
    outMatrix44[2] = 0.0f;
    outMatrix44[3] = 0.0f;
    outMatrix44[4] = 0.0f;
    outMatrix44[5] = fOne;
    outMatrix44[6] = 0.0f;
    outMatrix44[7] = 0.0f;
    outMatrix44[8] = 0.0f;
    outMatrix44[9] = 0.0f;
    outMatrix44[10] = fOne;
    outMatrix44[11] = 0.0f;
    outMatrix44[12] = 0.0f;
    outMatrix44[13] = 0.0f;
    outMatrix44[14] = 0.0f;
    outMatrix44[15] = fOne;

    if (iVar7 != 0 && boneIndex != -1) {
        do {
            // Check character data: animationslot state? / +0x34 is an array of bytes?
            char slotState = *(char*)(*(int*)(characterData + 0x34) + 0x14 + boneIndex);
            if (slotState != '\x02') {
                return 0;
            }

            // Get transform array from character data
            iVar7 = *(int*)(characterData + 0x38);
            iVar8 = boneIndex * 0x20; // each frame data is 0x20 bytes?
            // Read quaternion from the frame data (x,y,z,w at offsets +0x10, +0x14, +0x18, +0x1c)
            fVar2 = *(float*)(iVar7 + 0x1c + iVar8); // w
            fVar3 = *(float*)(iVar7 + 0x18 + iVar8); // z
            fVar4 = *(float*)(iVar7 + 0x10 + iVar8); // x
            fVar5 = *(float*)(iVar7 + 0x14 + iVar8); // y
            pfVar1 = (float*)(iVar7 + 0x10 + iVar8);
            fVar9 = fVar3*fVar3 + fVar2*fVar2 + fVar4*fVar4 + fVar5*fVar5;
            if (fVar9 <= DAT_00e2cbe0) {
                fVar10 = 0.0f;
            } else {
                fVar10 = fOne / SQRT(fVar9);
            }
            // Normalize quaternion
            pfVar1[0] = fVar4 * fVar10;
            pfVar1[1] = fVar5 * fVar10;
            pfVar1[2] = fVar3 * fVar10;
            pfVar1[3] = fVar2 * fVar10;

            // Convert quaternion to matrix (local matrix)
            FUN_0056cef0(pfVar1, local_50); // local_50 is a 4x4 matrix
            local_20[0] = *(float*)(extraout_ECX + 0x10);
            local_20[1] = *(float*)(extraout_ECX + 0x14);
            local_20[2] = *(float*)(extraout_ECX + 0x18);
            local_20[3] = fOne;

            // Possibly combine with parent or identity?
            FUN_0048ee40();

            // Update boneIndex for next iteration (bone skeleton chain?)
            if (*(short*)(thisPtr + 0x74) < 0) {
                boneIndex = -1;
            } else {
                int nextBone = (int)*(short*)(thisPtr + 0x74);
                if (*(int*)(*(int*)(thisPtr + 0x70) + 0x18) <= nextBone || boneIndex < 0) {
                    boneIndex = -1;
                } else {
                    int boneArray = *(int*)(*(int*)(thisPtr + 0x70) + 0x1c);
                    if (*(int*)(boneArray + 8 + nextBone * 0x18) <= boneIndex) {
                        boneIndex = -1;
                    } else {
                        boneIndex = *(int*)(boneIndex * 0x10 + *(int*)(boneArray + nextBone * 0x18 + 0xc));
                    }
                }
            }
        } while (boneIndex != -1);
    }

    // Final combine with otherMatrix
    FUN_0056d530(outMatrix44, otherMatrix);
    return 1;
}