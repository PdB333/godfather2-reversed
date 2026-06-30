// FUNC_NAME: PlayerAimComponent::updateAimDirection

struct LinkedListNode {
    float data;      // +0x00
    float* next;     // +0x04 (pointer to next node)
};

// Global constants (from data references)
extern const float kPi;        // DAT_00e2afac
extern const float k2Pi;       // DAT_00e2a848
extern const float kHalfPi;    // DAT_00e44564 (0.5*pi)
extern const float kSmallAngle; // DAT_00e44588
extern const float kDistThreshold; // DAT_00e2cbe0
extern const float kOneOverDist;  // DAT_00e2b1a4 (1.0f)
extern const float kSomeFactor;   // DAT_00e2cd54
extern const float kInvFactor;    // DAT_00e44968

// Forward declarations of called functions
void FUN_004daf90(float* node); // Remove node from list
void FUN_005fdf60(float* this, int param); // Initialize something
void FUN_005fe2e0(float* this, float* src, float* dst, int mode); // Transform vector
void FUN_005f5ce0(); // Math utility (maybe cos/sin)
void FUN_00414aa0(); // Some update
void FUN_00b9a9fa(); // Math function (wrap angle?)

void __thiscall PlayerAimComponent::updateAimDirection(
    float* thisPtr,                // param_1
    int* targetObject,             // param_2
    int targetId,                  // param_3 (undefined4)
    float* outDirection,           // param_4
    float* optionalOutDirection,   // param_5
    char useAlternateMode          // param_6
)
{
    float* pfVar1;
    float* pfVar2;
    float* pfVar3;
    int* piVar4;
    float fVar5;
    double dVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;

    // Stack locals for list manipulation
    float fStack_48;
    float fStack_44;
    float fStack_40;
    int iStack_3c;
    float local_38;
    int local_34;      // was undefined4 but used as pointer
    float local_30;
    float local_2c;
    int local_28;      // was undefined4 but used as pointer
    float local_24;
    float fStack_20;
    float fStack_1c;
    float fStack_18;

    pfVar3 = thisPtr + 0x11; // +0x11: float field
    *(unsigned char*)(thisPtr + 0x10) = 0; // clear byte at +0x10
    if (*pfVar3 != 0.0f) {
        FUN_004daf90(pfVar3); // Remove node if non-zero
        *pfVar3 = 0.0f;
    }

    // Save and possibly remove node at +0x1c
    local_2c = thisPtr[0x1c];
    local_28 = 0;
    if (local_2c != 0.0f) {
        local_28 = *(int*)((int)local_2c + 4);
        *(float**)((int)local_2c + 4) = &local_2c;
    }

    local_24 = thisPtr[0x1e];
    local_38 = thisPtr[0x1f];
    local_34 = 0;
    if (local_38 != 0.0f) {
        local_34 = *(int*)((int)local_38 + 4);
        *(float**)((int)local_38 + 4) = &local_38;
    }

    local_30 = thisPtr[0x21];
    FUN_005fdf60(thisPtr, targetId); // Init with target ID

    pfVar3 = (float*)(*(code**)(*targetObject + 0xc))(targetId); // vtable call to get something (maybe a position)
    fVar10 = *pfVar3; // first component of result
    fStack_44 = 0.0f;
    if (fVar10 != 0.0f) {
        fStack_44 = *(float*)((int)fVar10 + 4); // save next pointer
        *(float**)((int)fVar10 + 4) = &fStack_48; // point back to stack for safe removal
    }
    fStack_40 = pfVar3[2]; // third component
    pfVar3 = (float*)(-(uint)(fVar10 != 0.0f) & (uint)fStack_40); // conditionally use fStack_40 as pointer? Actually this is weird: it's masking fStack_40 with sign of fVar10 != 0. But likely a bug in decompilation. Let's keep as is.

    // Clear some orientation vector (offset +0x08 to +0x0b)
    thisPtr[0x0b] = 0.0f;
    thisPtr[0x0a] = 0.0f;
    thisPtr[0x09] = 0.0f;
    thisPtr[0x08] = 0.0f;

    fStack_48 = fVar10; // store the first pointer value

    if (useAlternateMode == '\0') {
        // Direct mode: assign target orientation directly
        FUN_005f5ce0();
        FUN_005f5ce0();
        fVar10 = fStack_48;
        pfVar2 = thisPtr + 0x22; // +0x22: list head for a different node
        if ((pfVar2 != &fStack_48) && (*pfVar2 != fStack_48)) {
            if (*pfVar2 != 0.0f) {
                FUN_004daf90(pfVar2); // remove old
            }
            thisPtr[0x22] = fVar10; // set new
            if (fVar10 != 0.0f) {
                thisPtr[0x23] = *(float*)((int)fVar10 + 4); // copy next?
                *(float**)((int)fVar10 + 4) = thisPtr + 0x22; // link back
            }
        }
        thisPtr[0x24] = fStack_40; // other component
        // Copy output direction
        thisPtr[0x18] = *outDirection;
        thisPtr[0x19] = outDirection[1];
        thisPtr[0x1a] = outDirection[2];
    }
    else {
        // Alternate mode: combine with current orientation (probably gradual turning)
        pfVar2 = thisPtr + 0x1c;
        if ((pfVar2 != &fStack_48) && (*pfVar2 != fVar10)) {
            if (*pfVar2 != 0.0f) {
                FUN_004daf90(pfVar2);
            }
            *pfVar2 = fVar10;
            if (fVar10 != 0.0f) {
                thisPtr[0x1d] = *(float*)((int)fVar10 + 4);
                *(float**)((int)fVar10 + 4) = pfVar2;
            }
        }
        pfVar1 = thisPtr + 0x1f;
        thisPtr[0x1e] = fStack_40;
        if (pfVar1 != pfVar2) {
            fVar10 = *pfVar2;
            if (*pfVar1 != fVar10) {
                if (*pfVar1 != 0.0f) {
                    FUN_004daf90(pfVar1);
                }
                thisPtr[0x1f] = fVar10;
                if (fVar10 != 0.0f) {
                    thisPtr[0x20] = *(float*)((int)fVar10 + 4);
                    *(float**)((int)fVar10 + 4) = thisPtr + 0x1f;
                }
            }
        }
        thisPtr[0x21] = thisPtr[0x1e];
        // Copy from the masked pointer pfVar3
        thisPtr[0x18] = *pfVar3;
        thisPtr[0x19] = pfVar3[1];
        thisPtr[0x1a] = pfVar3[2];
        // Copy back to output
        *outDirection = thisPtr[0x18];
        outDirection[1] = thisPtr[0x19];
        outDirection[2] = thisPtr[0x1a];
        // Transform call
        FUN_005fe2e0(thisPtr, &fStack_48, thisPtr + 0x22, 0);
    }

    FUN_00414aa0(); // general update

    fVar10 = 0.0f;
    thisPtr[0x38] = 0.0f;
    thisPtr[0x30] = 0.0f;
    thisPtr[0x44] = 0.0f;
    thisPtr[0x43] = 0.0f;

    // Check if we have a valid target
    if ((thisPtr[0x22] == 0.0f) || ((pfVar2 = (float*)thisPtr[0x24]) == (float*)0x0)) {
        // No target: set flags to indicate no valid aim
        thisPtr[0x2d] = (float)((uint)thisPtr[0x2d] | 1); // set bit 0 in flags
        thisPtr[0x3f] = 0.0f;
        thisPtr[0x3e] = 0.0f;
        thisPtr[0x3d] = 0.0f;
        thisPtr[0x42] = 0.0f;
        thisPtr[0x41] = 0.0f;
        thisPtr[0x40] = 0.0f;
        goto LAB_006015e9;
    }

    // Compute desired direction vector
    if (useAlternateMode == '\0') {
        local_24 = *pfVar3;
        fStack_20 = pfVar3[1];
        fVar9 = pfVar3[2];
    }
    else {
        local_24 = *pfVar2; // pfVar2 from above (maybe the current direction)
        fStack_20 = pfVar2[1];
        fVar9 = pfVar2[2];
    }

    local_24 = local_24 - *thisPtr; // subtract position? thisPtr[0..2] likely position
    fStack_20 = fStack_20 - thisPtr[1];
    fVar9 = fVar9 - thisPtr[2];
    fStack_18 = fStack_18 - thisPtr[3]; // note: thisPtr[3] might be something else

    fVar7 = fStack_20 * fStack_20 + local_24 * local_24 + fVar9 * fVar9;
    fStack_1c = fVar10;

    if (kDistThreshold < fVar7) {
        fVar10 = sqrtf(fVar7);
        fStack_1c = kOneOverDist / fVar10;
    }

    local_24 = fStack_1c * local_24;
    fStack_20 = fStack_1c * fStack_20;
    fStack_1c = fStack_1c * fVar9;
    dVar6 = (double)local_24;
    thisPtr[0x31] = fVar10; // store distance
    FUN_00b9a9fa(); // presumably something like atan2 or angle wrap
    fVar10 = (float)dVar6;
    thisPtr[0x3f] = fVar10; // yaw angle

    dVar6 = (double)fStack_20;
    FUN_00b9a9fa();
    fVar9 = kHalfPi - (float)dVar6; // pitch? or roll?
    thisPtr[0x42] = fVar9;

    if ((optionalOutDirection == (float*)0x0) || (useAlternateMode != '\0')) {
        // No optional output or in alternate mode -> set angles directly
        thisPtr[0x3e] = fVar10;
        thisPtr[0x3d] = fVar10;
        thisPtr[0x41] = fVar9;
        thisPtr[0x40] = fVar9;
        if (optionalOutDirection != (float*)0x0) {
            *optionalOutDirection = local_24;
            optionalOutDirection[1] = fStack_20;
            optionalOutDirection[2] = fStack_1c;
        }
        goto LAB_006015e9;
    }

    // Otherwise: compute smoothed angles with wrapping
    dVar6 = (double)*optionalOutDirection;
    FUN_00b9a9fa();
    fVar8 = kSmallAngle;
    fVar7 = kPi;
    fVar9 = k2Pi;
    fVar5 = (float)dVar6;
    fVar10 = fVar10 - fVar5;
    thisPtr[0x3e] = fVar5; // previous angle
    if (fVar10 <= fVar7) {
        if (fVar10 < fVar8) {
            fVar10 = fVar10 + fVar9;
        }
    }
    else {
        fVar10 = fVar10 - fVar9;
    }
    fVar5 = fVar5 - fVar10;
    thisPtr[0x3d] = fVar5; // smoothed yaw difference
    if (fVar5 <= fVar7) {
        if (fVar5 < fVar8) {
            fVar5 = fVar5 + fVar9;
            goto LAB_0060147b;
        }
    }
    else {
        fVar5 = fVar5 - fVar9;
LAB_0060147b:
        thisPtr[0x3d] = fVar5;
    }

    dVar6 = (double)optionalOutDirection[1];
    FUN_00b9a9fa();
    fVar9 = kPi;
    fVar8 = kHalfPi - (float)dVar6;
    fVar7 = thisPtr[0x42] - fVar8;
    thisPtr[0x41] = fVar8;
    fVar10 = k2Pi;
    if (fVar7 <= fVar9) {
        if (fVar7 < kSmallAngle) {
            fVar7 = fVar7 + k2Pi;
        }
    }
    else {
        fVar7 = fVar7 - k2Pi;
    }
    fVar8 = fVar8 - fVar7;
    thisPtr[0x40] = fVar8;
    if (fVar8 <= fVar9) {
        if (fVar8 < kSmallAngle) {
            fVar8 = fVar8 + fVar10;
            goto LAB_00601535;
        }
    }
    else {
        fVar8 = fVar8 - fVar10;
LAB_00601535:
        thisPtr[0x40] = fVar8;
    }

    fVar9 = thisPtr[0x31] * kSomeFactor;
    thisPtr[0x3b] = fVar9;
    fVar10 = kInvFactor;
    if (0.0f < fVar9) {
        fVar10 = kOneOverDist / fVar9;
    }
    thisPtr[0x3c] = fVar10;
    thisPtr[0x34] = 0.0f;
    thisPtr[0x35] = 0.0f;
    thisPtr[0x36] = 0.0f;
    thisPtr[0x38] = 2.8026e-45f; // very small float, likely epsilon

LAB_006015e9:
    FUN_005f5ce0(); // another math utility

    // Callback function pointer at offset 0x29
    if ((code*)thisPtr[0x29] != (code*)0x0) {
        (*(code*)thisPtr[0x29])(thisPtr, &local_30, &iStack_3c, thisPtr + 0x1f, thisPtr + 0x22);
    }

    // Restore list links from the saved local pointers earlier
    // Clean up fStack_48
    if (fStack_48 != 0.0f) {
        pfVar3 = *(float**)((int)fStack_48 + 4);
        if (pfVar3 == &fStack_48) {
            *(float*)((int)fStack_48 + 4) = fStack_44;
        }
        else {
            while ((float*)pfVar3[1] != &fStack_48) {
                pfVar3 = (float*)pfVar3[1];
            }
            pfVar3[1] = fStack_44;
        }
    }
    // Clean up iStack_3c
    if (iStack_3c != 0) {
        piVar4 = *(int**)(iStack_3c + 4);
        if (piVar4 == &iStack_3c) {
            *(float*)(iStack_3c + 4) = local_38;
        }
        else {
            while ((int*)piVar4[1] != &iStack_3c) {
                piVar4 = (int*)piVar4[1];
            }
            piVar4[1] = (int)local_38;
        }
    }
    // Clean up local_30
    if (local_30 != 0.0f) {
        pfVar3 = *(float**)((int)local_30 + 4);
        if (pfVar3 == &local_30) {
            *(float*)((int)local_30 + 4) = local_2c;
            return;
        }
        while ((float*)pfVar3[1] != &local_30) {
            pfVar3 = (float*)pfVar3[1];
        }
        pfVar3[1] = local_2c;
    }

    return;
}