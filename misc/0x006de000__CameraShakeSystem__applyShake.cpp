// FUNC_NAME: CameraShakeSystem::applyShake

void __thiscall CameraShakeSystem::applyShake(
    int this,
    float *outPos,
    float *outTarget,
    float *outUp,
    float *outRight,
    float *outForward,
    float *outLookSpeed,
    int *shakeData,
    float deltaTime,
    char isZoomed,
    char *isShaking,
    float *shakeTimer,
    float shakeDecay
)
{
    char cVar1;
    int iVar2;
    uint uVar3;
    int *piVar4;
    float10 fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fStack_84;
    float fStack_80;
    float fStack_74;
    float fStack_70;
    float fStack_68;
    uint uStack_64;
    float local_5c;
    undefined8 local_58;
    float local_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float fStack_40;
    float fStack_3c;
    float fStack_38;
    float local_34;
    float local_30;
    float local_2c;
    float local_28;
    float fStack_24;
    float local_20;
    float fStack_1c;

    // Determine pointer to source shake data (offset -0x48 adjustment for null handling)
    if (*shakeData == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *shakeData + -0x48;
    }
    if (shakeData[2] == 0) {
        piVar4 = (int *)0x0;
    } else {
        piVar4 = (int *)(shakeData[2] + -0x48);
    }

    if ((iVar2 != 0) && (piVar4 != (int *)0x0)) {
        // Get camera transform (position and quaternion components)
        iVar2 = FUN_00471610();
        local_58 = *(undefined8 *)(iVar2 + 0x30); // camera position X,Y
        local_50 = *(float *)(iVar2 + 0x38);      // camera position Z
        iVar2 = FUN_00471610();
        local_20 = *(float *)(iVar2 + 0x38);      // target position Z
        local_28 = (float)*(undefined8 *)(iVar2 + 0x30); // target position X,Y
        fStack_24 = (float)((ulonglong)*(undefined8 *)(iVar2 + 0x30) >> 0x20); // target position Y as separate float

        // Compute difference vector from camera to target
        local_34 = local_28 - (float)local_58;    // delta X
        local_30 = fStack_24 - local_58._4_4_;    // delta Y
        local_2c = local_20 - local_50;            // delta Z

        // Distance between camera and target
        fVar6 = SQRT(local_34 * local_34 + local_2c * local_2c + local_30 * local_30);

        local_5c = 0.0;
        // Perform virtual call on shakeData[2] object (likely a hash check for shake type)
        cVar1 = (**(code **)(*piVar4 + 0x10))(0x55859efa, &local_5c);
        uVar3 = -(uint)(cVar1 != '\0') & uStack_64;

        if ((*(int *)(this + 0x2d0) != 0) && (uVar3 != 0)) {
            // Check a flag in the external object (at offset 0x8e4 bit 0)
            if ((*(byte *)(*(int *)(this + 0x2d0) + 0x8e4) & 1) == 0) {
                cVar1 = FUN_00690150(0x2a); // Check if shake type A is allowed
                if ((cVar1 == '\0') && (cVar1 = FUN_00690150(0x2b), cVar1 == '\0')) {
                    cVar1 = FUN_00690150(0x18); // Check if shake type C is allowed
                    if (cVar1 == '\0') {
                        // Normal shake - select parameters based on character state (offset 0x1b8c)
                        switch(*(undefined1 *)(uVar3 + 0x1b8c)) {
                        case 1:
                        case 4:
                            fStack_80 = (DAT_00e445ac - (float)shakeData[0x2e]) * *(float *)(this + 0x80) +
                                        (float)shakeData[0x2e];
                            fVar8 = (float)shakeData[0x30];
                            fVar14 = (float)shakeData[0x2f];
                            fStack_74 = (float)shakeData[0x31];
                            fStack_84 = (float)shakeData[0x32] * DAT_00e445c8;
                            fVar11 = (float)shakeData[0x34];
                            fStack_70 = (DAT_00d5efa0 - (float)shakeData[0x33]) * *(float *)(this + 0x80) +
                                        (float)shakeData[0x33];
                            fVar7 = ((float)shakeData[0x35] - (float)shakeData[0x36]) * deltaTime +
                                    (float)shakeData[0x36];
                            break;
                        case 2:
                        case 3:
                            fStack_80 = (DAT_00e445ac - (float)shakeData[0x37]) * *(float *)(this + 0x80) +
                                        (float)shakeData[0x37];
                            fVar8 = (float)shakeData[0x39];
                            fVar14 = (float)shakeData[0x38];
                            fStack_74 = (float)shakeData[0x3a];
                            fStack_84 = (float)shakeData[0x3b] * DAT_00e445c8;
                            fVar11 = (float)shakeData[0x3d];
                            fStack_70 = (DAT_00d5efa0 - (float)shakeData[0x3c]) * *(float *)(this + 0x80) +
                                        (float)shakeData[0x3c];
                            fVar7 = ((float)shakeData[0x3e] - (float)shakeData[0x3f]) * deltaTime +
                                    (float)shakeData[0x3f];
                            break;
                        default:
                            fVar7 = *(float *)(this + 0x80);
                            fStack_80 = (DAT_00e445ac - (float)shakeData[0x24]) * fVar7 +
                                        (float)shakeData[0x24];
                            fVar8 = (DAT_00d5ca64 - (float)shakeData[0x27]) * fVar7 +
                                    (float)shakeData[0x27];
                            if (isZoomed == '\0') {
                                fVar14 = (float)shakeData[0x26];
                            } else {
                                fVar14 = DAT_00e44564 - (float)shakeData[0x25];
                            }
                            fStack_74 = (float)shakeData[0x28];
                            fStack_84 = (float)shakeData[0x29] * DAT_00e445c8;
                            fVar11 = (float)shakeData[0x2b];
                            fStack_70 = (DAT_00d5efa0 - (float)shakeData[0x2a]) * fVar7 +
                                        (float)shakeData[0x2a];
                            fVar7 = ((float)shakeData[0x2c] - (float)shakeData[0x2d]) * deltaTime +
                                    (float)shakeData[0x2d];
                        }
                    } else {
                        // Special handling for shake type C (offset 0x18 flag)
                        fStack_80 = (float)shakeData[0x4c];
                        fVar11 = (float)shakeData[0x2b];
                        fVar8 = (float)shakeData[0x4e];
                        fVar14 = (float)shakeData[0x4d];
                        fStack_74 = (float)shakeData[0x4f];
                        fStack_84 = (float)shakeData[0x50] * DAT_00e445c8;
                        fStack_70 = (DAT_00d5efa0 - (float)shakeData[0x2a]) * *(float *)(this + 0x80) +
                                    (float)shakeData[0x2a];
                        fVar7 = (float)shakeData[0x2c];
                    }
                } else {
                    // Shake type A or B active - use alternate parameters
                    fVar10 = DAT_00e51200; // some global constant
                    fVar11 = DAT_00d5f6f4;
                    fVar7 = DAT_00d5f6f0;
                    fStack_80 = (float)shakeData[0x46];
                    fVar8 = (float)shakeData[0x48];
                    fVar14 = (float)shakeData[0x47];
                    fStack_74 = (float)shakeData[0x49];
                    fStack_84 = (float)shakeData[0x4a] * DAT_00e445c8;
                    fStack_70 = (float)shakeData[0x4b];
                    *isShaking = '\x01';
                    *shakeTimer = fVar10;
                }
            } else {
                // Flag at offset 0x8e4 is set - cinematic/override shake
                fStack_80 = (float)shakeData[0x40];
                fVar8 = (float)shakeData[0x42];
                fVar14 = (float)shakeData[0x41];
                fStack_74 = (float)shakeData[0x43];
                fStack_84 = (float)shakeData[0x44] * DAT_00e445c8;
                fStack_70 = (float)shakeData[0x45];
                fVar11 = DAT_00e511f8;
                fVar7 = DAT_00e511fc;
            }

            // Check if we need to force back to a default shake type
            if ((((*isShaking != '\0') && (cVar1 = FUN_00690150(0x2a), cVar1 == '\0')) &&
                 (cVar1 = FUN_00690150(0x2b), cVar1 == '\0')) && (0.0 < *shakeTimer)) {
                fStack_80 = (float)shakeData[0x46];
                fVar8 = (float)shakeData[0x48];
                fVar14 = (float)shakeData[0x47];
                fStack_74 = (float)shakeData[0x49];
                fStack_84 = (float)shakeData[0x4a] * DAT_00e445c8;
                fStack_70 = (float)shakeData[0x4b];
                fVar11 = DAT_00d5f6f4;
                fVar7 = DAT_00d5f6f0;
            }

            // Decay timer
            shakeDecay = *shakeTimer - shakeDecay;
            if (shakeDecay < 0.0) {
                shakeDecay = 0.0;
            }
            *shakeTimer = shakeDecay;
            if (shakeDecay == 0.0) {
                *isShaking = '\0';
            }

            // Clamp shake parameters
            if (fVar11 < 0.0) {
                fVar11 = 0.0;
            }
            if (fVar7 < fVar11) {
                fVar7 = fVar11;
            }

            // Determine blend factor (fStack_68 is the current blending value)
            if (fStack_68 < fVar7) {
                if (fVar11 < fStack_68) {
                    if (DAT_00e44598 < fVar7 - fVar11) {
                        // Use smooth interpolation (FUN_006c91c0 likely a smoothstep)
                        fVar5 = (float10)FUN_006c91c0(fStack_68, fVar11, fVar7, 0x3f800000, 0);
                        *(float *)(this + 0x2c0) = (float)fVar5;
                    } else {
                        // Use constant
                        *(undefined4 *)(this + 0x2c0) = DAT_00d5c458;
                    }
                } else {
                    *(undefined4 *)(this + 0x2c0) = DAT_00d5780c;
                }
            } else {
                *(undefined4 *)(this + 0x2c0) = 0;
            }

            // If blend factor is zero, exit early
            if (*(float *)(this + 0x2c0) == 0.0) {
                return;
            }

            // Compute shake direction vectors (assumed to be camera local axes)
            // Call to FUN_0043a210 likely computes cross product or matrix axes
            FUN_0043a210(&fStack_48, &fStack_3c); // get 'up' and 'right' vectors?
            local_50 = fStack_40 * 0.0 - fStack_48 * 0.0;
            fStack_4c = fStack_48 - fStack_44 * 0.0;
            local_58._4_4_ = fStack_44 * 0.0 - fStack_40;
            FUN_0043a210((int)&local_58 + 4, (int)&local_58 + 4); // normalize?

            // Orthogonalize
            local_30 = local_50 * fStack_40 - fStack_4c * fStack_44;
            local_28 = local_58._4_4_ * fStack_44 - local_50 * fStack_48;
            fVar11 = (float)shakeData[5];
            local_2c = fStack_4c * fStack_48 - local_58._4_4_ * fStack_40;

            // Determine if we use radial or linear shake
            if (fVar11 * fVar11 <= fStack_68) {
                // Radial shake (scaled by distance)
                fStack_3c = fStack_3c * fStack_74;
                local_34 = local_34 * fStack_74;
            } else {
                // Linear shake along camera axis
                fStack_3c = fVar11 * fStack_48;
                local_34 = fVar11 * fStack_40;
                fStack_38 = fVar11;
                fStack_74 = fStack_44;
            }

            // Apply shake translation offset
            local_34 = local_28 * fVar8 + local_34 + (float)local_58;
            dVar9 = (double)fStack_84;
            fStack_3c = local_30 * fVar8 + fStack_3c + fVar6;
            fStack_38 = local_2c * fVar8 + fStack_38 * fStack_74 + local_5c;
            FUN_00b99fcb(); // Possibly sin/cos for rotation
            fVar8 = (float)dVar9 * fStack_80 + fVar8;
            dVar9 = (double)fStack_84;
            FUN_00b99e20(); // Possibly sin/cos complement
            fVar11 = (float)dVar9 * fStack_80;
            if ((float)dVar9 * fStack_80 < DAT_00d58cbc) {
                fVar11 = DAT_00d58cbc;
            }

            // Apply zoom factor
            if (isZoomed != '\0') {
                fVar14 = fVar14 * DAT_00d5ccf8;
            }

            // Interpolate look speed and apply final transformations
            local_20 = local_5c;
            fVar11 = DAT_00e44564 - fVar11;
            fStack_1c = (float)local_58;
            fVar7 = *outLookSpeed;
            fVar10 = ((float)shakeData[0x1a] - (float)shakeData[0x22]) * deltaTime + (float)shakeData[0x22];
            if (fVar7 != DAT_00d577a0) {
                fVar10 = (fVar10 - fVar7) * DAT_00d5c454 + fVar7;
            }
            fVar10 = ((float)shakeData[0x12] - fVar10) * *(float *)(this + 0x2cc) + fVar10;
            *outLookSpeed = fVar10;

            // Apply blending to position, target, and up vectors
            fVar7 = *(float *)(this + 0x2c0);
            fVar12 = ((local_58._4_4_ * fVar14 + local_30 * fVar8 + fVar11 * fStack_48 + fVar6) - *outRight) * fVar10 + *outRight;
            fVar13 = ((local_50 * fVar14 + local_2c * fVar8 + fVar11 * fStack_44 + local_5c) - outRight[1]) * fVar10 + outRight[1];
            fVar8 = ((fStack_4c * fVar14 + local_28 * fVar8 + fVar11 * fStack_40 + (float)local_58) - outRight[2]) * fVar10 + outRight[2];

            *outPos = (fVar12 - *outPos) * fVar7 + *outPos;
            outPos[1] = (fVar13 - outPos[1]) * fVar7 + outPos[1];
            outPos[2] = (fVar8 - outPos[2]) * fVar7 + outPos[2];

            fVar11 = *(float *)(this + 0x2c0);
            *outTarget = ((fVar12 - fStack_3c) - *outTarget) * fVar11 + *outTarget;
            outTarget[1] = ((fVar13 - fStack_38) - outTarget[1]) * fVar11 + outTarget[1];
            outTarget[2] = ((fVar8 - local_34) - outTarget[2]) * fVar11 + outTarget[2];

            fVar11 = *(float *)(this + 0x2c0);
            outUp[1] = (fStack_38 - outUp[1]) * fVar11 + outUp[1];
            *outUp = (fStack_3c - *outUp) * fVar11 + *outUp;
            outUp[2] = (local_34 - outUp[2]) * fVar11 + outUp[2];

            // Apply final height offset
            cVar1 = FUN_00690150(0x18);
            if (cVar1 == '\0') {
                fVar6 = (DAT_00d5efa0 - (float)shakeData[0x21]) * *(float *)(this + 0x80) +
                        (float)shakeData[0x21];
                fVar6 = ((float)shakeData[0x19] - fVar6) * deltaTime + fVar6;
            } else {
                fVar6 = (float)shakeData[0x57];
            }
            *outForward = (fStack_70 - fVar6) * *(float *)(this + 0x2c0) + fVar6;
            return;
        }
    }

    // If conditions not met, zero out blend factor
    *(undefined4 *)(this + 0x2c0) = 0;
    return;
}