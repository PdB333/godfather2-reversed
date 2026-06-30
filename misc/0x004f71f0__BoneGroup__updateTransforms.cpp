// FUNC_NAME: BoneGroup::updateTransforms
undefined4* BoneGroup::updateTransforms(undefined4* thisPtr, int skeleton, int poseData)
{
    byte bVar1;
    int iVar2;
    int iVar3;
    bool bUseDefault;
    char cVar5;
    undefined1 uVar6;
    int *piVar7;
    undefined4 *puVar8;
    undefined4 *puVar9;
    uint uVar10;
    int *piVar11;
    int unaff_FS_OFFSET;
    int *local_64;
    undefined4 *local_60;
    undefined4 local_5c;
    uint uStack_54;
    undefined4 uStack_50; // 16-byte aligned buffers for bone matrices
    undefined4 uStack_4c;
    undefined4 uStack_48;
    undefined4 uStack_44;
    undefined4 uStack_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined4 uStack_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;
    
    BoneGroup::initBase();  // base initialization (FUN_00533cc0)
    thisPtr[0] = &gBoneGroupVtable;  // +0x00 vtable pointer
    if (*(char *)(skeleton + 0xd) != '\0') {
        return thisPtr;
    }
    iVar2 = *(int *)(thisPtr[1] + 0xc4);  // offset 4 -> +0xc4 => skeleton bone pointer
    if (iVar2 == 0) {
        local_64 = (int *)0x0;
    }
    else {
        local_64 = (int *)(iVar2 + -0x48);  // adjust to parent bone node
    }
    iVar2 = *(int *)(thisPtr[1] + 0x20);  // +0x20 => bone resource handle
    local_5c = 0xffffffff;
    uVar6 = 1;
    bUseDefault = false;
    if (iVar2 != 0) {
        *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1;  // reference count increment
    }
    piVar7 = (int *)BoneGroup::getBoneResource(iVar2);  // FUN_004f76d0 - get bone data
    local_60 = (undefined4 *)0x0;
    if (piVar7 == (int *)0x0) {
        // Thread-local storage access: retrieve flags for this bone index
        uVar10 = *(uint *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + thisPtr[4]); // +0x10 bone index
        if ((uVar10 & 0x40) == 0) {
            if ((uVar10 & 4) == 0) {
                local_64 = (int *)0x0;
            }
            else {
                local_5c = *(undefined4 *)(thisPtr[1] + 0xb8);  // fallback animation
            }
        }
        else {
            BoneGroup::handleGeneralError();  // FUN_00533fb0
            local_64 = (int *)0x0;
        }
    }
    else {
        cVar5 = (**(code **)(*piVar7 + 0x14))();  // vfunc 0x14: isLoaded?
        if (cVar5 == '\0') {
            *(undefined1 *)(skeleton + 0xc) = 1;
            return thisPtr;
        }
        if (piVar7[5] == 0) {
            local_64 = (int *)0x0;
        }
        else {
            local_64 = (int *)(piVar7[5] + -0x48);  // parent bone
        }
        local_5c = (**(code **)(*piVar7 + 0x34))();  // vfunc 0x34: get time offset
        uVar6 = (**(code **)(*piVar7 + 0x1c))();      // vfunc 0x1c: get blend weight
        puVar8 = (undefined4 *)(**(code **)(*piVar7 + 0x28))();  // vfunc 0x28: get relative matrix
        puVar9 = (undefined4 *)(**(code **)(*piVar7 + 0x2c))();  // vfunc 0x2c: get absolute matrix
        if ((((float)piVar7[0x28] < *(float *)(poseData + 0xac)) && (puVar9 != (undefined4 *)0x0)) ||
           (puVar9 = puVar8, puVar8 != (undefined4 *)0x0)) {
            local_60 = puVar9;
            if (local_60 != (undefined4 *)0x0) goto LAB_004f7394;
        }
        else {
            bUseDefault = true;
        }
    }
    // Build 16-byte bone matrices from pose data based on animation index
    uVar10 = (uint)*(char *)(poseData + 0x47);  // pose->animationIndex
    if (uVar10 == 3) {
        uVar10 = BoneGroup::getRandomValue() % 3;  // FUN_004e9200 -> get random for variation
    }
    iVar2 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);  // base address for bone data table
    iVar3 = thisPtr[4];
    puVar9 = (undefined4 *)((uVar10 + 5) * 0x10 + iVar3 + iVar2);
    uStack_50 = *puVar9;           // copy first matrix (or quaternion) from table slot (uVar10+5)
    uStack_4c = puVar9[1];
    uStack_48 = puVar9[2];
    uStack_44 = puVar9[3];
    uVar10 = 0x21 >> ((char)uVar10 * '\x04' & 0x1fU) & 0xf;  // compute next slot index via lookup table
    puVar9 = (undefined4 *)((uVar10 + 5) * 0x10 + iVar3 + iVar2);
    uStack_40 = *puVar9;           // second matrix
    uStack_3c = puVar9[1];
    uStack_38 = puVar9[2];
    uStack_34 = puVar9[3];
    puVar9 = (undefined4 *)(((0x21 >> ((char)uVar10 * '\x04' & 0x1fU) & 0xfU) + 5) * 0x10 + iVar3 + iVar2);
    uStack_30 = *puVar9;           // third matrix
    uStack_2c = puVar9[1];
    uStack_28 = puVar9[2];
    uStack_24 = puVar9[3];
    puVar9 = (undefined4 *)(iVar3 + 0x80 + iVar2);  // slot at index + 0x80 (base offset)
    uStack_20 = *puVar9;           // fourth matrix (identity or default)
    uStack_1c = puVar9[1];
    uStack_18 = puVar9[2];
    uStack_14 = puVar9[3];
LAB_004f7394:
    bVar1 = *(byte *)(poseData + 0x44);  // pose flags
    if (local_64 == (int *)0x0) {
        piVar7 = (int *)0x0;
    }
    else {
        uStack_54 = 0;
        cVar5 = (**(code **)(*local_64 + 0x10))(0x77a210a2, &uStack_54);  // vfunc 0x10: get child by hash
        piVar7 = (int *)(-(uint)(cVar5 != '\0') & uStack_54);
    }
    if (local_60 == (undefined4 *)0x0) {
        if (bUseDefault) {
            local_60 = (undefined4 *)(thisPtr[1] + 0x30);  // use default matrix from skeleton data
        }
        else {
            local_60 = &uStack_50;  // use computed matrix
        }
    }
    if ((piVar7 == (int *)0x0) || ((bVar1 >> 6 & 1) != 0)) {
        BoneGroup::applySingleBoneTransform(*(undefined4 *)(thisPtr[1] + 0x10), poseData, local_5c, uVar6);
    }
    else {
        piVar7 = (int *)(**(code **)(*piVar7 + 0x14c))();  // get child list iterator
        if (piVar7 != (int *)0x0) {
            do {
                if (piVar7 == (int *)0x0) {
                    piVar11 = (int *)0x0;
                }
                else {
                    piVar11 = piVar7 + 0x15;  // offset to child bone struct
                }
                uStack_54 = DAT_01206880;  // some global data
                BoneGroup::applyBoneTransform(*(undefined4 *)(thisPtr[1] + 0x10), poseData, piVar11, local_5c, uVar6, local_60);
                piVar7 = (int *)(**(code **)(*piVar7 + 0x150))();  // next child
            } while (piVar7 != (int *)0x0);
            *(undefined1 *)(skeleton + 0xc) = 1;  // mark skeleton as transformed
            return thisPtr;
        }
    }
    *(undefined1 *)(skeleton + 0xc) = 1;
    return thisPtr;
}