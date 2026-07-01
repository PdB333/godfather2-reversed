// Xbox PDB: EARS_Modules_TargetingReticuleManager_ShowFreeAimReticule
// FUNC_NAME: HUDTargetingManager::updateTargeting
void __thiscall HUDTargetingManager::updateTargeting(int this, int playerData)
{
    int screen;
    int *piVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    int iVar5;
    undefined4 uVar6;
    int *piVar7;
    int offsetPos; // local_48
    int newElementPtr; // local_44
    undefined4 colorR; // local_40
    undefined4 colorG; // local_3c
    undefined4 colorB; // local_38
    undefined4 colorA; // local_34
    undefined4 someFlag; // local_30
    int screenBase; // local_2c
    undefined4 someID; // local_28
    undefined4 *ptrToColor; // local_24
    undefined1 buffer[28]; // local_20

    // Check if already initialized (bit 2 of flags at +0x10)
    if ((*(uint *)(this + 0x10) >> 2 & 1) == 0) {
        // Call initialization helper
        FUN_0081dce0();
        // Get screen/renderer object (0 = primary screen)
        screen = FUN_004262f0(0);
        // Copy color data from this object (offsets +0x108, +0x10c, +0x110) and global
        colorR = *(undefined4 *)(this + 0x108);
        colorG = *(undefined4 *)(this + 0x10c);
        colorB = *(undefined4 *)(this + 0x110);
        colorA = _DAT_00d5780c; // global default alpha
        // Calculate screen position offset (screen + 0x40)
        offsetPos = screen + 0x40;
        screenBase = screen;

        if ((playerData == 0) ||
           ((((*(int *)(playerData + 0x4d0) == 0 && (*(int *)(playerData + 0x4dc) == 0)) &&
             (*(int *)(playerData + 0x4d8) == 0)) && (*(int *)(playerData + 0x4dc) == 0)))) {
            // No player data or all targeting slots empty -> create free-aim and center reticles
            ptrToColor = &colorR;
            someID = 0xffffffff;
            someFlag = 5;
            FUN_004eacb0("hud_targeting_freeaim");
            piVar7 = (int *)FUN_004df3c0(&newElementPtr, buffer, offsetPos, 0x1ff, 0, &someFlag);
            // Store pointer at +0xe8 (free-aim reticle)
            piVar2 = (int *)(this + 0xe8);
            if (*(int *)(this + 0xe8) != 0) {
                *(undefined4 *)(*(int *)(this + 0xe8) + 8) = 0;
                *piVar2 = 0;
            }
            iVar5 = *piVar7;
            *piVar2 = iVar5;
            if (iVar5 != 0) {
                *(int **)(iVar5 + 8) = piVar2;
                *piVar7 = 0;
            }
            if (newElementPtr != 0) {
                *(undefined4 *)(newElementPtr + 8) = 0;
            }

            // Create center reticle
            ptrToColor = &colorR;
            someID = 0xffffffff;
            someFlag = 5;
            screenBase = screen;
            FUN_004eacb0("hud_targeting_center");
            piVar7 = (int *)FUN_004df3c0(&newElementPtr, buffer, offsetPos, 0x1ff, 0, &someFlag);
            // Store pointer at +0xec (center reticle)
            piVar2 = (int *)(this + 0xec);
            if (*(int *)(this + 0xec) != 0) {
                *(undefined4 *)(*(int *)(this + 0xec) + 8) = 0;
                *piVar2 = 0;
            }
            iVar5 = *piVar7;
            *piVar2 = iVar5;
            if (iVar5 != 0) {
                *(int **)(iVar5 + 8) = piVar2;
                *piVar7 = 0;
            }
            if (newElementPtr != 0) {
                *(undefined4 *)(newElementPtr + 8) = 0;
            }

            // Update texture/material for the free-aim reticle (stored at +0x100)
            FUN_004df830(*(undefined4 *)(this + 0x100));
            iVar5 = *(int *)(this + 0x100);
            uVar6 = *(undefined4 *)(this + 0x24);
            uVar3 = *(undefined4 *)(this + 0x28);
            uVar4 = *(undefined4 *)(this + 0x2c);
            // Copy position/vector data from +0x20-0x2c to the texture object at +0x10-0x1c
            *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(this + 0x20);
            *(undefined4 *)(iVar5 + 0x14) = uVar6;
            *(undefined4 *)(iVar5 + 0x18) = uVar3;
            *(undefined4 *)(iVar5 + 0x1c) = uVar4;
        }
        else {
            // Player data exists and has targeting info -> create from that data
            ptrToColor = &colorR;
            someID = 0xffffffff;
            someFlag = 5;
            uVar6 = FUN_004df270(&offsetPos, (int *)(playerData + 0x4d0), offsetPos, 0x1ff, 0, &someFlag);
            FUN_00414db0(uVar6);
            if (offsetPos != 0) {
                *(undefined4 *)(offsetPos + 8) = 0;
            }
        }

        // Update texture/material for the center reticle (stored at +0xfc)
        FUN_004df830(*(undefined4 *)(this + 0xfc));
        iVar5 = *(int *)(this + 0xfc);
        uVar6 = *(undefined4 *)(this + 0x24);
        uVar3 = *(undefined4 *)(this + 0x28);
        uVar4 = *(undefined4 *)(this + 0x2c);
        // Copy position/vector data from +0x20-0x2c to the texture object at +0x10-0x1c
        *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(this + 0x20);
        *(undefined4 *)(iVar5 + 0x14) = uVar6;
        *(undefined4 *)(iVar5 + 0x18) = uVar3;
        *(undefined4 *)(iVar5 + 0x1c) = uVar4;

        // Set initialization flag (bit 2 at +0x10)
        *(uint *)(this + 0x10) = *(uint *)(this + 0x10) | 4;

        // If there's a child object at +0x14, update it as well
        if (*(int *)(this + 0x14) != 0) {
            FUN_0081dd40(*(int *)(this + 0x14));
        }
    }
    return;
}