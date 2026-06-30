// FUNC_NAME: Character::updateAnimationInfluences

void Character::updateAnimationInfluences()
{
    int* piVar1;
    float fVar2;
    byte bVar3;
    ushort uVar4;
    int iVar5;
    int iVar6;
    bool bVar7;
    char cVar8;
    int iVar9;
    int iVar10;
    uint uVar11;
    int unaff_FS_OFFSET;
    uint64_t uVar12;
    undefined8 uVar13;
    int local_48;
    int local_44;
    float local_40;          // Maximum influence distance
    float local_38;          // Minimum influence distance
    float local_2c;          // Retrieved influence position/distance
    float local_28;          // Max distance from influence
    float local_24;          // Min distance from influence
    float afStack_20[8];     // Array of influence distances

    // Check if character state allows influence processing (not in death/disabled states)
    if ((*(uint*)(this + 0x0C) & 0x20300000) != 0)
        return;

    local_40 = 0.0f;
    bVar7 = false;
    local_38 = DAT_00e2e50c;       // Some large initial value (probably FLT_MAX)

    iVar9 = getCurrentPlayerIndex();   // FUN_004e9fa0
    iVar5 = **(int**)(unaff_FS_OFFSET + 0x2C);  // Game state manager (e.g., GameState)
    uVar4 = *(ushort*)(iVar5 + 0x10);         // Game phase flags
    local_48 = 0;
    iVar10 = (uint)(*(int*)(iVar5 + 0x34) != 0) * 0x98; // If local player exists, base offset = 0x98

    if (0 < *(int*)(iVar10 + 4 + iVar9))      // Number of influence sources for this slot
    {
        local_44 = 0;
        do {
            uVar11 = *(uint*)(*(int*)(this + 0x10) + 0x14); // Influence mask from animation state
            piVar1 = (int*)(local_44 + iVar10 + 0xC + iVar9); // Pointer to current influence source entry
            afStack_20[local_48] = DAT_00e44758; // Default sentinel value (e.g., -1.0f)

            if ((uVar11 & 0x800) == 0)
            {
                LAB_0051bd6b:
                bVar3 = *(byte*)(*(int*)(this + 0x10) + 0x1D); // Filter flags for this character

                // Check if influence source is applicable:
                // - bVar3 is 0 (no filter), or source's filter matches, or has game phase flag
                if ((((bVar3 == 0) || (piVar1[2] == 0)) || (((byte)piVar1[2] & bVar3) != 0)) &&
                    ((*(uint*)(this + 0x84) & (uint)uVar4) == (uint)uVar4))
                {
                    uVar12 = getObjectID();  // FUN_004e8f70 - current object's unique ID (64-bit)
                    iVar10 = *piVar1;       // Source object ID (32-bit?)

                    // Complex ID matching; simplified: if IDs match with sign handling or special flags
                    if (idsMatch(iVar10, uVar12) || (hasSpecialFlag(uVar12) && iVar10 != (int)uVar12))
                    {
                        cVar8 = FUN_0051b5f0(iVar10, &local_2c); // Get influence position/distance
                        if (cVar8 != 0) {
                            afStack_20[local_48] = local_2c;
                            bVar7 = true;
                        }
                        // Track min/max distances
                        if (local_40 <= local_28)
                            local_40 = local_28;
                        if (local_24 <= local_38)
                            local_38 = local_24;
                    }
                }
            }
            else
            {
                // Influence source is a reference-counted object handle
                iVar10 = *(int*)(this + 0x20);
                if (iVar10 != 0)
                    *(int*)(iVar10 + 4) = *(int*)(iVar10 + 4) + 1; // Increment ref count
                iVar10 = getObjectFromHandle(iVar10);  // FUN_004e8550
                if (iVar10 == 0)
                    goto LAB_0051bd6b;

                // Check if this handle is already in a list within the object (avoid duplicates)
                uVar11 = 0;
                if (*(uint*)(iVar10 + 0x18) != 0)
                {
                    do {
                        if (*(int*)(iVar10 + 8 + uVar11 * 4) == piVar1[1]) // Compare handle IDs
                        {
                            if (uVar11 != 0xFFFFFFFF)
                                goto LAB_0051bd6b;
                            break;
                        }
                        uVar11 = uVar11 + 1;
                    } while (uVar11 < *(uint*)(iVar10 + 0x18));
                }
                // If not found, fall through to normal processing
                goto LAB_0051bd6b;
            }

            local_44 = local_44 + 0x10;     // Next entry (each 0x10 bytes)
            local_48 = local_48 + 1;
            iVar10 = (uint)(*(int*)(iVar5 + 0x34) != 0) * 0x98;
        } while (local_48 < *(int*)(iVar10 + 4 + iVar9));
    }

    // Apply max influence distance if global flag allows or character has specific state
    if ((DAT_0120551d == 0) || ((*(uint*)(this + 0x0C) & 0x400000) != 0))
    {
        FUN_0051b4d0(this, local_40);  // Set character's max influence distance
    }

    if (bVar7)
    {
        // Apply all non-default influences
        iVar10 = 0;
        if (0 < *(int*)((uint)(*(int*)(iVar5 + 0x34) != 0) * 0x98 + 4 + iVar9))
        {
            do {
                fVar2 = afStack_20[iVar10];
                if (fVar2 != DAT_00e44758)
                {
                    uVar13 = getObjectID();  // Current object ID
                    iVar6 = *(int*)((uint64_t)uVar13 >> 0x20); // Upper 32 bits of ID
                    bVar3 = *(byte*)(*(int*)(this + 0x10) + 0x1D);
                    if (((iVar6 == (int)uVar13) == (bool)(bVar3 >> 3 & 1)) ||
                        (((bVar3 & 0xF7) != 0 && (iVar6 != (int)uVar13))))
                    {
                        FUN_0051b9f0(this, iVar6, fVar2);  // Apply influence to character
                    }
                }
                iVar10 = iVar10 + 1;
            } while (iVar10 < *(int*)((uint)(*(int*)(iVar5 + 0x34) != 0) * 0x98 + 4 + iVar9));
        }

        uVar11 = *(uint*)(this + 0x0C);
        *(undefined2*)(this + 0x82) = 0;  // Reset some short flag

        // Update state flags based on conditions
        if ((((uVar11 & 0x40000) != 0) && ((uVar11 & 1) != 0)) &&
            (*(uint*)(this + 0x0C) = uVar11 & 0xFFFBFFFF, (uVar11 & 0x80000) != 0))
        {
            *(uint*)(this + 0x0C) = uVar11 & 0xFFF3FFFF;
            if (((uVar11 & 1) != 0) && ((*(uint*)(*(int*)(this + 0x10) + 0x14) & 0x20000000) != 0))
            {
                *(uint*)(this + 0x0C) = uVar11 & 0xFFF3FFFF | 0x80000000;
            }
            FUN_0051b0b0(this); // Reset/reinitialize influence system
        }
    }
    return;
}