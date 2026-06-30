// FUNC_NAME: RagdollPhysics::solveConstraintForces
void RagdollPhysics::solveConstraintForces(ConstraintParams* constraintParams)
{
    float* pfVar1;
    float fVar2;
    int iBoneIndex;
    char cBoneFlag;
    int iBoneOffset;
    int iBoneIdx;
    int* pConstraintArray;
    float fRand1;
    float* pfContact;
    float fContactForce;
    float fVec1, fVec2, fVec3;
    float fNormalLen, fInvNormalLen;
    float fDot1, fDot2, fDot3;
    float fAccumX, fAccumY, fAccumZ;
    float fBoneContact[2937]; // large buffer
    float* pfTemp1;
    float fTemp2;
    float fTemp3, fTemp4;
    float fBonePosX, fBonePosY, fBonePosZ;
    float fBoneVelX, fBoneVelY, fBoneVelZ;
    float fBoneMassInv;
    float fBoneInertiaInv;
    float fForce1, fForce2, fForce3;
    float fStack_4a0;
    float fStack_494;
    float fAccumulator[4];
    float fBoneContactArray[5]; // 5 floats
    float fStack_428, fStack_424;
    float fStack_420, fStack_41c, fStack_418, fStack_414, fStack_410;
    int uStack_40c;
    float fStack_408;
    int uStack_3fc;
    char acBoneActive[12];
    int iConstraintIndex;
    float afContactForces[60]; // 15*4?
    float afNormalized[6]; // 6 floats
    float afBoneForce[4];
    float fStack_2c8;
    float afBoneContactForces[9];
    char acBoneContactFlags[112]; // 112 bytes
    int uStack_230;
    char acWorldTransforms[12]; // 3 floats?
    char acBoneTransform[20];
    float fMatrix1[4];
    float fMatrix2[4];
    float fMatrix3[4];
    float fMatrix4[4];
    int uStack_1f0, uStack_1ec, uStack_1e8, uStack_1e4;
    char acOutTransform[64];
    float fTemp5[4];
    float fTransformOut[4];
    char acInTransform[16];
    float afBoneOutput[67];

    // Get timestep from constraint parameters (offset +0x08)
    fBoneMassInv = *(float*)(constraintParams + 8);
    // Scale initial forces by timestep (using bone mass from ESI[0x4c..0x53])
    fAccumX = (float)(this[0x4c] * fBoneMassInv);
    fAccumY = (float)(this[0x4d] * fBoneMassInv);
    fAccumZ = (float)(this[0x4e] * fBoneMassInv);
    fBonePosX = (float)(this[0x4f] * fBoneMassInv);
    fBonePosY = (float)(this[0x50] * fBoneMassInv);
    fBoneVelX = (float)(this[0x51] * fBoneMassInv);
    fBoneVelY = (float)(this[0x52] * fBoneMassInv);
    fBonePosZ = (float)(this[0x53] * fBoneMassInv);
    iBoneOffset = this[7]; // skeleton data pointer
    // Get ragdoll physics object (this[6]) offset 0xe0 and 0xd0
    int* pRagdollInternal = (int*)(this[6] + 0xe0);
    pConstraintArray = (int*)(this[6] + 0xd0);
    fBoneInertiaInv = *(float*)(constraintParams + 8);
    fRand1 = (float)FUN_009efd10(); // random value
    fBoneMassInv = fRand1 * fBoneInertiaInv;

    // Add random perturbation to initial forces
    int* pSkeleton = (int*)this[7]; // skeleton data
    fAccumX = *(float*)(pSkeleton + 0x10) * fBoneMassInv + fAccumX;
    fAccumY = *(float*)(pSkeleton + 0x14) * fBoneMassInv + fAccumY;
    fAccumZ = *(float*)(pSkeleton + 0x18) * fBoneMassInv + fAccumZ;
    fBonePosX = *(float*)(pSkeleton + 0x1c) * fBoneMassInv + fBonePosX;

    // Another random factor for opposite direction
    fRand1 = (float)FUN_009efd10();
    fRand1 = -fRand1;
    // Store random perturbation in local_440 as 4 floats (direction)
    fVec1 = fRand1 * *(float*)(pSkeleton + 0x10);
    fVec2 = fRand1 * *(float*)(pSkeleton + 0x14);
    fVec3 = fRand1 * *(float*)(pSkeleton + 0x18);
    fBonePosZ = fRand1 * *(float*)(pSkeleton + 0x1c);

    // Store timestep again
    fBoneMassInv = *(float*)(constraintParams + 8);

    // Call virtual functions on ragdoll internal object
    (*(code**)(pConstraintArray[0] + 0x58))();   // some update
    (*(code**)(pConstraintArray[0] + 0x48))();   // another update
    (*(code**)(pConstraintArray[0] + 0x50))(&fBonePosY); // store result

    // If there's a constraint object pointer (this[0x11]), call method
    if (this[0x11] != 0) {
        (**(code**)(*(int*)this[0x11] + 0xc))(fBonePosZ);
    }

    // Initialize accumulator arrays (2 groups of 24 floats each)
    float* pAccum = afNormalized + 6; // point to middle of array? Actually careful
    int iGroup = 2;
    do {
        // Clear 15 floats + 1 byte? Actually clearing 0x18 floats each iteration
        pAccum[-3] = 0.0f;
        pAccum[-4] = 0.0f;
        pAccum[-5] = 0.0f;
        pAccum[-6] = 0.0f;
        pAccum[1] = 0.0f;
        *pAccum = 0.0f;
        pAccum[-1] = 0.0f;
        pAccum[-2] = 0.0f;
        pAccum[5] = 0.0f;
        pAccum[4] = 0.0f;
        pAccum[3] = 0.0f;
        pAccum[2] = 0.0f;
        pAccum[8] = 0.0f;
        pAccum[9] = 0.0f;
        pAccum[10] = 0.0f;
        pAccum[0xb] = 0.0f;
        pAccum[0xc] = 0.0f;
        *(char*)(pAccum + 0xe) = 0;
        pAccum[6] = 0.0f;
        pAccum[7] = 0.0f;
        pAccum[0xd] = 0.0f;
        pAccum += 0x18;
        iGroup--;
    } while (iGroup != 0);

    // Compute velocity magnitude from ragdoll internal
    int* pPhys = (int*)this[6];
    float fVelSq = *(float*)(pPhys + 0x1a0) * *(float*)(pPhys + 0x1a0) +
                   *(float*)(pPhys + 0x1a4) * *(float*)(pPhys + 0x1a4) +
                   *(float*)(pPhys + 0x1a8) * *(float*)(pPhys + 0x1a8);
    float fVelMag = (float)FUN_00414a80(fVelSq); // sqrt
    fStack_420 = fVelMag;

    // Clear local variables
    fBoneVelX = 0.0f;
    fBoneVelY = 0.0f;
    fBonePosZ = 0.0f;

    // Loop over bone count (skeletonData[0x20] is count as char)
    pSkeleton = (int*)this[7];
    if (*(char*)(pSkeleton + 0x20) > 0) {
        fStack_4a0 = 0.0f; // accumulator for bone index
        fBonePosY = 0.0f;
        fBonePosX = 0.0f; // reusing as index
        do {
            // Get bone data pointer
            int* pBone = (int*)(this[0x12] + (int)fBonePosX); // bone array
            // Bone type index from skeleton data + offset 0x24
            int boneType = *(char*)(*(int*)(pSkeleton + 0x8c) + 0x24 + (int)fStack_4a0);
            // Get constraint info from global table
            int* pConstraintEntry = (int*)(DAT_01223480 + 0x24); // maybe a static array
            float fCx = *(float*)(pConstraintEntry + 0x14);
            float fCy = *(float*)(pConstraintEntry + 0x18);
            float fCz = *(float*)(pConstraintEntry + 0x10);
            float fCw = *(float*)(pConstraintEntry + 0x1c);
            fStack_428 = fCy*fCy + fCx*fCx + fCz*fCz; // magnitude squared
            float* pContactForce = (float*)0;
            // Get contact force from ESI[0x48] array
            fBonePosY = *(float*)(this[0x48] + (int)fStack_494 * 4);
            // Normalize the constraint direction
            if (fStack_428 != 0.0f) {
                float fInvMag = (float)(1.0f / FUN_00414a80(fStack_428));
                pContactForce = (float*)fInvMag;
            }
            // Compute contact impulse scaled by timestep and mass
            float fImpX = (1.0f - (float)pContactForce * fCz);
            float fImpY = (1.0f - fCx * (float)pContactForce);
            float fImpZ = (1.0f - fCy * (float)pContactForce);
            // Get bone world orientation from ragdoll internal
            float* pBoneOrientation = (float*)((int)fBonePosY + 0x10 + this[0x46]);
            fBoneInertiaInv = (pBoneOrientation[2] * fImpZ + pBoneOrientation[1] * fImpY +
                              fImpX * *pBoneOrientation) * fBonePosY * fBonePosY; // note: fBonePosY reused
            fBoneContact[0] = fImpZ * fBoneInertiaInv;
            fBoneContact[1] = fBoneInertiaInv * (float)pContactForce * fCw;
            // If contact force exceeds threshold, do something
            if (DAT_00e2b05c < fBonePosY) {
                int* pRagdoll = (int*)this[6];
                FUN_009f2000(); // debug or warning
                (**(code**)(*(int*)(pRagdoll + 0xd0) + 0x4c))(&fStack_4b8, pBone + 0x30);
            }
            // Check for additional contact pointer
            float** ppContact = (float**)((int)fBonePosY + 0x24 + this[0x46]);
            if (*ppContact != 0) {
                float* pContactData = *ppContact;
                float fContactImpulse;
                float fNormFactor = 1.0f - *(float*)(*(int*)(pSkeleton + 0x8c) + 0x1c + (int)fStack_4a0);
                fImpX = fNormFactor * fBoneInertiaInv * fImpX;
                fImpY = fNormFactor * fBoneInertiaInv * fImpY;
                fBoneContact[0] = fNormFactor * fBoneContact[0];
                fBoneContact[1] = fNormFactor * fBoneContact[1];
                // Randomize impulse direction
                float* pBoneData = (float*)(*(int*)(pSkeleton + 0x8c) + (int)fStack_4a0);
                fStack_494 = (float)FUN_009efd10();
                fContactImpulse = *(float*)(pBoneData + 0x20) * fStack_494 * fBonePosY; // timestep
                float fImpSq = fImpX*fImpX + fBoneContact[0]*fBoneContact[0] + fImpY*fImpY;
                if (fContactImpulse * fContactImpulse < fImpSq) {
                    // Normalize and scale
                    float fNorm = 0.0f;
                    if (fImpSq != 0.0f) {
                        fNorm = 1.0f / (float)FUN_00414a80(fImpSq);
                    }
                    fBoneContact[1] = fNorm * fBoneContact[1];
                    fBoneContact[0] = fNorm * fBoneContact[0];
                    fStack_494 = (float)FUN_009efd10();
                    fContactImpulse = *(float*)(pBoneData + 0x20) * fStack_494 * fBonePosY;
                    fBoneContact[0] = fContactImpulse * fBoneContact[0];
                    fBoneContact[1] = fContactImpulse * fBoneContact[1];
                }
                // Send contact impulse to ragdoll internal
                (**(code**)(pContactData[0x34] + 0x4c))(&fStack_4b8, pBone + 0x30);
                // Track best contact for each bone type
                if ((fBoneContactArray[boneType + 2] == 0.0) ||
                    ( fContactImpulse = *(float*)((int)fBoneContactArray[boneType + 2] + 0x19c),
                     pContactData[0x67] <= fContactImpulse &&
                     fContactImpulse != pContactData[0x67] )) {
                    fBoneContactArray[boneType + 2] = (float)pContactData;
                }
            }
            // Compute constraint velocity and add to accumulators
            int offset = this[0x46];
            float fBoneOff1 = *(float*)((int)fBonePosY + 0x14 + offset);
            float fBoneOff2 = *(float*)((int)fBonePosY + 0x18 + offset);
            float fBoneOff3 = *(float*)((int)fBonePosY + 0x10 + offset);
            float* pBonePos = (float*)((int)fBonePosY + offset);
            float fForceWeight = (*(float*)(this[0x49] + (int)fStack_494 * 4) +
                                 *(float*)(this[0x47] + (int)fStack_494 * 4)) /
                                *(float*)((int)fStack_4a0 + *(int*)(pSkeleton + 0x8c));
            // Cross product with bone axis
            fBoneContact[3] = fBoneOff1 * *(float*)(pBone + 0x88) - *(float*)(pBone + 0x84) * fBoneOff2;
            fBonePosY = fBoneOff3 * *(float*)(pBone + 0x84) - *(float*)(pBone + 0x80) * fBoneOff1;
            fBoneContact[4] = *(float*)(pBone + 0x80) * fBoneOff2 - fBoneOff3 * *(float*)(pBone + 0x88);
            // If angular velocity too small, use linear velocity instead
            if (fBoneContact[3]*fBoneContact[3] + fBonePosY*fBonePosY + fBoneContact[4]*fBoneContact[4] < DAT_00e44598) {
                int* pBoneAlt = (int*)this[0x12];
                float fAlt1 = *(float*)(pBoneAlt + 0x68 + (int)fBonePosX);
                float fAlt2 = *(float*)(pBoneAlt + 100 + (int)fBonePosX);
                float fAlt3 = *(float*)(pBoneAlt + 0x60 + (int)fBonePosX);
                fBoneContact[3] = *(float*)(pBone + 0x84) * fAlt1 - *(float*)(pBone + 0x88) * fAlt2;
                fBoneContact[4] = fAlt3 * *(float*)(pBone + 0x88) - *(float*)(pBone + 0x80) * fAlt1;
                fBonePosY = *(float*)(pBone + 0x80) * fAlt2 - fAlt3 * *(float*)(pBone + 0x84);
            }
            float fAngMagSq = fBoneContact[3]*fBoneContact[3] + fBonePosY*fBonePosY + fBoneContact[4]*fBoneContact[4];
            if (fAngMagSq == 0.0f) {
                fBonePosZ = 0.0f;
            } else {
                fBonePosZ = 1.0f / (float)FUN_00414a80(fAngMagSq);
            }
            pSkeleton = (int*)this[7];
            float fNormX = fBonePosZ * fBoneContact[3];
            float fNormY = fBonePosZ * fBonePosY;
            float fNormZ = fBonePosZ * fBoneContact[4];
            float fBoneWeight = fForceWeight; // from earlier
            // Compute torque axis
            float fTorqueX = pBonePos[6];
            float fTorqueY = pBonePos[5];
            float fTorqueZ = pBonePos[4];
            fStack_408 = fTorqueY * fNormX - fTorqueZ * fNormY;
            // Stiffness factor
            float fStiffness = DAT_00e2b1a4 / (float)(int)*(char*)(*(int*)(pSkeleton + 0x98) + (int)boneType);
            // Accumulate forces into afNormalized array for each bone type
            int boneGroup = boneType * 0x18;
            afNormalized[boneGroup] = pBonePos[0] * fStiffness + afNormalized[boneGroup];
            afNormalized[boneGroup + 1] = pBonePos[1] * fStiffness + afNormalized[boneGroup + 1];
            afNormalized[boneGroup + 2] = pBonePos[2] * fStiffness + afNormalized[boneGroup + 2];
            afNormalized[boneGroup + 3] = pBonePos[3] * fStiffness + afNormalized[boneGroup + 3];
            afNormalized[boneGroup + 7] = afNormalized[boneGroup + 7]; // no change?
            afNormalized[boneGroup + 4] = (fTorqueZ * fNormY - fTorqueY * fNormZ) + afNormalized[boneGroup + 4];
            afNormalized[boneGroup + 5] = afNormalized[boneGroup + 5] + (fTorqueX * fNormZ - fTorqueZ * fNormX);
            afNormalized[boneGroup + 6] = afNormalized[boneGroup + 6] + fStack_408;
            afNormalized[boneGroup + 8] = afNormalized[boneGroup + 8] + fNormX;
            afNormalized[boneGroup + 9] = afNormalized[boneGroup + 9] + fNormY;
            afNormalized[boneGroup + 10] = afNormalized[boneGroup + 10] + fNormZ;
            // Accumulate bone data into custom array
            *(float*)(acBoneContactFlags + boneGroup - 0x24) = *(float*)(acBoneContactFlags + boneGroup - 0x24) + fBonePosZ * 0.0;
            int* pSkelData = (int*)this[7];
            *(float*)(acBoneContactFlags + boneGroup - 0x18) = *(float*)(*(int*)(pSkelData + 0x8c) + 0xc + (int)fStack_4a0) * fBoneOff1 * fStiffness +
                *(float*)(acBoneContactFlags + boneGroup - 0x18);
            *(float*)(acBoneContactFlags + boneGroup - 0x14) = *(float*)(*(int*)(pSkelData + 0x8c) + 0x10 + (int)fStack_4a0) * fStiffness +
                *(float*)(acBoneContactFlags + boneGroup - 0x14);
            *(float*)(acBoneContactFlags + boneGroup - 0x10) = *(float*)(*(int*)(pSkelData + 0x8c) + 0x14 + (int)fStack_4a0) * fStiffness +
                *(float*)(acBoneContactFlags + boneGroup - 0x10);
            *(float*)(acBoneContactFlags + boneGroup - 0xc) = *(float*)(acBoneContactFlags + boneGroup - 0xc) + fBonePosY;
            *(float*)(acBoneContactFlags + boneGroup - 8) = *(float*)(acBoneContactFlags + boneGroup - 8) + fBoneWeight;
            // Calculate active flag for bone
            bool bActive = false;
            if ((acBoneContactFlags[boneGroup] != 0) || (*(char*)((int)fStack_494 + this[0x28]) != 0)) {
                bActive = true;
            }
            acBoneContactFlags[boneGroup] = bActive ? 1 : 0;
            pSkeleton = (int*)this[7];
            *(float*)(acBoneContactFlags + boneGroup - 4) = *(float*)((int)fStack_4a0 + 0x18 + *(int*)(pSkeleton + 0x8c)) * fStiffness * fStack_420 +
                *(float*)(acBoneContactFlags + boneGroup - 4);
            // Advance indices
            fBonePosX += 0xc0; // 192 bytes per bone
            fBonePosY += 0x40; // 64 bytes per bone
            fStack_4a0 += 0x28; // 40 bytes
            fStack_494 += 1.0f;
        } while ((int)fStack_494 < (int)*(char*)(pSkeleton + 0x20));
    }

    // After bone loop, copy world transform
    uStack_230 = *(int*)(this[7] + 0x70);
    // Now loop over all constraints (contact groups) count in ESI[7]+0x9c
    int contactCount = *(int*)(this[7] + 0x9c);
    if (0 < contactCount) {
        float* pContactAccum = afNormalized + 6;
        int iContact = 0;
        do {
            // Normalize linear force direction
            float fLinX = pContactAccum[-1];
            float fLinY = pContactAccum[-2];
            float fLinZ = *pContactAccum;
            float fLinMagSq = fLinY*fLinY + fLinX*fLinX + fLinZ*fLinZ;
            float fInvLinMag = 0.0f;
            if (fLinMagSq != 0.0f) {
                fInvLinMag = 1.0f / (float)FUN_00414a80(fLinMagSq);
            }
            pContactAccum[-2] = fInvLinMag * fLinY;
            pContactAccum[1] = fInvLinMag * pContactAccum[1];
            pContactAccum[-1] = fInvLinMag * fLinX;
            *pContactAccum = fInvLinMag * fLinZ;
            // Normalize angular force direction
            float fAngX = pContactAccum[4];
            float fAngY = pContactAccum[2];
            float fAngZ = pContactAccum[3];
            float fAngMagSq = fAngY*fAngY + fAngX*fAngX + fAngZ*fAngZ;
            float fInvAngMag = 0.0f;
            if (fAngMagSq != 0.0f) {
                fInvAngMag = 1.0f / (float)FUN_00414a80(fAngMagSq);
            }
            float fPrevContact = fBoneContactArray[(int)pContactAccum + 2]; // note: using pContactAccum as index
            pContactAccum[2] = fInvAngMag * fAngY;
            pContactAccum[3] = fInvAngMag * fAngZ;
            pContactAccum[4] = fInvAngMag * fAngX;
            pContactAccum[5] = pContactAccum[5] * fInvAngMag;
            // Store contact indices
            pContactAccum[6] = (float)(acBoneActive + iContact);
            pContactAccum[7] = (float)(acBoneActive + iContact);
            if (fPrevContact == 0.0) {
                acBoneActive[iContact] = 1;
                acBoneActive[iContact + 1] = 1;
                // Clear a 16-float block
                *(int*)((int)afContactForces + iContact + 0x2c) = 0;
                *(int*)((int)afContactForces + iContact + 0x28) = 0;
                *(int*)((int)afContactForces + iContact + 0x24) = 0;
                *(int*)((int)afContactForces + iContact + 0x20) = 0;
                *(int*)((int)afContactForces + iContact + 0xc) = 0;
                *(int*)((int)afContactForces + iContact + 8) = 0;
                *(int*)((int)afContactForces + iContact + 4) = 0;
                *(int*)((int)afContactForces + iContact) = 0;
                *(int*)((int)afContactForces + iContact + 0x1c) = 0;
                *(int*)((int)afContactForces + iContact + 0x18) = 0;
                *(int*)((int)afContactForces + iContact + 0x14) = 0;
                *(int*)((int)afContactForces + iContact + 0x10) = 0;
                *(int*)((int)afContactForces + iContact + 0x3c) = 0;
                *(int*)((int)afContactForces + iContact + 0x38) = 0;
                *(int*)((int)afContactForces + iContact + 0x34) = 0;
                *(int*)((int)afContactForces + iContact + 0x30) = 0;
                FUN_0045cbe0(); // initialize something
            } else if (*(char*)((int)fPrevContact + 0xd8) == '\a') {
                // If contact is a certain type, call virtual
                (**(code**)(*this + 0x34))(fPrevContact, acBoneActive + iContact);
            } else if (((int)pContactAccum < 1) || (fPrevContact != fBoneContactArray[2])) {
                // Compute world-space force from local-space constraint data
                int contactObj = (int)fPrevContact + 0xd0;
                FUN_00a1ba90(constraintParams, &contactObj, 1, 0, acBoneActive + iContact);
                float fFactor = *(float*)(contactObj + 0x6c);
                float fForce1 = fFactor * (*(float*)(contactObj + 0x60) - *(float*)(contactObj + 0x50));
                float fForce2 = fFactor * (*(float*)(contactObj + 100) - *(float*)(contactObj + 0x54));
                float fForce3 = fFactor * (*(float*)(contactObj + 0x68) - *(float*)(contactObj + 0x58));
                float fForce4 = fFactor * (*(float*)(contactObj + 0x6c) - *(float*)(contactObj + 0x5c));
                float fTorqueX = *(float*)(contactObj + 0xa0) * fFactor;
                float fTorqueY = *(float*)(contactObj + 0xa4) * fFactor;
                float fTorqueZ = *(float*)(contactObj + 0xa8) * fFactor;
                FUN_0055f7d0(acBoneActive + iContact); // transform matrix
                // Combine forces
                float fForceWorldX = *(float*)((int)afContactForces + iContact + 0x40) * fTorqueX +
                                     *(float*)((int)afContactForces + iContact + 0x60) * fTorqueZ +
                                     *(float*)((int)afContactForces + iContact + 0x50) * fTorqueY;
                float fForceWorldY = *(float*)((int)afContactForces + iContact + 0x44) * fTorqueX +
                                     *(float*)((int)afContactForces + iContact + 0x64) * fTorqueZ +
                                     *(float*)((int)afContactForces + iContact + 0x54) * fTorqueY;
                float fForceWorldZ = *(float*)((int)afContactForces + iContact + 0x48) * fTorqueX +
                                     *(float*)((int)afContactForces + iContact + 0x68) * fTorqueZ +
                                     *(float*)((int)afContactForces + iContact + 0x58) * fTorqueY;
                pContactAccum[7] = (float)(acInTransform + iContact);
                // Store result
                *(float*)((int)afBoneOutput + iContact + 0x10) = fForceWorldX;
                *(float*)((int)afBoneOutput + iContact + 0x14) = fForceWorldY;
                *(float*)((int)afBoneOutput + iContact + 0x18) = fForceWorldZ;
                *(int*)((int)afBoneOutput + iContact + 0x1c) = 0;
                *(float*)((int)afBoneOutput + iContact) = fForce1;
                *(float*)((int)afBoneOutput + iContact + 4) = fForce2;
                *(float*)((int)afBoneOutput + iContact + 8) = fForce3;
                *(float*)((int)afBoneOutput + iContact + 0xc) = fForce4;
            } else {
                // Copy previous results
                pContactAccum[6] = afBoneContactForces[1];
                pContactAccum[7] = afBoneContactForces[2];
            }
            pContactAccum += 0x18;
            iContact += 0x80; // 128 bytes
        } while (iContact < *(int*)(this[7] + 0x9c));
    }

    // Now process ragdoll internal transform
    fStack_420 = (float)(this[6] + 0xd0);
    FUN_00a1ba90(constraintParams, &fStack_420, 1, 0, acBoneTransform);
    int* pRagdoll = (int*)this[6];
    float fRagdollFactor = *(float*)(pRagdoll + 0x13c);
    float fForce1 = fRagdollFactor * (*(float*)(pRagdoll + 0x130) - *(float*)(pRagdoll + 0x120));
    float fForce2 = fRagdollFactor * (*(float*)(pRagdoll + 0x134) - *(float*)(pRagdoll + 0x124));
    float fForce3 = fRagdollFactor * (*(float*)(pRagdoll + 0x138) - *(float*)(pRagdoll + 0x128));
    float fForce4 = fRagdollFactor * (*(float*)(pRagdoll + 0x13c) - *(float*)(pRagdoll + 300));
    float fTorqueX = *(float*)(pRagdoll + 0x170) * fRagdollFactor;
    float fTorqueY = *(float*)(pRagdoll + 0x174) * fRagdollFactor;
    float fTorqueZ = *(float*)(pRagdoll + 0x178) * fRagdollFactor;
    float fTorqueW = *(float*)(pRagdoll + 0x17c) * fRagdollFactor;
    pSkeleton = (int*)this[7];
    uStack_1f0 = *(int*)(pSkeleton + 0x180);
    uStack_1ec = *(int*)(pSkeleton + 0x184);
    uStack_1e8 = *(int*)(pSkeleton + 0x188);
    uStack_1e4 = *(int*)(pSkeleton + 0x18c);
    FUN_0055f7d0(acBoneTransform);
    FUN_00aa2cd0(acOutTransform, &fTorqueX);
    pSkeleton = (int*)this[7];
    fMatrix1[0] = fForce1;
    fMatrix1[1] = fForce2;
    fMatrix1[2] = fForce3;
    fMatrix1[3] = fForce4;
    if (*(float*)(pSkeleton + 0x6c) != DAT_00e2b05c) {
        float fFactor = *(float*)(pSkeleton + 0x6c) * (float)this[0x2f] * fBonePosY; // fBonePosY is timestep?
        fForce1 = fForce1 + fFactor * *(float*)(pSkeleton + 0x30) * *(float*)(pSkeleton + 0x180);
        fForce2 = fForce2 + *(float*)(pSkeleton + 0x184) * *(float*)(pSkeleton + 0x34) * fFactor;
        fForce3 = fForce3 + *(float*)(pSkeleton + 0x188) * *(float*)(pSkeleton + 0x38) * fFactor;
        fForce4 = fForce4 + *(float*)(pSkeleton + 0x18c) * *(float*)(pSkeleton + 0x3c) * fFactor;
    }
    // Integrate motion
    fStack_420 = *(float*)(constraintParams + 8);
    fStack_41c = *(float*)(constraintParams + 0xc);
    FUN_00c024b0(&fStack_420, pSkeleton + 0xa4, afNormalized, this + 0x15);

    // Compute body force from constraints
    int* pPhys = (int*)this[6];
    fTorqueX = *(float*)(pPhys + 0x100) * fForce3 + *(float*)(pPhys + 0xf0) * fForce2 +
               fForce1 * *(float*)(pPhys + 0xe0);
    fTorqueY = *(float*)(pPhys + 0x104) * fForce3 + *(float*)(pPhys + 0xf4) * fForce2 +
               *(float*)(pPhys + 0xe4) * fForce1;
    fTorqueZ = *(float*)(pPhys + 0x108) * fForce3 + *(float*)(pPhys + 0xf8) * fForce2 +
               *(float*)(pPhys + 0xe8) * fForce1;
    fTorqueW = 0.0f;
    // Apply to ragdoll internal
    (**(code**)(*(int*)(pPhys + 0xd0) + 0x44))(&fTorqueX);
    (**(code**)(*(int*)(pPhys + 0xd0) + 0x40))(acBoneTransform);
    // Process constraints again for each contact
    if (0 < *(int*)(this[7] + 0x9c)) {
        float* pContact = afNormalized + 10;
        int iContact = 0;
        do {
            float fContactVal = fBoneContactArray[iContact];
            if ((fContactVal != 0.0) && (*(char*)((int)fContactVal + 0xd8) != '\a') &&
                ((iContact == 0) || (fBoneContactArray[0] != fBoneContactArray[1]))) {
                float* pConData = (float*)*pContact;
                float fCon1 = *(float*)((int)pConData + 0x24);
                float fCon2 = *(float*)((int)pConData + 0x28);
                float fCon3 = *(float*)((int)pConData + 0x20);
                float fPenalty = fStack_4a0 * DAT_00e39f98;
                float fObj1 = *(float*)((int)fContactVal + 0x1b8);
                float fObj2 = *(float*)((int)fContactVal + 0x1b4);
                float fPenalty1 = (pConData[0x58] * fCon2 + pConData[0x54] * fCon1 + fCon3 * pConData[0x50]) - *(float*)((int)fContactVal + 0x1b0);
                float fObj3 = *(float*)((int)fContactVal + 0x1bc);
                float fPenalty2 = (pConData[0x78] * fCon2 + pConData[0x70] * fCon3 + pConData[0x74] * fCon1) - fObj1;
                float fPenalty3 = (pConData[0x68] * fCon2 + pConData[0x60] * fCon3 + pConData[0x64] * fCon1) - fObj2;
                // Clamp penalties
                if (fPenalty <= fPenalty1) fPenalty1 = fPenalty;
                if (fPenalty <= fPenalty3) fPenalty3 = fPenalty;
                if (fPenalty <= fPenalty2) fPenalty2 = fPenalty;
                float fClampLow = 1.0f - fObj3;
                if (fPenalty <= (1.0f - fObj3)) fClampLow = fPenalty;
                float fClampHigh = 1.0f - fPenalty;
                if (fPenalty1 <= fClampHigh) fPenalty1 = fClampHigh;
                if (fPenalty3 <= fClampHigh) fPenalty3 = fClampHigh;
                if (fPenalty2 <= fClampHigh) fPenalty2 = fClampHigh;
                if (fClampLow <= fClampHigh) fClampLow = fClampHigh;
                // Apply corrected forces
                fPenalty2 = fPenalty2 + fObj1;
                fPenalty3 = fPenalty3 + fObj2;
                fClampLow = fClampLow + fObj3;
                fPenalty1 = fPenalty1 + *(float*)((int)fContactVal + 0x1b0);
                fStack_410 = *(float*)((int)fContactVal + 0x1a8);
                uStack_40c = *(int*)((int)fContactVal + 0x1ac);
                float fDiffX = pConData[0x10] - *(float*)((int)fContactVal + 0x1a0);
                float fDiffY = pConData[0x14] - *(float*)((int)fContactVal + 0x1a4);
                if (fPenalty <= fDiffX) fDiffX = fPenalty;
                if (fPenalty <= fDiffY) fDiffY = fPenalty;
                float fClampHigh2 = 1.0f - fPenalty;
                if (fDiffX <= fClampHigh2) fDiffX = fClampHigh2;
                if (fDiffY <= fClampHigh2) fDiffY = fClampHigh2;
                fDiffX = fDiffX + *(float*)((int)fContactVal + 0x1a0);
                float fResult = fDiffY + *(float*)((int)fContactVal + 0x1a4);
                // Apply final force
                fStack_454 = fClampHigh;
                fStack_44c = fClampHigh;
                fStack_424 = fClampLow;
                fStack_41c = fClampLow;
                (**(code**)(*(int*)((int)fContactVal + 0xd0) + 0x44))(&fPenalty1);
                (**(code**)(*(int*)((int)fContactVal + 0xd0) + 0x40))(&pContact);
            }
            pContact += 0x18;
            iContact++;
        } while (iContact < *(int*)(this[7] + 0x9c));
    }

    // Final update of bone velocities
    pSkeleton = (int*)this[7];
    if (*(char*)(pSkeleton + 0x20) > 0) {
        fBonePosX = 0.0f;
        fBonePosY = 0.0f;
        fStack_494 = 0.0f;
        do {
            int boneType = *(char*)(*(int*)(pSkeleton + 0x8c) + 0x24 + (int)fBonePosX);
            int* pBoneData = (int*)((int)fBonePosY + 0x24 + this[0x46]);
            int* pBone = (int*)(this[0x12] + (int)fStack_494);
            int* pConstraint = this + boneType * 9 + 0x15; // index into constraint arrays
            // Determine active constraint
            int activeConstraint = 0;
            if ((pBoneData == 0) || (*(char*)(pBoneData + 0xd8) != '\a')) {
                activeConstraint = 0;
            } else {
                activeConstraint = pConstraint[2];
            }
            pBone[0xa8] = activeConstraint;
            pBone[0xac] = pConstraint[3];
            pBone[0xb4] = pConstraint[1];
            pBone[0xb0] = *pConstraint;
            FUN_00aa2cd0(uStack_3fc, this[7] + 0x40);
            int* pRagdollPhys = (int*)this[6];
            if (*(char*)((int)this[0x28] + (int)fStack_494) == 0) {
                // Compute velocity from forces and orientation
                float fVel = *(float*)(pRagdollPhys + 0x1a4) * fStack_414 +
                             *(float*)(pRagdollPhys + 0x1a8) * fStack_410 +
                             fStack_418 * *(float*)(pRagdollPhys + 0x1a0) + *(float*)(pBone + 0xb0);
                if (fBoneContactArray[boneType] != 0.0) {
                    float fContactPos = afNormalized[boneType * 0x18 + 10];
                    fVel -= (*(float*)((int)fContactPos + 0x10) * fStack_418 +
                             *(float*)((int)fContactPos + 0x14) * fStack_414 +
                             *(float*)((int)fContactPos + 0x18) * fStack_410);
                }
                fVel /= *(float*)(*(int*)(pSkeleton + 0x8c) + (int)fBonePosX);
                *(float*)(pBone + 0xa0) = fVel;
                *(float*)(pBone + 0xa4) = fVel * fStack_4a0 + *(float*)(pBone + 0xa4);
            } else {
                *(int*)(pBone + 0xa0) = 0;
            }
            pSkeleton = (int*)this[7];
            fStack_494 += 0xc0;
            fBonePosY += 0x40;
            fBonePosX += 0x28;
        } while ((int)fStack_494 < (int)*(char*)(pSkeleton + 0x20));
    }
    return;
}