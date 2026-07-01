// FUNC_NAME: Entity::updatePathMovement

void __thiscall Entity::updatePathMovement(Entity* this, uint32_t arg2, uint32_t arg3)
{
    float fVar1;
    int iVar2;
    int iVar3;
    int local_90;
    uint32_t local_8c;
    float* local_88;
    int local_84;
    uint32_t local_80;
    float* local_7c;
    float local_78;
    float local_74;
    float local_70;
    Vector3 local_6c; // 8 bytes? Actually 12 bytes? But decompiled shows undefined8 + undefined4, so likely 12 bytes
    uint32_t local_64;
    float local_60;
    float local_5c;
    float local_58;
    uint32_t local_54;
    uint8_t local_48[12]; // path result buffer
    int local_3c;
    int local_38;
    float* local_34; // current path node position
    float* local_30; // previous path node position
    uint32_t local_2c;
    uint8_t local_24[32]; // some buffer

    // Check flag at bit 11 of field at +0xc88
    if ((this->flags & 0x800) == 0) {
        // Use custom path from navigation component at +0xf44
        iVar2 = FUN_005faf10(this + 0xf44); // likely getPathObject
    } else {
        // Use global path from singleton
        iVar2 = *(int*)(DAT_0112af68 + 0x194);
    }

    if (iVar2 != 0) {
        iVar3 = FUN_00471610(); // getGameManager or world
        // Copy transform or position from manager
        local_6c = *(Vector3*)(iVar3 + 0x30);
        local_64 = *(uint32_t*)(iVar3 + 0x38);

        // Setup path query with current position, path object, flags, and args
        FUN_0085f280(&local_6c, iVar2, this->flags & 0xFFFFF700, arg2, arg3);

        // Get path result into local_48
        FUN_00602490(&local_6c, local_48, local_2c);

        if (local_34 == nullptr) {
            // No path nodes, set callback to default and start following
            this->pathCallback = FUN_005fe070; // default callback
            FUN_00601760(this + 0xf44, &local_6c, 0, 0); // startPathFollowing
            this->pathCallback = FUN_00867d40; // restore callback
        } else {
            // Compute direction from previous node to current node
            local_78 = *local_34 - *local_30;
            local_74 = local_34[1] - local_30[1];
            local_70 = local_34[2] - local_30[2];
            local_54 = 0;
            local_60 = local_78;
            local_5c = local_74;
            local_58 = local_70;

            // Normalize the direction vector
            FUN_0056afa0(&local_60, &local_60); // normalizeVector

            local_78 = local_60;
            local_74 = local_5c;
            local_70 = local_58;

            // Build linked list for path smoothing (local_84 and local_90)
            local_84 = 0;
            local_80 = 0;
            if (local_3c != 0) {
                local_84 = local_3c;
                local_80 = *(uint32_t*)(local_3c + 4);
                *(int**)(local_3c + 4) = &local_84;
            }
            local_7c = local_34;
            local_90 = 0;
            local_8c = 0;
            if (local_38 != 0) {
                local_90 = local_38;
                local_8c = *(uint32_t*)(local_38 + 4);
                *(int**)(local_38 + 4) = &local_90;
            }
            local_88 = local_30;

            // Apply path smoothing with direction
            FUN_00600a40(&local_84, local_24, &local_78, 0, &local_90);

            // Free temporary lists
            if (local_90 != 0) {
                FUN_004daf90(&local_90);
            }
            if (local_84 != 0) {
                FUN_004daf90(&local_84);
            }
        }
    }

    // Compute speed factor from field at +0x1100, clamp to minimum
    fVar1 = this->speedFactor; // +0x1100
    if (fVar1 <= DAT_00d58cbc) {
        fVar1 = DAT_00d58cbc;
    }

    // Set time scale or speed based on global constant divided by factor
    FUN_00600210(DAT_00d75cd4 / fVar1, 0, 0, 0);

    // Post-update cleanup
    FUN_008659a0();
}