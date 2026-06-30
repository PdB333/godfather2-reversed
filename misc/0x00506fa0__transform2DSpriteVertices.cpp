// FUNC_NAME: transform2DSpriteVertices
void transform2DSpriteVertices(float translateX, float translateY, float scale, float cosAngle, float sinAngle)
{
    float fVar1, fVar2, fVar3, fVar4, fVar7, fVar8, fVar9, fVar11;
    float *pfVar5, *pfVar6;
    double dVar10;

    // Prepare global scaling factors
    dVar10 = (double)scale;
    FUN_00b99e20();
    fVar7 = (float)dVar10 * DAT_00e2b04c;               // DAT_00e2b04c: global unit scale

    dVar10 = (double)scale;
    FUN_00b99fcb();
    fVar8 = (float)dVar10 * DAT_00e2b04c;               // Same scale factor

    // Allocate output buffer: 6 floats? Actually we store 4 floats per vertex, 10 vertices => 40 floats
    pfVar5 = (float *)FUN_0060cd00(6, 10, 0, 1, 0);     // Allocate memory for transformed vertices

    fVar4 = DAT_00e2cd54;                                // Texture coordinate offset
    fVar3 = DAT_00e2b1a4;                                // Screen space offset

    if (pfVar5 != (float *)0x0) {
        // Screen aspect/scale factors
        fVar9 = DAT_01218e48 * DAT_00e2b04c;            // Y scaling
        fVar11 = DAT_01218e44 * DAT_00e2b04c;           // X scaling

        // Source vertex data: 10 pairs (u,v) stored at DAT_01128124
        pfVar6 = (float *)&DAT_01128124;

        do {
            fVar1 = pfVar6[-1];                         // u coordinate
            fVar2 = *pfVar6;                            // v coordinate

            // Transform to screen coordinates:
            // x = ((u*cos - v*sin)*scale + translateX) * screenScaleX - offsetX
            *pfVar5 = ((fVar1 * fVar7 * cosAngle - fVar2 * fVar8 * sinAngle) + translateX) * fVar11 - fVar3;

            // y = offsetY - ((v*cos + u*sin)*scale + translateY) * screenScaleY
            pfVar5[1] = fVar3 - ((fVar2 * fVar7 * sinAngle + fVar1 * fVar8 * cosAngle) + translateY) * fVar9;

            // Output texture coordinates (offset by constant)
            pfVar5[2] = fVar1 + fVar4;
            pfVar5[3] = fVar2 + fVar4;

            // Advance: source reads 2 floats, output writes 4 floats
            pfVar6 += 2;
            pfVar5 += 4;
        } while ((int)pfVar6 < 0x1128174);              // Loop until end of source data (10 pairs)

        FUN_0060cde0();                                 // Release or finalize buffer
    }
    return;
}