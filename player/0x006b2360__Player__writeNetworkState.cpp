// FUNC_NAME: Player::writeNetworkState
unsigned int __thiscall Player::writeNetworkState(unsigned int* outBuffer)
{
    bool bVar1;
    float fVar2;
    unsigned int uVar3;

    // Copy position vector? (offset 0x38, 0x3C, 0x40)
    outBuffer[0] = *(unsigned int*)(this + 0x38); // +0x38: likely mPosX
    outBuffer[1] = *(unsigned int*)(this + 0x34) & 0x17DA17FD; // +0x34: mFlags, cleared bits
    outBuffer[2] = *(unsigned int*)(this + 0x40); // +0x40: mPosZ? or mAngularVel?
    outBuffer[3] = *(unsigned int*)(this + 0x3C); // +0x3C: mPosY

    if (*(int*)(this + 0x16C) == 4) // +0x16C: mPlayerState (e.g., InCar, Dead?)
    {
        outBuffer[4] = 3; // Override state to 3 (e.g., InVehicle)
        uVar3 = 3;
    }
    else
    {
        outBuffer[4] = *(int*)(this + 0x16C); // +0x16C: mPlayerState
        outBuffer[5] = *(unsigned int*)(this + 0x170); // +0x170: mStateTime? mStateData?

        if ((*(int*)(this + 0x16C) != 0) || (((byte)(*(unsigned int*)(this + 0x34) >> 0x1C) & 1) != 0))
            goto LAB_006b23f5;

        bVar1 = (*(unsigned int*)(this + 0x34) >> 0x12 & 1) == 0; // bit 18 of flags
        if (!bVar1)
        {
            outBuffer[1] = outBuffer[1] | 0x80000; // Set bit 19
        }

        if ((*(byte*)(this + 0x36) & 1) == 0) // byte at +0x36, low bit
        {
            if (bVar1) goto LAB_006b23f5;
        }
        else
        {
            outBuffer[1] = outBuffer[1] | 0x20000; // Set bit 17
        }

        outBuffer[4] = 1; // Override state to 1 (e.g., Ground)
        uVar3 = 1;
    }

    // Convert state index to some float (e.g., state time or animation blend)
    fVar2 = (float)FUN_006b20f0(uVar3);
    outBuffer[5] = *(unsigned int*)&fVar2; // reinterpret cast

LAB_006b23f5:
    outBuffer[6] = 0; // Padding/placeholder
    outBuffer[7] = *(unsigned int*)(this + 0x5C); // +0x5C: mHealth? or mVelocity?
    outBuffer[8] = *(unsigned int*)(this + 0x60); // +0x60: mArmor? or mSpeed?
    outBuffer[9] = *(unsigned int*)(this + 0x68); // +0x68: mMaxHealth?
    outBuffer[10] = *(unsigned int*)(this + 0x6C); // +0x6C: mMaxArmor?
    outBuffer[11] = *(unsigned int*)(this + 0x74); // +0x74: mCurrentWeapon?
    outBuffer[12] = *(unsigned int*)(this + 0x7C); // +0x7C: maybe mWeaponAmmo?
    outBuffer[13] = *(unsigned int*)(this + 0x80); // +0x80: mWeaponReserve?
    outBuffer[14] = *(unsigned int*)(this + 0x88); // +0x88: mSomeTimer?
    outBuffer[15] = *(unsigned int*)(this + 0xA0); // +0xA0: mScore?
    outBuffer[16] = *(unsigned int*)(this + 0x64); // +0x64: mKills? or mMoney?
    unsigned int uVar3_2 = *(unsigned int*)(this + 200); // +0xC8: mSomeNetworkID?
    outBuffer[17] = uVar3_2;
    outBuffer[18] = 0; // Padding
    outBuffer[19] = *(unsigned int*)(this + 0x174); // +0x174: mStateTimer?
    outBuffer[20] = *(unsigned int*)(this + 0x178); // +0x178: mAnimationID?
    outBuffer[21] = 0; // Padding/zero
    outBuffer[22] = 0;
    outBuffer[23] = 0;

    return 0x60; // Size of packed data (96 bytes)
}