// FUNC_NAME: CollisionSweep::sweepAndSlide
// Address: 0x0058f090
// This function performs a sweep-and-slide collision response along surfaces.
// It takes an entity (param_2) with position at +0x90, quaternion at +0x50,
// previous target at +0xD0, and applies sliding logic based on collision normals.
// The input 'in_EAX' is interpreted as a displacement/velocity quaternion overwriting +0x50.

void __thiscall CollisionSweep::sweepAndSlide(
    int mode,                     // param_1: 0=slide along normal, 1=slide along other, 2=copy, default=full
    Entity* entity,               // param_2: object with physics fields
    uint flags,                   // param_4: bit0=extra transform, bit1=alternative epsilon
    const float* displacementQuat // in_EAX: input quaternion/velocity to apply at +0x50
)
{
    // Saved original quaternion at +0x50 (before overwriting)
    float oldQuatW = entity->field_4x_50[0]; // +0x50
    float oldQuatX = entity->field_4x_50[1]; // +0x54
    float oldQuatY = entity->field_4x_50[2]; // +0x58
    float oldQuatZ = entity->field_4x_50[3]; // +0x5C

    // Overwrite quaternion with input displacement
    entity->field_4x_50[0] = displacementQuat[0];
    entity->field_4x_50[1] = displacementQuat[1];
    entity->field_4x_50[2] = displacementQuat[2];
    // Note: third component written, but +0x5C is not set? Actually it is set via in_EAX[3]? Code shows only [0],[1],[2] are set? Let's recheck decomp: after setting +0x50, +0x54, +0x58 it sets +0x5C? No, it sets +0x50, +0x54, +0x58, then later there's a load from +0x5C but it's not written. Possibly a bug. We'll assume it's set as well.
    // Actually the code: "*(undefined4 *)(param_2 + 0x54) = in_EAX[1];" "*(undefined4 *)(param_2 + 0x58) = in_EAX[2];" but no in_EAX[3]. So only 3 components? That's odd. Might be a 3-float normal. We'll treat it as 3-float.
    // For reconstruction, we'll leave as 3 floats for displacement.
    // The oldQuatZ is not overwritten; it remains from old.

    // Read previous target position from +0xD0
    float targetPosW = entity->field_4x_D0[0]; // +0xD0
    float targetPosX = entity->field_4x_D0[1]; // +0xD4
    float targetPosY = entity->field_4x_D0[2]; // +0xD8
    float targetPosZ = entity->field_4x_D0[3]; // +0xDC

    // Current entity position at +0x90
    float curPosW = entity->field_4x_90[0]; // +0x90
    float curPosX = entity->field_4x_90[1]; // +0x94
    float curPosY = entity->field_4x_90[2]; // +0x98
    float curPosZ = entity->field_4x_90[3]; // +0x9C

    // Vectors
    float vecFromTargetToCur[4]; // local_70 etc.
    vecFromTargetToCur[0] = curPosW - targetPosW;
    vecFromTargetToCur[1] = curPosX - targetPosX;
    vecFromTargetToCur[2] = curPosY - targetPosY;
    vecFromTargetToCur[3] = curPosZ - targetPosZ;

    float vecOldQuatToCur[4]; // local_a0 etc.
    float oldQuatW_save = entity->field_4x_50[0]; // after overwrite? Actually after overwrite, oldQuatW is saved separately. This is the new quaternion (displacement) vs old cur position? Let's see: local_a0 = oldQuatW - curPosW; etc. So it's displacement from cur pos to old quat? Wait, oldQuatW is actually the newly written displacement? No, oldQuatW is from +0x50 but after overwrite, it's the new displacement. So this is displacement from current entity position to the new displacement? Actually the code: local_a0 = oldQuatW - curPosW; where oldQuatW is the first component of the just-written value. So it's the vector from current pos to the displacement quaternion's first component? That doesn't make geometric sense. Likely the quaternion at +0x50 is actually a velocity/offset, not a quaternion. The operations treat it as a vector. So the object at +0x50 is a 3-float offset. We'll rename accordingly.

    // Better interpretation: The function receives a movement vector (dx,dy,dz) via in_EAX and writes it to entity->velocity offset 0x50. Then it does sliding.

    // So we'll treat offset 0x50 as "velocity" (3 floats, no w)
    // Old "velocity" saved as oldVel.
    // New velocity set from input.
    // Then compute difference between new velocity and current position? That is odd. Let's follow the code literally.

    // local_a0 = newVel[0] - curPosW? But curPosW is position, not velocity. This might be a bug in decompilation? Or maybe the object has multiple fields and we misinterpreted offsets. Given the complexity, we'll reconstruct as closely as possible to the decompiled logic.

    // I'll proceed with the code structure, using the original variable names but with meaningful comments.

    // Save old velocity (from +0x50) before overwrite
    float oldVel[4];
    oldVel[0] = entity->field_50[0];
    oldVel[1] = entity->field_50[1];
    oldVel[2] = entity->field_50[2];
    oldVel[3] = entity->field_50[3]; // +0x5C

    // Write new velocity from input
    entity->field_50[0] = displacement[0];
    entity->field_50[1] = displacement[1];
    entity->field_50[2] = displacement[2];
    // Note: +0x5C is not written (may remain old)

    // Read target position from +0xD0 (previous frame desired position?)
    float targetPos[4];
    targetPos[0] = entity->field_D0[0];
    targetPos[1] = entity->field_D0[1];
    targetPos[2] = entity->field_D0[2];
    targetPos[3] = entity->field_D0[3];

    // Vectors:
    // v1 = current position - target position (movement from target to current)
    float v1[4];
    v1[0] = entity->field_90[0] - targetPos[0];
    v1[1] = entity->field_90[1] - targetPos[1];
    v1[2] = entity->field_90[2] - targetPos[2];
    v1[3] = entity->field_90[3] - targetPos[3];

    // v2 = old velocity - current position? Actually oldVel - current pos? Code: local_a0 = oldVel[0] - curPosW; so v2 = old velocity minus current position (weird)
    float v2[4];
    v2[0] = oldVel[0] - entity->field_90[0];
    v2[1] = oldVel[1] - entity->field_90[1];
    v2[2] = oldVel[2] - entity->field_90[2];
    v2[3] = oldVel[3] - entity->field_90[3];

    // v3 = new velocity - target position? Actually newVel minus targetPos? Code: local_b0 = newVel[0] - targetPos[0]; etc.
    float v3[4];
    v3[0] = entity->field_50[0] - targetPos[0];
    v3[1] = entity->field_50[1] - targetPos[1];
    v3[2] = entity->field_50[2] - targetPos[2];
    v3[3] = entity->field_50[3] - targetPos[3];

    // Compute squared lengths
    float lenV2Sq = v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2]; // local_44? Actually local_44 = fStack_6c... Wait local_44 is from v1? Let's track: local_44 = v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]? Code: local_44 = fStack_6c*fStack_6c + fStack_68*fStack_68 + local_70*local_70; and local_70 is v1[0]? Yes local_70 = v1[0]. So local_44 = lenV1Sq.
    // Similarly local_4c = lenV3Sq.
    // local_b0? Actually local_b0 is v3[0]? No, local_b0 is part of v3? Let's just proceed.

    float lenV1Sq = v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2];
    float lenV3Sq = v3[0]*v3[0] + v3[1]*v3[1] + v3[2]*v3[2];
    float invLenV3Sq = DAT_00e2b1a4 / lenV3Sq; // local_48

    float lenV2Sq = v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2]; // fVar5 originally from fStack_9c etc. Actually fVar5 = fStack_9c*fStack_9c + local_a0*local_a0 + fStack_98*fStack_98; and local_a0 = v2[0], fStack_9c = v2[1], fStack_98 = v2[2]. So lenV2Sq.

    // Compute fVar4 = ((lenV3Sq + lenV1Sq) - lenV2Sq) * invLenV3Sq * DAT_00e2cd54;
    float t = ((lenV3Sq + lenV1Sq) - lenV2Sq) * invLenV3Sq * DAT_00e2cd54; // parameter along v3

    // Condition for sliding
    bool bVar2;
    if ((flags >> 1) & 1) {
        bVar2 = (lenV3Sq * DAT_00e2cd14) < (lenV1Sq + lenV2Sq);
    } else {
        bVar2 = (lenV3Sq * DAT_00e2cd54) < (lenV1Sq + lenV2Sq);
    }

    if (!bVar2 || (t < 0.0f) || (t > 1.0f)) { // DAT_00e2b1a4 is 1.0? Actually comparison: DAT_00e2b1a4 < fVar4 (t). So if t > 1.0? Probably DAT_00e2b1a4 is 1.0.
        // No intersection, restore old velocity
        entity->field_50[0] = oldVel[0];
        entity->field_50[1] = oldVel[1];
        entity->field_50[2] = oldVel[2];
        return;
    }

    // Compute closest point along v3 from target
    float closest[4];
    closest[0] = t * v3[0] + targetPos[0];
    closest[1] = t * v3[1] + targetPos[1];
    closest[2] = t * v3[2] + targetPos[2];
    // closest[3] = t * v3[3] + targetPos[3]; // v3[3] is probably 0 or 1? Not used.

    // Compute perpendicular distance squared
    float perpDistSq = lenV1Sq - t*t * lenV3Sq; // local_44
    if (perpDistSq <= 0.0f) {
        perpDistSq = 0.0f;
        // lenV2Sq is used later? Actually fVar5 = lenV3Sq? Code: if perpDistSq<=0 then fVar5 = lenV3Sq; else fVar5 = sqrt(perpDistSq). We'll track.
    } else {
        perpDistSq = sqrtf(perpDistSq);
    }
    float perpDist = (perpDistSq <= 0.0f) ? lenV3Sq : perpDistSq; // fVar5

    // Direction vectors for sliding
    float slideDir[4]; // local_60 etc.
    // Initially slideDir = v2? Actually local_30 = local_a0? Let's set:
    slideDir[0] = v2[0];
    slideDir[1] = v2[1];
    slideDir[2] = v2[2];
    // slideDir[3] left maybe zero.

    float slideNormal[4]; // local_20 etc.
    slideNormal[0] = v1[0];
    slideNormal[1] = v1[1];
    slideNormal[2] = v1[2];

    // Now switch on mode
    float finalVel[4]; // local_90 etc.
    switch (mode) {
        case 0: {
            // Dot product of v3 and v1
            float dot_v3_v1 = v3[0]*v1[0] + v3[1]*v1[1] + v3[2]*v1[2];
            // Compute reflection? Using function at 0x44c490 (likely cross product)
            // Actually: FUN_0044c490(&local_70, &local_b0, DAT_00e44564 - invLenV3Sq * dot_v3_v1, &local_90);
            float factor = DAT_00e44564 - invLenV3Sq * dot_v3_v1;
            // local_70 is v1, local_b0 is v3? Wait local_b0 is part of v3? In case0, local_b0 is used, but it was v3[0] earlier? Actually local_b0 = v3[0]? Let's re-derive: earlier local_b0 = v3[0] (from code: local_b0 = *(float *)(param_2+0x50) - local_40; where local_40 is targetPos[0]). So yes.
            // So crossProduct(v1, v3, factor, result)?
            crossProduct(v1, v3, factor, finalVel); // FUN_0044c490
            normalize(finalVel); // FUN_0044d680
            // Check final length against epsilon
            if ( (dot_v3_v1*dot_v3_v1 - lenV3Sq) * DAT_00e44680 <= DAT_00e2e210 ) { // actually condition: if DAT_00e2e210 <= (float)((uint)(fVar4 * fVar4 - local_4c) & DAT_00e44680) ... this is unclear
                // It's a bitwise AND on float? That's odd. Likely a condition for parallel vectors.
                bVar2 = true;
                goto afterSwitch;
            }
            // Fall through to case1? The code doesn't have break, it falls through.
        }
        case 1: {
            // Negate v2
            v2[0] = -v2[0];
            v2[1] = -v2[1];
            v2[2] = -v2[2];
            float dot_v2_v3 = v2[0]*v3[0] + v2[1]*v3[1] + v2[2]*v3[2];
            float factor = DAT_00e44564 - invLenV3Sq * dot_v2_v3;
            crossProduct(v2, v3, factor, finalVel); // FUN_0044c490
            normalize(finalVel); // FUN_0044d680
            // Check condition
            bVar2 = ( (dot_v2_v3*dot_v2_v3 - lenV3Sq) * DAT_00e44680 ) < DAT_00e2e210;
            break;
        }
        case 2: {
            // Copy operations? Unclear. Uses FUN_00417760 (copy) and FUN_00473610 (unknown)
            copyVector(&oldVel, &finalVel); // FUN_00417760
            copyVector(&finalVel, &v2); // FUN_00417760 again? Actually it's copy from something.
            // then FUN_00473610() (maybe a function call)
            bVar2 = (perpDist < DAT_00e2e210);
            break;
        }
        default: {
            // Compute v4 = oldvel - targetPos? Actually local_90 = oldVel[0] - targetPos[0]; etc.
            float v4[4];
            v4[0] = oldVel[0] - targetPos[0];
            v4[1] = oldVel[1] - targetPos[1];
            v4[2] = oldVel[2] - targetPos[2];
            // copyVector(&oldVel, &finalVel); // FUN_00417760
            // copyVector(&v2, &v2); // seems redundant
            float dot_v2_v3 = v2[0]*v3[0] + v2[1]*v3[1] + v2[2]*v3[2];
            float factor = DAT_00e44564 - invLenV3Sq * dot_v2_v3;
            finalVel[0] = factor * v3[0] + v2[0];
            finalVel[1] = factor * v3[1] + v2[1];
            finalVel[2] = factor * v3[2] + v2[2];
            normalize(finalVel); // FUN_0044d680
            // Then goto label LAB_0058f46f which sets bVar2 as in case1
            bVar2 = ( (dot_v2_v3*dot_v2_v3 - lenV3Sq) * DAT_00e44680 ) < DAT_00e2e210;
            break;
        }
    }

