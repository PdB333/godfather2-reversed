// FUNC_NAME: Player::checkTargetVisibility
uint __fastcall Player::checkTargetVisibility(Player* this) {
    float fVar1, fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    bool bVar10;
    uint in_EAX;
    int iVar11, iVar12, iVar13, iVar14, iVar15, iVar16;
    float fVar18;

    // Check if bits 6 and 7 of state flags are set (0x6c)
    if ((*(byte*)(this + 0x6c) & 0xc0) != 0) {
        // Get two entities (e.g., player and target) from global function
        iVar11 = getSomeEntity();  // FUN_00471610
        iVar12 = getSomeEntity();
        fVar1 = *(float*)(iVar12 + 0x30); // target position x
        fVar2 = *(float*)(iVar11 + 0x30); // player position x
        fVar3 = *(float*)(iVar12 + 0x34); // target y
        fVar4 = *(float*)(iVar11 + 0x34); // player y
        fVar5 = *(float*)(iVar12 + 0x38); // target z
        fVar6 = *(float*)(iVar11 + 0x38); // player z

        // Get camera or aiming object
        in_EAX = getAimingObject(); // FUN_008fa210
        if (in_EAX != 0) {
            // Choose range based on bit 7 of state flags
            if ((*(uint*)(this + 0x6c) >> 7 & 1) == 0) {
                fVar18 = *(float*)(in_EAX + 0x8c); // range from aiming object
            } else {
                fVar18 = *(float*)(in_EAX + 4);    // alternative range
            }

            // Get more entities for orientation vectors
            iVar11 = getSomeEntity();
            iVar12 = getSomeEntity();
            iVar13 = getSomeEntity();
            fVar7 = *(float*)(iVar12 + 0x24); // orientation component
            fVar8 = *(float*)(iVar11 + 0x20);
            fVar9 = *(float*)(iVar13 + 0x28);

            // Get additional entities for dot product calculation
            iVar11 = getSomeEntity();
            iVar12 = getSomeEntity();
            iVar13 = getSomeEntity();
            iVar14 = getSomeEntity();
            iVar15 = getSomeEntity();
            iVar16 = getSomeEntity();

            // Compute dot product of two orientation vectors
            bVar10 = (*(float*)(iVar14 + 0x24) * *(float*)(iVar13 + 0x24) +
                      *(float*)(iVar12 + 0x20) * *(float*)(iVar11 + 0x20) +
                      *(float*)(iVar16 + 0x28) * *(float*)(iVar15 + 0x28)) < 0.0f;

            if (bVar10) {
                // If dot product negative, adjust range and set flags
                fVar18 = DAT_00e44564 - *(float*)(in_EAX + 100); // some global minus aiming object value
                *(uint*)(this + 0x6c) |= 0x80;   // set bit 7
                *(uint*)(this + 0x6c) &= 0xffffffbf; // clear bit 6
            }

            in_EAX = *(uint*)(this + 0x6c);
            // Check if bit 6 is set and a global threshold, then compare distance
            if ((((in_EAX >> 6 & 1) == 0) || (*(uint*)(this + 0xb0) <= DAT_01205224)) &&
                (fVar18 <= fVar7 * (fVar3 - fVar4) + fVar8 * (fVar1 - fVar2) + fVar9 * (fVar5 - fVar6))) {
                // Target is within cone/distance
                if ((in_EAX >> 7 & 1) != 0) {
                    if (bVar10) {
                        *(uint*)(this + 0x6c) |= 0x200; // set bit 9
                        return 1; // success with high byte set
                    }
                    *(uint*)(this + 0x6c) &= 0xfffffdff; // clear bit 9
                }
                return 1; // success
            }
        }
    }
    return 0; // failure
}