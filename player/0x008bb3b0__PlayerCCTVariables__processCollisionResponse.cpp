// FUNC_NAME: PlayerCCTVariables::processCollisionResponse
undefined4 __thiscall PlayerCCTVariables::processCollisionResponse(
    PlayerCCTVariables *this,
    float *collisionNormal,       // param_2: likely collision normal (3 floats stored as undefined4)
    float *contactVelocity)       // param_3: likely contact velocity or displacement
{
    float *pVelocityLocal;
    int *pSomeObject;
    hkpCharacterProxy *proxy;
    int iVar2;
    undefined4 uVar3;
    byte bFlags;
    byte bTemp1;
    byte bTemp2;
    code *pVFTable;
    double dAccum;
    float fLength;
    float fNormalY;
    float fNormalZ;
    float fNormalX;
    float fInvLength;
    float **ppfCrossResult;
    float afQuaternion[4]; // afStack_78
    uint uMasked;
    float fDotOrMag;
    undefined4 uStack_60;
    undefined4 uStack_5c;
    undefined4 uStack_58;
    undefined4 uStack_54;
    float fCosAngle;
    undefined4 uStack_4c;
    float fLocal[4];
    int iStack_7c;
    float fStack_50;
    float fStack_3c;
    float fStack_64;

    // Save return address for stack trace (debug)
    // piStack_b4 = (int *)0x8bb3c8; (removed in reconstruction)

    // Call vtable entry 0x7c (offset 31) on this (likely update or step)
    (this->vtable[0x7c >> 2])();

    // Set flag 0x800 in flags at offset +0x18c (99*4)
    this->m_flags |= 0x800;

    // Get pointer to character proxy from member at +0x130 (0x4c*4)
    proxy = (hkpCharacterProxy *)this->m_pCharacterProxy;

    if (proxy != NULL) {
        // pSomeObject = (int *)this->m_pCharacterProxy; // but it's reused
        // Call vtable offset 0x40 (initialize or step)
        proxy->vtable[0x40 >> 2]();

        // Get some ID or random value
        uVar3 = FUN_0043b490(); // likely random or some hash
        // Transform values for something
        uVar3 = FUN_00540c60(8, 0x15, uVar3);
        // Dispatch message to proxy
        (proxy->vtable[0x44 >> 2])(0xb49c1276, uVar3);
        // Another dispatch with different ID
        (proxy->vtable[0x40 >> 2])(0x9e0761a2, 0);

        // Extract collision normal (param_2 is three floats stored as undefined4)
        float normalX = *(float *)&collisionNormal[0];
        float normalY = *(float *)&collisionNormal[1];
        float normalZ = *(float *)&collisionNormal[2];

        // Extract contact velocity (param_3 is float*)
        fNormalX = contactVelocity[0];
        fNormalY = contactVelocity[1];
        fNormalZ = contactVelocity[2];

        // Compute squared length of contact velocity
        fLength = fNormalZ * fNormalZ + fNormalY * fNormalY + fNormalX * fNormalX;

        // Initialize output quaternion (afStack_78) and some other variables
        // fStack_3c, fStack_50, fStack_64 are set to a global constant (likely 1.0)
        fStack_3c = _DAT_00d5780c; // 1.0f?
        fStack_50 = _DAT_00d5780c;
        fStack_64 = _DAT_00d5780c;
        afQuaternion[0] = _DAT_00d5780c;
        afQuaternion[3] = 0.0f;
        uMasked = 0;

        // Initialize rest of quaternion to zero
        afQuaternion[1] = 0.0f;
        afQuaternion[2] = 0.0f;
        uStack_60 = 0;
        uStack_5c = 0;
        uStack_58 = 0;
        uStack_54 = 0;
        uStack_4c = 0;

        // Normalize contact velocity
        fInvLength = 0.0f;
        if (fLength != 0.0f) {
            fInvLength = _DAT_00d5780c / SQRT(fLength);
        }

        // Scale contact velocity components
        fNormalZ = fNormalZ * fInvLength;
        // The following lines compute cross product with zero? Actually it's incomplete due to missing multiplies in decompilation.
        // Probably intended: compute perpendicular vector to contact velocity.
        // We'll reconstruct with typical physics response:
        // Compute cross product between contact velocity and collision normal? Or something else.
        // The decompilation shows many zero multiplies, likely due to missing variables.
        // For now, keep as is but note it's a simplified version.
        // The code computes:
        // fVar9 = fVar10 * fVar8 * 0.0; -> 0
        // fVar12 = fVar8 * fVar11 * 0.0; -> 0
        // piStack_b4 = (int *)(fVar12 - fStack_a0 * 0.0); -> 0
        // fVar10 = fVar9 - fVar8 * fVar11; -> -fVar8*fVar11
        // fStack_30 = (float)((uint)fVar10 & DAT_00e44680); -> absolute value (mask sign)
        // similar for others
        // This part calculates absolute values of the normalized components and compares to threshold.

        float fTempX = -fInvLength * fNormalX; // actually fVar10 = -fVar8*fVar11 => -fInvLength * fNormalX? But fNormalX is from param3? Wait, after scaling, fNormalX is the original x of contact velocity? Actually the code uses fVar11 = *param_3 (original x), then later fVar10 = fVar9 - fVar8 * fVar11. Since fVar9 is 0, fVar10 = -fVar8 * fVar11 = -fInvLength * contactVelocity[0]. So fVar10 = -norm_x. And fStack_30 = absolute value of that.
        // Similarly, pfStack_b8 = (float *)(fStack_a0 - fVar9) = fNormalZ - 0 = fNormalZ (scaled z), but then it's cast to uint and masked. So absolute value of scaled z.
        // And piStack_b4 = (int *)(fVar12 - fStack_a0 * 0.0) = 0, so that axis is zero.

        // Actually the code sets piStack_b4 = (int*)(0 - 0) = 0. Then later uses (float)piStack_b4 which is 0.
        // So the cross product effectively has only two non-zero components? This is messy.

        // To keep reconstruction accurate, I'll just mimic the decompiled code exactly.

        float absNegNormX = (float)((uint)(-fInvLength * contactVelocity[0]) & DAT_00e44680);
        float absScaledZ = (float)((uint)(fNormalZ) & DAT_00e44680); // fNormalZ is scaled z
        // piStack_b4 is zero, so abs of zero is zero.
        float absZero = 0.0f;

        // Compare to threshold DAT_00d5efb8
        bTemp2 = 8; // initial flag for z component
        if (DAT_00d5efb8 < absScaledZ) {
            bTemp2 = 0;
        }
        if (DAT_00d5efb8 < absZero) {
            bTemp1 = 0;
        } else {
            bTemp1 = 4;
        }
        if (DAT_00d5efb8 < absNegNormX) {
            bFlags = 0;
        } else {
            bFlags = 2;
        }

        byte combinedFlags = bFlags | bTemp1 | bTemp2;

        if (combinedFlags == 0x0E) {
            // All components above threshold? Use null pointer
            pVFTable = proxy->vtable[0x58 >> 2];
            ppfCrossResult = NULL;
        } else {
            dAccum = (double)(fInvLength * 0.0 * 0.0 + 0.0 + 0.0 + fNormalZ); // sum of scaled components? Actually it's sum of all scaled components? Since most are zero.
            // Call some math function
            FUN_00b9b988(); // maybe sin/cos?
            // Compute squared magnitude of cross product vector (which is basically (absNegNormX, 0, absScaledZ)?)
            float mag2 = (absNegNormX * absNegNormX) + (absZero * absZero) + (absScaledZ * absScaledZ);
            float invMag = 0.0f;
            if (mag2 != 0.0f) {
                invMag = _DAT_00d5780c / SQRT(mag2);
            }
            pVFTable = proxy->vtable[0x58 >> 2];
            ppfCrossResult = &absScaledZ; // pointer to the array? Actually the code takes address of pfStack_b8 which is &fStack_a0, but fStack_a0 was the scaled z. So it's a pointer to the z component.
            // Then scale the cross product components by some factor
            absScaledZ = this->m_fScale * (float)dAccum * invMag * absScaledZ; // this->m_fScale is at param_1[0x7e] (0x1f8)
            // piStack_b4 is presumably treated similarly, but it's zero.
        }

        // Call vtable function 0x58 on proxy with afQuaternion, contactVelocity, and ppfCrossResult
        (pVFTable)(afQuaternion, contactVelocity, ppfCrossResult);
    }

    // After proxy handling, do additional work with global object
    // Get pointer to global singleton? DAT_012233a0
    int *pGlobal = *(int **)(DAT_012233a0 + 4);
    int iSomeOffset;
    if (pGlobal == 0) {
        iSomeOffset = 0;
    } else {
        iSomeOffset = *pGlobal + -0x1f30;
    }

    // Set up some kind of function pointer structure
    undefined4 *pFuncRef = &PTR_FUN_00d5dbbc;
    undefined4 someId = 0x9d305abf;
    if (iSomeOffset == 0) {
        iSomeOffset = 0;
    } else {
        iSomeOffset = iSomeOffset + 0x48;
    }

    // Copy a float from iSomeOffset+4 into afQuaternion[0]
    afQuaternion[0] = 0.0f;
    if (iSomeOffset != 0) {
        afQuaternion[0] = *(float *)(iSomeOffset + 4);
        *(int **)(iSomeOffset + 4) = &iSomeOffset; // overwrite pointer? circular?
    }

    // Initialize rest of quaternion to zero
    afQuaternion[3] = 0.0f;
    afQuaternion[2] = 0.0f;
    afQuaternion[1] = 0.0f;

    // Use local variable as a linked list node? (pppuStack_9c = &pFuncRef)
    // Call several functions
    FUN_00408a00();
    FUN_00894c90();
    FUN_008b9e20(this + 0x71); // likely a sub-object at offset 0x1c4

    if (iSomeOffset != 0) {
        FUN_004daf90();
    }

    return 1;
}