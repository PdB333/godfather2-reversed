// FUNC_NAME: Noname_0x005cf9a0
// Address: 0x005cf9a0 - Godfather II Minimap Icon Drawing Function (EARS Engine)
// Likely part of MinimapRenderer or MapIconRenderer class.
// Draws map icons with various flags: visibility, highlight, size, child recursion.
// Uses a global brightness decay system for pulsing/alpha effects.

// Note: Many global variables are referenced; some are temp state for brightness/color.
// The function processes a node structure (param_2) with coordinates and flags.

int __thiscall MinimapRenderer_InternalDraw(int this, int* node, int renderContext, int param4, int param5)
{
    int* textureData;
    int iVar1;
    float fVar2;
    char cVar3;
    int* piVar4;
    uint uVar5;
    uint uVar6;
    int extraout_ECX;
    uint uVar7;
    float fVar8;
    float fVar9;
    uint color;
    float radius;
    float fX1, fY1, fX2, fY2;
    float fScaleX1, fScaleY1;
    float fScaleX2, fScaleY2;
    uint local_5c;
    float local_58;
    float local_50;
    float local_4c;
    float local_48;
    uint local_44;
    float local_40;
    float local_3c;
    float local_38;
    uint local_34;
    int rectX1, rectY1, rectX2, rectY2;
    int local_28;
    int local_24;
    int local_20;
    int local_1c;
    uint local_18;
    uint local_14;

    // Get texture/renderable data from the node's resource handle
    // FUN_005ce530 likely retrieves a texture or icon data pointer
    piVar4 = (int*)FUN_005ce530(*node);
    
    // Validate: texture type != 8 (maybe font?) and texture pointer is non-zero
    if ((piVar4[1] != 8) && (*piVar4 != 0))
    {
        // Flag 0x40: likely "hidden" - bail out early
        if ((node[6] & 0x40) != 0)
        {
            return 1;
        }
        
        // Flag 0x80000: has children? Recurse into child nodes (offset +0x24 = 0x90 bytes)
        if ((node[6] & 0x80000) != 0)
        {
            // Recursive call for each child? This call with node+0x24 (child list?)
            cVar3 = MinimapRenderer_InternalDraw(node + 0x24, renderContext, param4, param5);
            if (cVar3 == '\0')
            {
                return 0;
            }
            // Re-fetch texture data after recursion
            piVar4 = (int*)FUN_005ce530(*node);
            if (piVar4[1] == 8)
            {
                return 0;
            }
            if (*piVar4 == 0)
            {
                return 0;
            }
        }
        
        // Copy node rectangle coordinates (int -> int)
        local_20 = node[1]; // x1
        local_1c = node[2]; // y1
        local_30 = node[3]; // x2
        local_2c = node[4]; // y2
        
        // Default padding/alignment values (likely zero from global)
        local_18 = 0;
        local_14 = DAT_00e2b1a4;  // global zero?
        local_28 = 0;
        local_24 = DAT_00e2b1a4;
        
        // Flag 0x80: draw background/underlay?
        if ((*(byte*)(node + 6) & 0x80) != 0)
        {
            // Scale radius based on some multiplier and random color
            fVar2 = *(float*)(*node + 8) * DAT_00e2cd48;
            uVar5 = FUN_005d07d0(); // random color
            FUN_005c4960(); // save/push state?
            FUN_005cf730(piVar4, uVar5, fVar2, fVar2, renderContext, param4, param5);
        }
        
        fVar2 = DAT_0119d0bc; // current brightness/alpha global
        
        // Flag 0x200: draw as a "pulse" circle?
        if ((node[6] & 0x200) != 0)
        {
            // Brightness decay logic: if below threshold, decay faster
            if ((DAT_0119d0bc < DAT_00e2b118) &&
                (DAT_0119d0bc = DAT_0119d0bc * DAT_00e2b04c - DAT_00e2b118, DAT_0119d0bc < 0.0))
            {
                DAT_0119d0bc = 0.0;
            }
            local_58 = *(float*)(*node + 8); // radius from node data
            color = FUN_005d07d0(); // random color seed
            if (DAT_00e2eb58 <= *(float*)(extraout_ECX + 0xc) * local_58) // some condition?
            {
                color = color & 0xffffff | 0x99000000; // set alpha
            }
            if (DAT_00e446f4 < local_58)
            {
                local_58 = DAT_00e446f4; // clamp radius
            }
            FUN_005c4960();
            FUN_005cf730(piVar4, color, local_58 * DAT_00e2fc48, local_58 * DAT_00e2fc48, renderContext, param4, param5);
            DAT_0119d0bc = fVar2; // restore brightness
            return 1;
        }
        
        // Flag 0x100: draw a "highlight" (multiple layers?)
        if ((node[6] & 0x100) != 0)
        {
            // Same brightness decay as above
            if ((DAT_0119d0bc < DAT_00e2b118) &&
                (DAT_0119d0bc = DAT_0119d0bc * DAT_00e2b04c - DAT_00e2b118, DAT_0119d0bc < 0.0))
            {
                DAT_0119d0bc = 0.0;
            }
            uVar6 = FUN_005d07d0();
            uVar6 = uVar6 & 0xffffff | 0x7f000000; // semi-transparent white-ish
            FUN_005c4960();
            FUN_005cf730(piVar4, uVar6, _DAT_00e449a8, 0, renderContext, param4, param5); // horizontal line?
            FUN_005cf730(piVar4, uVar6, _DAT_00e449a8, _DAT_00e449a8, renderContext, param4, param5); // square
            
            uVar6 = FUN_005d07d0();
            uVar6 = uVar6 & 0xffffff | 0x4f000000; // semi-transparent with different alpha
            if ((_DAT_012278d4 & 1) == 0)
            {
                _DAT_012278d4 = _DAT_012278d4 | 1;
                _DAT_012278d0 = DAT_00e449a4; // save size
            }
            FUN_005c4960();
            FUN_005cf730(piVar4, uVar6, DAT_00e449a4, 0, renderContext, param4, param5);
            FUN_005cf730(piVar4, uVar6, DAT_00e449a4, _DAT_012278d0, renderContext, param4, param5);
        }
        
        uVar7 = node[6] & 0x20; // flag 0x20: "explored"?
        uVar6 = node[6] & 1;    // flag 0x1: "selected"?
        DAT_0119d0bc = fVar2;   // restore brightness
        if (uVar7 == 0)
        {
            fVar9 = DAT_00e2b04c; // default scale factor?
            fVar8 = DAT_00e2b04c;
            if (uVar6 == 0) goto LAB_005cfe80;
        }
        else
        {
            // flag 0x20 active: scale by radius from node
            fVar9 = *(float*)(*node + 8) * DAT_00e2b334;
            fVar8 = 0.0;
        }
        
        // Calculate expanded rectangle with offsets
        local_40 = fVar9 + (float)node[1];       // x1 + fVar9
        local_50 = (float)node[3] + fVar9;      // x2 + fVar9
        local_3c = (float)node[2] + fVar8;      // y1 + fVar8
        local_4c = (float)node[4] + fVar8;      // y2 + fVar8
        local_38 = DAT_00e2fc48;                 // size scaling?
        local_48 = DAT_00e2fc48;
        if (uVar7 == 0)
        {
            color = 0xff000000; // fully opaque black?
        }
        else
        {
            color = node[5];    // use node's own color
        }
        
        // If flag 0x1 (selected) and some global condition, save and clear a backup state
        if ((uVar6 != 0) && ((char)PTR_DAT_00f17650 == '\0'))
        {
            _DAT_0119daa0 = _DAT_0119d0b0;
            uRam0119daa4 = _DAT_0119d0b4;
            uRam0119daa8 = _DAT_0119d0b8;
            fRam0119daac = fVar2;
            _DAT_0119dab0 = DAT_0119d0c0;
            uRam0119dab4 = _DAT_0119d0c4;
            uRam0119dab8 = _DAT_0119d0c8;
            uRam0119dabc = _DAT_0119d0cc;
            DAT_0119d0c0 = 0;
            _DAT_0119d0c4 = 0;
            _DAT_0119d0c8 = 0;
            _DAT_0119d0cc = 0;
        }
        
        local_44 = DAT_00e2b1a4; // zero?
        local_34 = DAT_00e2b1a4;
        FUN_005c4960();
        // FUN_005ced60 likely draws a rectangle with given colors and flags
        cVar3 = FUN_005ced60(this + 0x10, piVar4, &local_40, &local_50, renderContext, color,
                             node[6] & 0x1e, param4, param5, 0);
        
        // Restore backup state
        if ((uVar6 != 0) && ((char)PTR_DAT_00f17650 == '\0'))
        {
            _DAT_0119d0b0 = _DAT_0119daa0;
            _DAT_0119d0b4 = uRam0119daa4;
            _DAT_0119d0b8 = uRam0119daa8;
            DAT_0119d0bc = fRam0119daac;
            DAT_0119d0c0 = _DAT_0119dab0;
            _DAT_0119d0c4 = uRam0119dab4;
            _DAT_0119d0c8 = uRam0119dab8;
            _DAT_0119d0cc = uRam0119dabc;
        }
        
        if (cVar3 != '\0')
        {
LAB_005cfe80:
            // Fallback draw with original rectangle and node color
            iVar1 = node[5];
            FUN_005c4960();
            uVar5 = FUN_005ced60(this + 0x10, piVar4, &local_20, &local_30, renderContext, iVar1,
                                 node[6] & 0x1e, param4, param5, 0);
            return uVar5;
        }
    }
    return 0;
}