afterSwitch:
    // If bVar2 is true, it means fallback to no slide? Actually bVar2 is used to decide whether to apply slide or not.
    // After switch, if bVar2 true, then set bVar2 = false; else bVar2 = true. Then later if !bVar2, do something else.
    if (bVar2) {
        bVar2 = false;
    } else {
        bVar2 = true;
    }

    // Save old current position z? Actually code: uVar1 = *(undefined4 *)(param_2 + 0x9c); // old curPosW[3]
    float oldCurPosW_save = entity->field_90[3]; // +0x9C

    // Update entity position using slide
    entity->field_90[0] = perpDist * finalVel[0] + closest[0];
    entity->field_90[1] = perpDist * finalVel[1] + closest[1];
    entity->field_90[2] = perpDist * finalVel[2] + closest[2];
    entity->field_90[3] = perpDist * finalVel[3] + closest[3]; // actually finalVel[3] may be 0

    // Restore old z component? Code: *(undefined4 *)(param_2 + 0x9c) = uVar1; // overwrite w component with saved value. So w remains unchanged.
    entity->field_90[3] = oldCurPosW_save;

    if (!bVar2) {
        // If slide was successful, move only along closest point plus slide direction along Y?
        entity->field_90[0] = closest[0];
        entity->field_90[1] = closest[1];
        entity->field_90[2] = closest[2] + perpDist; // note: uses perpDist added to z? Code: *(float *)(param_2 + 0x98) = fStack_58 + local_44; Where local_44 is perpDist? Actually local_44 after condition is perpDist. And fStack_58 is closest[2]. So yes, add perpDist to Z.
    }

    // Re-read current position and velocity for further transformations
    float newPos[4]; // from +0x90 after update
    newPos[0] = entity->field_90[0];
    newPos[1] = entity->field_90[1];
    newPos[2] = entity->field_90[2];
    newPos[3] = entity->field_90[3];

    float newVel[4]; // from +0x50
    newVel[0] = entity->field_50[0];
    newVel[1] = entity->field_50[1];
    newVel[2] = entity->field_50[2];
    newVel[3] = entity->field_50[3];

    // Compute some normalized vectors
    normalize(v1); // local_70 -> normalized v1
    normalize(v2); // local_60 -> normalized v2? Actually local_60 was slideDir? It's now using local_30? We'll track.

    float deltaPos[4]; // newPos - targetPos
    deltaPos[0] = newPos[0] - targetPos[0];
    deltaPos[1] = newPos[1] - targetPos[1];
    deltaPos[2] = newPos[2] - targetPos[2];
    normalize(deltaPos); // local_90

    float deltaVel[4]; // newVel - newPos
    deltaVel[0] = newVel[0] - newPos[0];
    deltaVel[1] = newVel[1] - newPos[1];
    deltaVel[2] = newVel[2] - newPos[2];
    normalize(deltaVel); // local_80

    // Dot products to align
    dotProduct(v1, deltaPos, &finalVel[0]); // FUN_004f1c90 (dot product)
    dotProduct(v2, deltaVel, &v1[0]); // actually local_a0? We'll treat as storing result.

    float magVel = v3[0]*v3[0] + v3[1]*v3[1] + v3[2]*v3[2]; // local_b0 vector? Actually it's v3 squared length again.
    if (magVel > DAT_00e2b05c) {
        // Normalize v3
        float invMag = 1.0f / sqrtf(magVel);
        v3[0] *= invMag;
        v3[1] *= invMag;
        v3[2] *= invMag;
        // Then call some transform functions to update orientation
        // FUN_0058dfa0(); (unknown)
        // FUN_0056cba0(&targetPos, param_2 + 0x140, &v2); // matrix multiply  (offset 0x140 maybe world matrix)
        // FUN_0056cef0(&v2, param_2 + 0xa0); // apply to offset 0xa0 (maybe a rotation matrix)
    }

    float magDeltaPos = deltaPos[0]*deltaPos[0] + deltaPos[1]*deltaPos[1] + deltaPos[2]*deltaPos[2]; // actually v2?
    if (magDeltaPos > DAT_00e2b05c) {
        // Normalize deltaPos
        float invMag = 1.0f / sqrtf(magDeltaPos);
        deltaPos[0] *= invMag;
        deltaPos[1] *= invMag;
        deltaPos[2] *= invMag;
        // Similar transform calls
        // FUN_0056cba0(&v2, param_2 + 0x130, &targetPos);
        // FUN_0056cef0(&targetPos, param_2 + 0x60);
        if (flags & 1) {
            // Additional transform
            // FUN_0056cba0(&v2, param_2 + 0x120, &targetPos);
            // FUN_0056cef0(&targetPos, param_2 + 0x20);
        }
    }

    // Final cleanup calls on offsets 0xa0, 0x60, 0x20 (maybe matrix orthonormalization)
    cleanUpMatrix(param_2 + 0xa0); // FUN_0058df40
    cleanUpMatrix(param_2 + 0x60);
    cleanUpMatrix(param_2 + 0x20);
}