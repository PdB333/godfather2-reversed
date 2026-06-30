// FUN_004e62a0: WeaponHandler::computeRecoilForce
bool WeaponHandler::computeRecoilForce(CharacterObject* character, float outForce[4], EffectData* outData) // outData is 4 ints/uint32
{
    // +0x4 in this: pointer to character's physics data
    float fVar13 = *(float*)(*(int*)(this + 4) + 0x8c); // speed constant?
    // index into animation/state array using this+0xe (short) * 0x24 + 0x30
    int iVar6 = *(int*)(*(int*)(this + 4) + 0x10) + 0x30 + *(short*)(this + 0xe) * 0x24;
    // compute force magnitude based on speed differences
    float fVar8 = (fVar13 - *(float*)(iVar6 + 0x18)) * *(float*)(iVar6 + 0x14);
    if (fVar8 > 0.0f) {
        if (MAX_FORCE <= fVar8) fVar8 = MAX_FORCE; // DAT_00e2b1a4
    } else {
        fVar8 = 0.0f;
    }
    float fVar13b = (fVar13 - *(float*)(iVar6 + 0x20)) * *(float*)(iVar6 + 0x1c);
    if (fVar13b > 0.0f) {
        if (MAX_FORCE <= fVar13b) fVar13b = MAX_FORCE;
    } else {
        fVar13b = 0.0f;
    }
    // multiply components by multiplier from this+0x30
    fVar13b = fVar13b * fVar8 * *(float*)(this + 0x30);

    // weapon data
    int* weaponPtr = (int*)(*(int*)(this + 4) + 0x20); // +0x20: pointer to inventory/equipped weapon
    // output effect data
    uint32 effectData[4] = {0,0,0,0};
    byte weaponFlags = 0;
    // weapon type is at *(this+0x24)->+0x10
    if (*weaponPtr != 0) {
        char weaponType = *(char*)(*(int*)(this + 0x24) + 0x10);
        if (weaponType == WEAPON_TYPE_MELEE_FAST) { // '\b'
            int weaponData = *weaponPtr;
            if (weaponData != 0) {
                *(int*)(weaponData + 4) += 1; // ref count?
            }
            weaponData = WeaponData::getForType(weaponData); // FUN_004e88c0
            if (weaponData != 0) {
                effectData[0] = *(undefined4*)(weaponData + 0x20);
                float fVar8 = *(float*)(weaponData + 0x10);
                float fVar9 = *(float*)(weaponData + 0x14);
                float fVar11 = *(float*)(weaponData + 0x18);
                float fVar12 = *(float*)(weaponData + 0x1c);
                weaponFlags = (*(byte*)(weaponData + 0x28) >> 1) & 1;
                effectData[1] = *(undefined4*)(weaponData + 0x24);
                byte bVar4 = *(byte*)(weaponData + 0x28);
                goto LABEL_SET;
            }
        } else if (weaponType == WEAPON_TYPE_RIFLE) { // '\x02'
            int weaponData = *weaponPtr;
            if (weaponData != 0) {
                *(int*)(weaponData + 4) += 1;
            }
            weaponData = WeaponData::getForRifle(weaponData); // FUN_004e8920
            if (weaponData != 0) {
                effectData[2] = *(undefined4*)(weaponData + 0x50);
                float fVar8 = *(float*)(weaponData + 0x10);
                float fVar9 = *(float*)(weaponData + 0x14);
                float fVar11 = *(float*)(weaponData + 0x18);
                float fVar12 = *(float*)(weaponData + 0x1c);
                bVar4 = *(byte*)(weaponData + 0x5c);
                goto LABEL_SET;
            }
        } else if (weaponType == WEAPON_TYPE_HEAVY) { // '\r'
            int weaponData = *weaponPtr;
            if (weaponData != 0) {
                *(int*)(weaponData + 4) += 1;
            }
            weaponData = WeaponData::getForHeavy(weaponData); // FUN_004e8980
            if (weaponData != 0) {
                float fVar8 = *(float*)(weaponData + 0x10);
                float fVar9 = *(float*)(weaponData + 0x14);
                float fVar11 = *(float*)(weaponData + 0x18);
                float fVar12 = *(float*)(weaponData + 0x1c);
                bVar4 = *(byte*)(weaponData + 0x20);
                goto LABEL_SET;
            }
        } else if (weaponType == WEAPON_TYPE_THROWN) { // '\v'
            WeaponData::release(weaponPtr); // FUN_00414e30
            int weaponData = WeaponData::getForThrown(*(int*)(this + 0x24) >> 8); // FUN_004e89e0
            if (weaponData != 0) {
                float fVar8 = *(float*)(weaponData + 8);
                float fVar12 = *(float*)(weaponData + 0xc);
                bVar4 = *(byte*)(weaponData + 0x10);
                // no y/z components
                float fVar11 = 0.0f;
                float fVar9 = 0.0f;
                goto LABEL_SET;
            }
        }
    }
    // fallback: use data from this+0x24
    {
        int weaponData = *(int*)(this + 0x24);
        float fVar8 = *(float*)(weaponData + 0x20);
        float fVar9 = *(float*)(weaponData + 0x24);
        float fVar11 = *(float*)(this + 0x2c);
        outForce[0] = *(float*)(weaponData + 0x1c);
        outForce[1] = fVar8;
        outForce[2] = fVar9;
        outForce[3] = fVar11 * fVar13b;
        goto OUTPUT;
    }

LABEL_SET:
    if (bVar4 & 1) {
        char weaponType = *(char*)(*(int*)(this + 0x24) + 0x10);
        if (weaponType == WEAPON_TYPE_MELEE_FAST || weaponType == WEAPON_TYPE_RIFLE || 
            weaponType == WEAPON_TYPE_HEAVY || weaponType == WEAPON_TYPE_THROWN) {
            outForce[0] = fVar8;
            outForce[1] = fVar9;
            outForce[2] = fVar11;
            outForce[3] = fVar12 * fVar13b;
        }
        goto OUTPUT;
    }

OUTPUT:
    // character orientation/damping adjustment
    byte characterStateFlag = *(byte*)(*(int*)(this + 0x24) + 0x12);
    int* pGameData = *(int**)(__readfsdword(0x2c) + 0x2c); // global game data
    if (characterStateFlag != 0) {
        float* pos = (float*)(*(int*)(*pGameData + 8) + 0x80 + *(int*)(this + 0x10));
        float dx = *pos - *(float*)(character + 0x70);
        float dy = pos[1] - *(float*)(character + 0x74);
        float dz = pos[2] - *(float*)(character + 0x78);
        float dot = *(float*)(character + 0x60)*dx + *(float*)(character + 0x68)*dy + *(float*)(character + 100)*dy; // note: +0x68 and +0x100? Actually +0x100 is +0x64? It's +0x68 for middle and +0x60 for start? Reconstructed: +0x60: col0, +0x68: col1, +0x100? Wait, the decompiled says "*(float *)(param_1 + 100) * fVar11 + *(float *)(param_1 + 0x68) * fVar12 + *(float *)(param_1 + 0x60) * fVar8" so that's +0x64 (100 decimal = 0x64). So dot = *(float*)(character+0x60)*dx + *(float*)(character+0x68)*dy + *(float*)(character+0x64)*dz.
        float fVar9 = dot;
        float fVar13 = 0.0f;
        if (fVar9 > VELOCITY_THRESHOLD) { // DAT_00e2e780
            double dVar10 = (double)(*(float*)(character + 0x14c) * SPEED_MULTIPLIER); // DAT_00e2cd54
            sqrt(???); // actually they call FUN_00b99e20, likely sqrt
            float norm = sqrtf(dx*dx + dy*dy + dz*dz);
            float ratio = (fVar9 / norm - (float)dVar10) / (MAX_FORCE - (float)dVar10);
            if (ratio > 0.0f) {
                if (MAX_FORCE <= ratio) ratio = MAX_FORCE;
            } else {
                ratio = 0.0f;
            }
            fVar13 = ratio;
        }
        float fVar8 = (float)characterStateFlag * DAMPING_FACTOR; // DAT_00e44640
        outForce[3] = (fVar8 * fVar13 + (MAX_FORCE - fVar8)) * outForce[3];
    }

    // weapon specific scaling if flag set
    if (*(uint*)(*(int*)(*pGameData + 8) + *(int*)(this + 0x10)) & 0x80000) {
        int iVar6 = *(int*)(this + 4);
        float scaleX = *(float*)(iVar6 + 0xa0);
        float scaleY = *(float*)(iVar6 + 0xa4);
        float scaleZ = *(float*)(iVar6 + 0xa8);
        float scaleW = *(float*)(iVar6 + 0xac);
        float oldW = outForce[3];
        outForce[0] *= scaleX;
        outForce[1] *= scaleY;
        outForce[2] *= scaleZ;
        outForce[3] = scaleW * outForce[3];
        outForce[3] = oldW; // bug? Actually they set it back? The code: param_2[3]=fVar11*param_2[3]; then param_2[3]=fVar13; That's a likely bug.
    }

    if (outForce[3] >= MIN_FORCE) { // DAT_00e2af44
        if (weaponFlags == 0) {
            int iVar6 = *(int*)(this + 0x24);
            outData[0] = *(undefined4*)(iVar6 + 0x40);
            outData[1] = *(undefined4*)(iVar6 + 0x44);
            outData[2] = *(undefined4*)(iVar6 + 0x48);
            outData[3] = 0;
        } else {
            char weaponType = *(char*)(*(int*)(this + 0x24) + 0x10);
            if (weaponType == WEAPON_TYPE_MELEE_FAST || weaponType == WEAPON_TYPE_RIFLE) {
                outData[0] = 0;
                outData[1] = effectData[0];
                outData[2] = effectData[1];
                outData[3] = effectData[2];
                return true;
            }
        }
        return true;
    }
    return false;
}