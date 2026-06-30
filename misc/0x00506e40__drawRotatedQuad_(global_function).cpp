// FUNC_NAME: drawRotatedQuad (global function)
// Address: 0x00506e40
// Role: Renders a 2D sprite/quad with rotation and scaling, likely for HUD or effects.
// Parameters: centerX, centerY, angleOrScale, halfWidth, halfHeight. The angle parameter is reused as both sin/cos constants (or the preceding calls set sin/cos globally – unclear).
// Uses global screen dimensions (DAT_00e2b1a4, DAT_00e2b04c) and scaling factors (DAT_01218e44, DAT_01218e48, DAT_00e2cd54).
// Allocates a vertex buffer (5*4 bytes, 4 vertices with 4 components each) via FUN_0060cd00, fills it, then commits via FUN_0060cde0.
// The quad is defined by 4 corners: (-1,-1), (1,-1), (-1,1), (1,1) scaled by (halfWidth, halfHeight) and rotated, then transformed to screen space.

void drawRotatedQuad(float centerX, float centerY, float angle, float halfWidth, float halfHeight)
{
    float screenHalfWidth;
    float screenHalfHeight;
    float fVar1; // scaling factor Y
    float fVar3; // scaling factor X? (from DAT_01218e48)
    float fVar2; // offset (from DAT_00e2b1a4)
    float* pfVar4; // vertex buffer pointer
    uint uVar5; // loop counter
    double dVar7; // double of angle (used as sin? cos?)
    double dVar8; // double of angle (used as cos? sin?)
    float fVar6; // corner x direction (+1 or -1)
    float fVar9; // corner y direction (+1 or -1)
    float computedX, computedY; // temporary computed coordinates

    dVar7 = (double)angle;
    FUN_00b99fcb(); // likely push matrix or precompute transform
    dVar8 = (double)angle;
    FUN_00b99e20(); // likely pop matrix or postcompute transform

    pfVar4 = (float*)FUN_0060cd00(5, 4, 0, 1, 0); // allocate vertex buffer (5*4 bytes, 4 vertices, 4 components each)
    fVar2 = DAT_00e2b1a4; // screen width or half width offset
    fVar1 = DAT_00e2b04c; // screen height or half height offset

    if (pfVar4 != (float*)0x0) {
        uVar5 = 0;
        do {
            fVar3 = DAT_01218e48; // scaling factor (e.g., 1/screenHeight or aspect)
            fVar6 = (float)(int)((uVar5 & 1) * 2 + -1); // x direction: -1,1,-1,1
            fVar9 = (float)(int)((uVar5 & 2) - 1); // y direction: -1,-1,1,1

            // Compute corner offset after rotation/scaling (angle used as both sin/cos)
            computedX = fVar6 * (float)dVar8 * halfWidth - fVar9 * (float)dVar7 * halfHeight;
            computedY = fVar9 * (float)dVar8 * halfHeight + fVar6 * (float)dVar7 * halfWidth;

            // Transform to screen coordinates
            *pfVar4 = ((computedX + centerX) * DAT_01218e44 * fVar1) - fVar2; // screen x
            pfVar4[1] = fVar2 - ((computedY + centerY) * fVar3 * fVar1); // screen y
            pfVar4[2] = (fVar6 + fVar2) * DAT_00e2cd54; // texture coordinate or z/w? (unclear)
            pfVar4[3] = (fVar9 + fVar2) * DAT_00e2cd54; // texture coordinate or z/w? (unclear)

            uVar5 = uVar5 + 1;
            pfVar4 = pfVar4 + 4;
        } while ((int)uVar5 < 4);

        FUN_0060cde0(); // submit vertex buffer to GPU
    }
    return;
}