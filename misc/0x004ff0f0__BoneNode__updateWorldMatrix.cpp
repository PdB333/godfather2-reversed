// FUNC_NAME: BoneNode::updateWorldMatrix
void BoneNode::updateWorldMatrix(void)
{
    float* pfMat;
    char cTemp;
    int iData;
    int iData2;
    int* piMat;
    int iFlags;
    int iBase;
    int iBoneIdx;
    int iTLS_Base;
    int iZero;
    undefined4 uVar9;
    undefined4 vLocal[4]; // 4 floats at local_60 (for matrix row or quat?)
    undefined4 vRotRow0[4]; // local_50 - copy from bone data
    undefined4 vRotRow1[4]; // local_40
    undefined4 vRotRow2[4]; // local_30
    float fPos[4]; // local_20 (translation)
    float fQuat[4]; // at fStack_14? Actually local_20, fStack_1c, fStack_18, fStack_14

    // Get TLS base (thread local storage)
    iTLS_Base = *(int*)(*(int*)(_FS_OFFSET + 0x2c) + 8); // _FS_OFFSET is Thread Environment Block

    // Get bone data structure pointer
    iData = *(int*)(this + 0x24);
    iBase = iTLS_Base; // likely frame allocator base

    // Allocate output matrix buffer (returns pointer stored at this+0x28)
    iData2 = FUN_004e9310((&DAT_00e2db60)[*(byte*)(iData + 0x6c)], // bone index or parent index? 
                          *(undefined4*)(iData + 0x18),           // ?
                          *(undefined4*)(iData + 0x60),           // ?
                          *(undefined4*)(iData + 0x64),           // ?
                          *(undefined4*)(iData + 0x68),           // ?
                          *(undefined4*)(iData + 0x7c),           // ?
                          *(undefined4*)(iData + 0x80));          // ?
    *(int*)(this + 0x28) = iData2;
    if (iData2 != 0) {
        // Get input transform from bone data offset (this+0x10 is offset into array)
        pfMat = (float*)(iBase + 0x80 + *(int*)(this + 0x10));
        fPos[0] = pfMat[0];
        fPos[1] = pfMat[1];
        fPos[2] = pfMat[2];
        fPos[3] = pfMat[3]; // might be w component (scale or quaternion?)

        iBoneIdx = iBase + *(int*)(this + 0x10); // base + offset
        iFlags = *(int*)(iData + 0x10);
        // Check if 'world' flag is set (bits 1 and 2 cleared means local)
        if ((iFlags & 6) == 0) {
            // Add local translation to input position
            fPos[0] += *(float*)(iData + 0x1c);
            fPos[1] += *(float*)(iData + 0x20);
            fPos[2] += *(float*)(iData + 0x24);
            // fPos[3] unchanged? likely w=1
        }

        if (*(char*)(iData + 0x6c) == '\0') { // No parent? or 'useLocalOnly'
            // Set local matrix (just translation? or identity + translation)
            FUN_004e9440(iData2, &fPos[0]);
        } else {
            if ((iFlags & 0x2000) == 0) {
                // Copy rotation matrix from bone data (3x4? stores 12 floats)
                vRotRow0[0] = *(undefined4*)(iBoneIdx + 0x50);
                vRotRow0[1] = *(undefined4*)(iBoneIdx + 0x54);
                vRotRow0[2] = *(undefined4*)(iBoneIdx + 0x58);
                vRotRow0[3] = *(undefined4*)(iBoneIdx + 0x5c);
                vRotRow1[0] = *(undefined4*)(iBoneIdx + 0x60);
                vRotRow1[1] = *(undefined4*)(iBoneIdx + 0x64);
                vRotRow1[2] = *(undefined4*)(iBoneIdx + 0x68);
                vRotRow1[3] = *(undefined4*)(iBoneIdx + 0x6c);
                vRotRow2[0] = *(undefined4*)(iBoneIdx + 0x70);
                vRotRow2[1] = *(undefined4*)(iBoneIdx + 0x74);
                vRotRow2[2] = *(undefined4*)(iBoneIdx + 0x78);
                vRotRow2[3] = *(undefined4*)(iBoneIdx + 0x7c);
            } else {
                FUN_004fef50(); // compute delta rotation?
                // Note: vRotRow arrays not initialized in this path?
            }

            // Write resulting 4x4 matrix into output buffer
            if (*(int*)(this + 0x28) != 0) {
                undefined4* pOut = (undefined4*)(*(int*)(*(int*)(this + 0x28) + 0x18) + iBase);
                pOut[0] = vRotRow0[0];
                pOut[1] = vRotRow0[1];
                pOut[2] = vRotRow0[2];
                pOut[3] = vRotRow0[3];
                pOut[4] = vRotRow1[0];
                pOut[5] = vRotRow1[1];
                pOut[6] = vRotRow1[2];
                pOut[7] = vRotRow1[3];
                pOut[8] = vRotRow2[0];
                pOut[9] = vRotRow2[1];
                pOut[10] = vRotRow2[2];
                pOut[11] = vRotRow2[3];
                pOut[12] = *(undefined4*)&fPos[0];
                pOut[13] = *(undefined4*)&fPos[1];
                pOut[14] = *(undefined4*)&fPos[2];
                pOut[15] = *(undefined4*)&fPos[3];
            }
        }

        // Handle additional transform (maybe scale or shear)
        if ((*(uint*)(this + 0x3c) & 8) == 0) {
            // Use bone data vector at +0x44 and call FUN_004e94a0
            iData = *(int*)(this + 0x24);
            vLocal[0] = *(undefined4*)(iData + 0x44);
            vLocal[1] = *(undefined4*)(iData + 0x48);
            vLocal[2] = *(undefined4*)(iData + 0x4c);
            vLocal[3] = DAT_00e2b1a4; // constant (0.0f?)
            FUN_004e94a0(vLocal, *(undefined4*)(iData + 0x40)); // set additional transform
        } else {
            // Clear flags and zero out the extra transform
            *(uint*)(this + 0x3c) &= 0xfffffff7;
            vLocal[0] = 0;
            vLocal[1] = 0;
            vLocal[2] = 0;
            vLocal[3] = 0;
            undefined4* pExtra = (undefined4*)(*(int*)(*(int*)(this + 0x28) + 0x18) + 0x40 + iBase);
            pExtra[0] = 0;
            pExtra[1] = 0;
            pExtra[2] = 0;
            pExtra[3] = 0;
            FUN_004aab40(); // clear something?
            uVar9 = 0;
            *(undefined4*)(*(int*)(*(int*)(this + 0x28) + 0x18) + 0x88 + iBase) = 0;
        }

        // Finalize with scale/shear from bone data
        iData = *(int*)(this + 0x24);
        FUN_004e9520(*(undefined4*)(this + 0x28),
                     *(undefined4*)(iData + 0x88),
                     *(undefined4*)(iData + 0x8c),
                     *(undefined4*)(iData + 0x94));

        // Check bone type and possibly update visibility or lod
        piMat = *(int**)(this + 0x24);
        cTemp = (char)piMat[0x1b]; // offset 0x24 + 0x6c = 0x90? Actually piMat+0x1b = byte at this+0x24+0x6c
        iData = 0;
        if ((cTemp == '\x03') || (cTemp == '\x0f') || (cTemp == '\x10')) {
            // Bone types: 3, 15, 16 (maybe root or specific)
            if ((piMat[0] != 0 || piMat[1] != 0) || (piMat[2] != 0 || piMat[3] != 0)) {
                // Check if the quaternion is non-zero and call some validation
                int iResult = FUN_004e9270();
                if (iResult != -1) {
                    iData = 0;
                }
            }
            // Write result to matrix header (maybe a flag)
            *(int*)(*(int*)(*(int*)(this + 0x28) + 0x18) + 0x94 + iBase) = iData;
        }
    }
    return;
}