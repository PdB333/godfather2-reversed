// FUNC_NAME: Projectile::updateProjectilePath
void Projectile::updateProjectilePath(void* targetData) {
    FUN_00533cc0();
    *unaff_ESI = &PTR_FUN_00e37560;
    unaff_ESI[9] = 0;
    if (*(char *)(unaff_EDI + 0xd) != '\0') {
        return;
    }
    int* weaponData = unaff_ESI[1] + 0x20;
    if (weaponData != 0) {
        *(int *)(weaponData + 4) += 1;
    }
    struct ImpactInfo* impact = (struct ImpactInfo*)FUN_004f2ce0(weaponData);
    if (impact != 0) {
        // Copy source position (0x10-0x1c) and target position (0x20-0x2c) from impact
        unaff_ESI[0xc] = impact->sourceX;
        unaff_ESI[0xd] = impact->sourceY;
        unaff_ESI[0xe] = impact->sourceZ;
        unaff_ESI[0xf] = impact->sourceW;
        unaff_ESI[0x10] = impact->targetX;
        unaff_ESI[0x11] = impact->targetY;
        unaff_ESI[0x12] = impact->targetZ;
        unaff_ESI[0x13] = impact->targetW;
        unaff_ESI[0x14] = DAT_01205228;

        float dx = (float)unaff_ESI[0xe] - (float)unaff_ESI[0x12];
        float dy = (float)unaff_ESI[0xd] - (float)unaff_ESI[0x11];
        float dz = (float)unaff_ESI[0xc] - (float)unaff_ESI[0x10];
        float distance = SQRT(dx*dx + dy*dy + dz*dz);

        if (DAT_00e2b1a4 <= distance) {
            float* maxRange = (float*)(targetData + 0x10);
            if (*maxRange <= DAT_00e44598 && DAT_00e44598 != *maxRange) {
                *maxRange = DAT_00e44598;
            }
            float normalizedDist = distance / *maxRange;
            bool exceedsThreshold = DAT_01217ab0 < normalizedDist;
            unaff_ESI[0x16] = normalizedDist;
            if (exceedsThreshold) {
                unaff_ESI[0x15] = unaff_ESI[0x14];
                unaff_ESI[9] = (int)targetData;
                uint slotId = FUN_004e9270();
                if ((((slotId != 0) && (slotId != 0xffffffff)) && (slotId < 0x1000)) &&
                   ((slotId * 0x38 != -0x11a0f28 &&
                    (int* refCount = *(int **)(&DAT_011a0f38 + slotId * 0x38)) != 0))) {
                    *refCount += 1;
                }
                FUN_004f2100(unaff_ESI, targetData, *(void**)(unaff_ESI[1] + 0x10), slotId,
                             unaff_ESI[4], unaff_ESI[5]);
                return;
            }
        }
    }
    *(char *)(unaff_EDI + 0xc) = 1;
}