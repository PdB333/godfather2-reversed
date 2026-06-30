// FUNC_NAME: NPCAnimComponent::updateAnimationBlendWeights
void NPCAnimComponent::updateAnimationBlendWeights() {
    int* piVar1;
    char cVar2;
    int iVar3;
    uint uVar4;
    int iVar5;
    float unaff_EBX; // blend weight accumulator
    int unaff_EDI; // this
    float fVar6;
    float fVar7;
    float fVar8; // animation ID from +0x1c8
    float fStack_1c; // blended parameter
    uint local_18; // dummy for calling convention
    float fStack_14;
    float fStack_10;
    float afStack_c[3]; // array for blend inputs

    // This->offset 600 (0x258) might be some constant or part of a vtable
    local_18 = *(undefined4*)(this + 600);
    // If state at +0x484 is zero, no animation
    if (*(int*)(this + 0x484) == 0) {
        return;
    }
    fVar8 = *(float*)(this + 0x1c8); // animation ID
    if ((int)fVar8 < 0) {
        return;
    }
    // Check if this animation is valid via vtable call (index 0x94)
    cVar2 = (**(code**)(*DAT_01223510 + 0x94))(fVar8, (int*)(this + 500));
    if (cVar2 == '\0') {
        return;
    }
    // +500 seems to be a counter or list size
    if (*(int*)(this + 500) < 1) {
        // If no items in list and state is 3 (maybe "blending out"), finish animation
        if (*(int*)(this + 0x484) == 3) {
            FUN_005e9520(); // likely finalize/blend out
        }
        return;
    }

    fStack_1c = *(float*)(this + 0x25c); // some initial blend weight
    local_18 = 0;
    if (*(char*)(this + 0x239) == '\0') {
        // First branch: simple blending, no secondary modifier
        (**(code**)(*DAT_01223510 + 0x78))(*(undefined4*)(this + 0x1c8), 0);
        afStack_c[0] = 0.0;
        fStack_10 = 0.0;
        cVar2 = FUN_005dcb60(DAT_01223508, *(undefined4*)(this + 0x24c));
        if (cVar2 != '\0') {
            // Probably multiply some weight by a factor
            unaff_EBX = afStack_c[0] * unaff_EBX;
            fStack_1c = fStack_10 * fStack_1c;
        }
        FUN_005dcc40(DAT_01223508, &local_18);
    } else {
        // Second branch: secondary modifier (e.g., aim, twist)
        fStack_14 = 0.0;
        fStack_10 = 0.0;
        afStack_c[0] = DAT_00e2b1a4; // often 1.0
        cVar2 = FUN_005e5270(this + 0x238, this + 0x47c, &fStack_14, &fStack_10, afStack_c, &local_18);
        fVar7 = fStack_14;
        if (cVar2 != '\0') {
            // Scale animation speed by factor
            (**(code**)(*DAT_01223510 + 0x78))(*(undefined4*)(this + 0x1c8), DAT_011274e8 * fStack_10);
            fStack_1c = afStack_c[0] * fStack_1c;
            unaff_EBX = fVar7;
        }
    }

    if (*(char*)(this + 0x285) == '\0') {
        // No blend override active
        if (*(int*)(this + 0x484) == 3) {
            // State 3: blending out, check if enough time has passed
            iVar5 = *(int*)(DAT_01223518 + 8) - *(int*)(this + 0x204);
            fVar7 = (float)*(int*)(this + 0x1b8);
            if ((fVar7 < DAT_00e44598) || (*(int*)(this + 0x1b8) <= iVar5)) {
                FUN_005e9520();
            } else {
                *(float*)(this + 0x1d8) = DAT_00e2b1a4 - (float)iVar5 / fVar7;
            }
        }
    } else if (-1 < *(int*)(this + 0x1cc)) {
        // Blend override: use custom duration
        iVar5 = (int)(*(float*)(this + 0x21c) * DAT_00e2e230);
        *(int*)(this + 0x1b8) = iVar5;
        fVar7 = DAT_00e2b1a4;
        if (0 < iVar5) {
            if (*(char*)(this + 0x286) == '\0') {
                // First time: start blending
                cVar2 = (**(code**)(*DAT_01223510 + 0x90))(*(int*)(this + 0x1cc));
                iVar5 = DAT_01223518;
                if (cVar2 != '\0') {
                    *(undefined1*)(this + 0x286) = 1;
                    *(undefined4*)(this + 0x204) = *(undefined4*)(iVar5 + 8);
                }
                goto LAB_005e8cac;
            }
            iVar3 = *(int*)(DAT_01223518 + 8) - *(int*)(this + 0x204);
            if ((iVar3 < iVar5) && (DAT_00e44598 <= (float)iVar5)) {
                *(float*)(this + 0x1d8) = (float)iVar3 / (float)iVar5;
                goto LAB_005e8cac;
            }
        }
        // Blend complete
        *(float*)(this + 0x1d8) = DAT_00e2b1a4;
        *(float*)(this + 0x1dc) = fVar7;
        *(undefined1*)(this + 0x285) = 0;
        *(undefined1*)(this + 0x286) = 0;
    }

LAB_005e8cac:
    // Clamp blend weight to [0,1]
    fVar6 = *(float*)(this + 0x1d8) * unaff_EBX;
    fVar7 = DAT_00e2b1a4;
    if ((DAT_00e2b1a4 < fVar6) || (fVar7 = 0.0, fVar6 < 0.0)) {
        fVar6 = fVar7;
    }
    fVar7 = fVar6;

    // Apply blend to animation system
    (**(code**)(*DAT_01223510 + 0x6c))(*(undefined4*)(this + 0x1c8)); // virtual 0x6c: probably set playback
    (**(code**)(*DAT_01223510 + 0x84))(*(undefined4*)(this + 0x1c8), fVar6); // virtual 0x84: set blend weight

    uVar4 = *(undefined4*)(this + 0x24c);
    if ((*(byte*)(this + 0x250) & 4) != 0) {
        uVar4 = DAT_012056c0; // override parameter
    }

    // Update animation parameter (e.g., speed or direction)
    cVar2 = FUN_005de7e0(DAT_01223508, uVar4, &fStack_1c);
    // virtual 0x88: set parameter
    if ((cVar2 != '\0') && (*(float*)(this + 0x1e0) != fStack_1c)) {
        *(float*)(this + 0x1e0) = fStack_1c;
        fVar6 = (float)(int)fStack_1c;
        if ((int)fStack_1c < 0) {
            fVar6 = fVar6 + DAT_00e44578;
        }
        (**(code**)(*DAT_01223510 + 0x88))(*(undefined4*)(this + 0x1c8), fVar6);
    }

    // Store the final blend for later use
    *(float*)(this + 0x1ec) = fVar7;

    // Update integer fields (e.g., play rate or position)
    iVar5 = (int)(fVar8 * DAT_00e445e0);
    if ((*(int*)(this + 0x1e4) != iVar5) &&
        (cVar2 = (**(code**)(*DAT_01223510 + 0x70))(*(undefined4*)(this + 0x1c8), iVar5),
         cVar2 != '\0')) {
        *(int*)(this + 0x1e4) = iVar5;
    }

    iVar5 = (int)(*(float*)(this + 0x260) * DAT_00e445e0);
    if ((*(int*)(this + 0x1e8) != iVar5) &&
        (cVar2 = (**(code**)(*DAT_01223510 + 0x74))(*(undefined4*)(this + 0x1c8), iVar5),
         cVar2 != '\0')) {
        *(int*)(this + 0x1e8) = iVar5;
    }
    return;
}