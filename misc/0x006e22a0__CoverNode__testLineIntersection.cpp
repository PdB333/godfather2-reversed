// FUNC_NAME: CoverNode::testLineIntersection
ushort __thiscall CoverNode::testLineIntersection(float *pDirection, float *pNormal, float *pTarget)
{
    // pDirection: direction vector (x, y, z) from entity to cover node
    // pNormal: normal vector of the cover face (uses components 0 and 2)
    // pTarget: target point to test

    // Offsets on this:
    // +0x20: position.x?
    // +0x28: position.z?
    // +0x124: pointer to some structure (maybe parent)/ or entity?
    // +0x154: some offset factor

    // Constants (likely 1.0)
    const float floatOne = DAT_00e44564;  // usually 1.0
    const float anotherOne = _DAT_00d5f7b0; // appears in subtraction

    int pSomeStruct;
    if (*(int*)((int)this + 0x124) == 0) {
        pSomeStruct = 0;
    } else {
        pSomeStruct = *(int*)((int)this + 0x124) - 0x48;
    }

    // Copy normal components
    float normalX = pNormal[0];
    float normalZ = pNormal[2];  // y component unused?

    // Direction vector
    float dirX = pDirection[0];
    float dirY = pDirection[1];
    float dirZ = pDirection[2];

    // Compute difference from this position to target
    float dx = *(float*)((int)this + 0x20) - pTarget[0];
    float dz = *(float*)((int)this + 0x28) - pTarget[2];
    // Note: dy not used

    // First dot product with only x and z components of normal
    float dot1 = normalX * dx + normalZ * dz;

    float oneMinusDot1 = floatOne - (dot1 + anotherOne);  // Probably 1 - (dot1 + 1) => -dot1

    // Scale direction by some factor
    float scaledX = dirX * oneMinusDot1;
    float scaledY = dirY * oneMinusDot1;
    float scaledZ = dirZ * oneMinusDot1;

    // Second factor based on bit flags
    float factor2;
    if ((*(uint*)(pSomeStruct + 0x8e0) >> 0x1d & 1) == 0) {
        factor2 = floatOne - *(float*)((int)this + 0x154);
    } else {
        factor2 = *(float*)((int)this + 0x154);
    }

    float offsetX = dirX * factor2;
    float offsetY = dirY * factor2;
    float offsetZ = dirZ * factor2;

    // Additional dot products
    float dot2 = dirX * dx + dirY * 0.0f + dirZ * dz;  // dirY*0 effectively
    float oneMinusDot2 = floatOne - dot2;
    float oneMinusDot1b = floatOne - dot1;

    // Modify point components
    float pointX = pTarget[0] - normalX * oneMinusDot1b - dirX * oneMinusDot2;
    float pointY = pTarget[1] - pNormal[1] * oneMinusDot1b - dirY * oneMinusDot2;
    float pointZ = pTarget[2] - normalZ * oneMinusDot1b - dirZ * oneMinusDot2;

    // First candidate intersection point
    float candidateX = pointX + offsetX + dirX * oneMinusDot2;
    float candidateY = pointY + offsetY + dirY * oneMinusDot2;
    float candidateZ = pointZ + offsetZ + dirZ * oneMinusDot2;

    // Call unknown function (likely a ray intersection test)
    float3 localVec = { pointX, pointY, pointZ };  // but first argument is ref to local_3c? Actually in code, local_3c was reassigned.
    // We'll replicate the exact logic:

    // Stage 1:
    float local48 = candidateX;
    float stack44 = candidateY;
    float local40 = candidateZ;
    // The unknown function is called with arguments: &local_3c (which is a vector), &local48 (float), local_c (array of normal components? actually local_c = copy of pNormal)

    // For simplicity, we replicate the call structure
    auto result = FUN_006ca5e0(&localVec, &candidateX, pNormal);
    ushort flags = (result == 1.0f) ? 0x40 : ((result < 1.0f) ? 0x02 : 0x00) | (isnan(result) ? 0x04 : 0x00);
    // The actual bit packing is more complex but omitted for brevity.

    // The code does multiple stages if equality holds.
    // We'll implement as in original but simplified.

    // Actually, we'll reconstruct the exact pattern.

    // Copy of original code logic:
    float localC[2]; // actually local_c[0] = *pNormal, but not used as array here
    localC[0] = *pNormal;
    float local10 = pDirection[2];
    float fVar6 = *(float*)((int)this + 0x20) - *pTarget;
    float local4 = *(float*)((int)this + 0x28) - pTarget[2];
    float fVar7 = localC[0] * fVar6 + pNormal[1] * 0.0f + pNormal[2] * local4;
    float local18 = *pDirection;
    float local14 = pDirection[1];
    float local1c = floatOne - (fVar7 + anotherOne);
    float local24 = localC[0] * local1c;
    float local20 = pNormal[1] * local1c;
    float local1c_2 = pNormal[2] * local1c;
    float local28;
    if ((*(uint*)(pSomeStruct + 0x8e0) >> 0x1d & 1) == 0) {
        local28 = floatOne - *(float*)((int)this + 0x154);
    } else {
        local28 = *(float*)((int)this + 0x154);
    }
    float local30 = local18 * local28;
    float local2c = local14 * local28;
    local28 = local10 * local28;
    fVar6 = floatOne - (local18 * fVar6 + local14 * 0.0f + local10 * local4);
    fVar7 = floatOne - fVar7;
    local14 = local14 * fVar6;
    localC[0] = localC[0] * fVar7;
    local10 = local10 * fVar6;
    local18 = local18 * fVar6;
    float fVar8 = (*pTarget - localC[0]) - local18;
    float fVar6_2 = (pTarget[1] - pNormal[1] * fVar7) - local14;
    float local34 = (pTarget[2] - fVar7 * pNormal[2]) - local10;
    int64 local3c = (int64)fVar8 | ((int64)fVar6_2 << 32); // pack as 64-bit? Actually local_3c is two floats treated as int64
    float local48 = fVar8 + local30 + local18;
    float fStack_44 = fVar6_2 + local2c + local14;
    float local40 = local34 + local28 + local10;

    // First call to unknown function
    float10 fVar5 = FUN_006ca5e0(&local3c, &local48, localC);
    float10 fVar2 = 1.0f;
    ushort uVar3;
    uVar3 = (ushort)(byte)(((fVar5 == fVar2) << 6) | ((isnan(fVar5) || isnan(fVar2)) << 2) | 2U | (fVar5 < fVar2)) << 8;
    if (fVar5 == fVar2) {
        // Second test with offset by local24 etc
        local3c = (int64)fStack_44 | ((int64)local48 << 32); // reassignment
        local48 = local48 + local24;
        fStack_44 = fStack_44 + local20;
        local34 = local40;
        local40 = local40 + local1c_2;
        fVar5 = FUN_006ca5e0(&local3c, &local48, localC);
        fVar2 = 1.0f;
        uVar3 = (ushort)(byte)(((fVar5 == fVar2) << 6) | ((isnan(fVar5) || isnan(fVar2)) << 2) | 2U | (fVar5 < fVar2)) << 8;
        if (fVar5 == fVar2) {
            // Third test using original target point with offset
            local34 = pTarget[2];
            int64 uVar1 = *(int64*)pTarget; // load target as 64-bit (xy packed)
            local3c._0_4_ = (float)uVar1;
            local3c._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
            local48 = (float)local3c + local30 + local18;
            fStack_44 = local3c._4_4_ + local2c + local14;
            local40 = local34 + local28 + local10;
            local3c = uVar1;
            fVar5 = FUN_006ca5e0(&local3c, &local48, localC);
            fVar2 = 1.0f;
            uVar3 = (ushort)((byte)(((fVar5 == fVar2) << 6) | ((isnan(fVar5) || isnan(fVar2)) << 2) | 2U | (fVar5 < fVar2))) | 1; // note: last call returns low byte with bit0 set
            if (fVar5 == fVar2) {
                return uVar3;
            }
        }
    }
    return uVar3 & 0xff00; // return only high byte if not equal on first two
}