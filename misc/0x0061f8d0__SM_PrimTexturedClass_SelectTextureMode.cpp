// Xbox PDB: SM_PrimTexturedClass::SelectTextureMode
// FUNC_NAME: ScreenOverlay::updateEffect
// Function at 0x0061f8d0: Updates a layered screen-space effect (e.g., dirt/rain overlay) with LOD and mode switching.
// param_1 (this): ScreenOverlay instance
// param_2: render context (camera or scene handle)

void __thiscall ScreenOverlay::updateEffect(int thisPtr, int renderContext)
{
    ushort uVar1;
    ushort uVar2;
    ushort uVar3;
    float fVar5;
    float fVar6;
    float fVar7;
    int *piVar8;
    char cVar9;
    uint uVar10;
    float *pfVar11;
    uint uVar12;
    int iVar13;
    undefined local_58[40]; // temporary buffer for texture/bind operation
    undefined local_30;
    undefined local_14;
    
    // Process three overlay layers (textures/effects)
    iVar13 = 0;
    do {
        // Prepare overlay layer: get texture handle from array at +0xB0 (3 slots)
        FUN_00606fd0(*(undefined4 *)(thisPtr + 0xB0 + iVar13 * 4), 2, 0, local_58);
        // Get layer transform data from render context at +0x20 (3 slots)
        undefined4 uVar4 = *(undefined4 *)(renderContext + 0x20 + iVar13 * 4);
        // Set layer transform (e.g., texture coordinates, scale)
        FUN_00614ed0(local_14, local_30, uVar4, uVar4);
        // Apply layer to rendering pipeline
        FUN_006071a0(local_58);
        iVar13 = iVar13 + 1;
    } while (iVar13 < 3);
    
    // Extract integer speeds from offset +0xCC and +0xD0, convert to float
    fVar5 = (float)*(int *)(thisPtr + 0xCC); // speedX (int -> float)
    if (*(int *)(thisPtr + 0xCC) < 0) {
        fVar5 = fVar5 + DAT_00e44578; // handle negative by adding a base value (likely float constant)
    }
    fVar6 = (float)*(int *)(thisPtr + 0xD0); // speedY
    if (*(int *)(thisPtr + 0xD0) < 0) {
        fVar6 = fVar6 + DAT_00e44578;
    }
    
    // Read tiling factors (ushort) at +0xD6, +0xD8, +0xDA
    uVar1 = *(ushort *)(thisPtr + 0xD6); // tileX
    uVar2 = *(ushort *)(thisPtr + 0xD8); // tileY
    uVar3 = *(ushort *)(thisPtr + 0xDA); // tileZ or depth
    
    fVar7 = fVar6 - DAT_00e2cd54; // offset for speed
    fVar5 = fVar5 * DAT_00e2cd54 - DAT_00e2cd54; // scale and offset
    fVar6 = fVar6 * DAT_00e2cd54 - DAT_00e2cd54;
    
    // LOD bias configuration
    DAT_01127774 = DAT_01127884; // copy global LOD settings
    fVar5 = fVar5 * DAT_00e2cd54 - DAT_00e2cd54; // repeated? might be a typo in decompilation
    fVar6 = fVar6 * DAT_00e2cd54 - DAT_00e2cd54;
    DAT_01127868 = FUN_0060a580(DAT_01127884, "lodBias"); // get LOD bias parameter
    
    if ((DAT_012058e8 == &PTR_PTR_01127760) && // some global state pointer check
        (FUN_0060a460(DAT_01127774), piVar8 = DAT_01205750, DAT_01127868 != 0)) {
        uVar12 = DAT_01127868 & 0xff;
        uVar10 = DAT_01127868 & 0x80000000;
        if (uVar10 == 0) {
            pfVar11 = (float *)(&DAT_011d97f0 + uVar12 * 0x10);
        } else {
            pfVar11 = (float *)(&DAT_011ea8f0 + uVar12 * 0x10);
        }
        // Update LOD bias value if changed
        if (*pfVar11 != DAT_01127840) {
            iVar13 = *DAT_01205750;
            *pfVar11 = DAT_01127840;
            if (uVar10 == 0) {
                (**(code **)(iVar13 + 0x1b4))(piVar8, uVar12, pfVar11, 1); // set parameter
            } else {
                (**(code **)(iVar13 + 0x178))(); // fallback
            }
        }
    }
    
    // Set effect shader parameters (e.g., scroll speed, tiling)
    FUN_00619a50(
        *(undefined4 *)(thisPtr + 0xB8), // parameter A
        *(undefined4 *)(thisPtr + 0xBC), // parameter B
        fVar7 / (float)uVar1, // speedX / tileX
        fVar5 / (float)uVar2, // scrollX / tileY
        fVar6 / (float)uVar3  // scrollY / tileZ
    );
    
    // Store first overlay layer handle globally (for later use)
    DAT_011f4230 = *(undefined4 *)(thisPtr + 0xB0);
    
    // Mode-dependent update (mode at +0xDC: 0 = normal, 1 = special)
    if (*(int *)(thisPtr + 0xDC) == 0) {
        // Normal mode: reset some flags and update transform matrices
        DAT_011f4234 = 0;
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 1;
        if (DAT_012058d0 < 7) {
            DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
            DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 0;
        FUN_006103f0(thisPtr + 0x10, thisPtr + 0x50, thisPtr + 0x30); // set overlay transforms (matrices)
        if (DAT_012058d0 < 7) {
            DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
            DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 1;
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
    } else if (*(int *)(thisPtr + 0xDC) != 1) {
        goto LAB_0061fc50; // unknown mode, skip to callback
    } else {
        // Mode 1: special (e.g., intense overlay like car dirt)
        DAT_011f4234 = 1;
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
        if (0x1a < DAT_00f15988) {
            DAT_00f15988 = 0x1b;
        }
        _DAT_011f3a44 = 1;
        cVar9 = FUN_004166b0(); // check debug overlay flag
        if ((cVar9 != '\0') && ((DAT_011f7430 & 1) != 0)) {
            FUN_00614a50(); // reload shaders or effect
        }
        FUN_006103f0(thisPtr + 0x10, thisPtr + 0x50, thisPtr + 0x30); // update transforms
        // Initialise some global float constants (e.g., color or intensity)
        _DAT_011f69b0 = DAT_00e2b1a4;
        _DAT_011f69b4 = 0;
        _DAT_011f69b8 = 0;
        uRam011f69bc = 0;
        _DAT_011f69c0 = 0;
        _DAT_011f69c4 = DAT_00e2b1a4;
        _DAT_011f69c8 = 0;
        uRam011f69cc = 0;
        _DAT_011f69d0 = 0;
        _DAT_011f69d4 = 0;
        _DAT_011f69d8 = DAT_00e2b1a4;
        uRam011f69dc = 0;
        _DAT_011f69e0 = 0;
        uRam011f69e4 = 0;
        uRam011f69e8 = 0;
        uRam011f69ec = DAT_00e2b1a4;
        if ((DAT_011f7430 & 1) != 0) {
            FUN_00614a50();
        }
        if (DAT_012058d0 < 0x1b) {
            DAT_012058d0 = 0x1b;
        }
    }
    
    // Common post-mode adjustments
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0;

LAB_0061fc50:
    // Update effect owner/callback
    if (*(int *)(thisPtr + 200) == 0) {
        *(int *)(thisPtr + 200) = renderContext; // store new context
        return;
    }
    // If callback exists, notify old context
    if (*(code **)(thisPtr + 0xC0) != (code *)0x0) {
        (**(code **)(thisPtr + 0xC0))(*(int *)(thisPtr + 200), *(undefined4 *)(thisPtr + 0xC4));
        *(int *)(thisPtr + 200) = renderContext;
        return;
    }
    *(int *)(thisPtr + 200) = renderContext;
    return;
}