// FUNC_NAME: Vehicle::applyDamping
uint __thiscall Vehicle::applyDamping(float dt) {
    uint uVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;

    float one = DAT_00e44564; // constant, likely 1.0f
    if (flags & 0x01) { // offset +0x30 byte, maybe "mIsSleeping" or "mIsActive"
        // Copy target velocity to current velocity
        mVelX = mTargetVelX;
        mVelY = mTargetVelY;
        mVelZ = mTargetVelZ;
        mVelW = mTargetVelW;
        // Check flags at +0xe4
        uint flags2 = *reinterpret_cast<uint*>(this + 0xe4);
        // Bit 1 == 0 and (bit 5 != 0 or periodic check)
        if (((flags2 >> 1) & 1) == 0 &&
            (((flags2 >> 5) & 1) != 0 ||
             (DAT_01205220 % *reinterpret_cast<uint*>(this + 0xb8) == 0))) {
            // Attempt to apply additional damping
            if (hasExternalInput()) { // FUN_00550b80
                float magSq = mVelX*mVelX + mVelY*mVelY + mVelZ*mVelZ;
                float mag = fastSqrt(magSq); // FUN_00414a80
                if (mag < DAT_00e2d99c) { // threshold
                    fVar2 = mSpeedFactor * DAT_00e44868; // offset +0x84 maybe "mSpeedFactor"
                    mVelX = mDirX * fVar2;
                    mVelY = mDirY * fVar2;
                    mVelZ = mDirZ * fVar2;
                    mVelW = mDirW * fVar2;
                }
                *reinterpret_cast<uint*>(this + 0xe4) |= 0x20; // set bit 5
                return uVar1;
            } else {
                *reinterpret_cast<uint*>(this + 0xe4) &= ~0x20; // clear bit 5
                return uVar1;
            }
        }
        return uVar1;
    } else {
        // Normal damping
        fVar4 = *reinterpret_cast<float*>(this + 0xa0); // some factor, maybe "mDampingScale"
        // Compute damped velocities
        fVar3 = one - *reinterpret_cast<float*>(this + 0x80) * *reinterpret_cast<float*>(this + 0x90) * fVar4 * dt;
        fVar5 = one - *reinterpret_cast<float*>(this + 0x94) * *reinterpret_cast<float*>(this + 0x84) * fVar4 * dt;
        // Update velocity components
        mVelX += fVar3;
        mVelY += fVar5;
        mVelZ += (one - *reinterpret_cast<float*>(this + 0x98) * *reinterpret_cast<float*>(this + 0x88) * fVar4 * dt);
        // Compute magnitude
        float magSq = mVelX*mVelX + mVelY*mVelY + mVelZ*mVelZ;
        uVar1 = fastSqrt(magSq); // returns float as uint? Actually should be float, but treat as uint for now
        fVar2 = *reinterpret_cast<float*>(this + 0x10) * *reinterpret_cast<float*>(this + 0x84); // some product
        if (fVar2 < fastSqrt(magSq)) { // can't reconstruct order exactly
            fVar2 = one - fVar2;
            mVelX = *reinterpret_cast<float*>(this + 0x90) * fVar2;
            mVelY = *reinterpret_cast<float*>(this + 0x94) * fVar2;
            mVelZ = *reinterpret_cast<float*>(this + 0x98) * fVar2;
            *reinterpret_cast<float*>(this + 0x7c) = *reinterpret_cast<float*>(this + 0x9c) * fVar2;
        }
        return uVar1;
    }
}