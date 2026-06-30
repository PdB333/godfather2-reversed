// FUNC_NAME: MathUtils::initSinCosTable
void MathUtils::initSinCosTable(void)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float *pfVar4;
    float fVar5;
    int iVar6;
    
    fVar3 = DAT_00e44640; // +0x0: scale factor for sin/cos table
    if (_DAT_01126288 != 0.0) { // +0x0: flag indicating table needs initialization
        fVar5 = 2.8026e-45; // starting angle index (0)
        _DAT_01126288 = 0.0; // clear initialization flag
        iVar6 = 0x20; // 32 entries in the table
        pfVar4 = (float *)&DAT_0112668c; // +0x0: pointer to sin/cos table data
        do {
            // Compute sin value for angle index -2
            fVar1 = (float)((int)fVar5 + -2);
            fVar2 = (float)(int)fVar1;
            pfVar4[-0x100] = fVar1; // store angle index
            if ((int)fVar1 < 0) {
                fVar2 = fVar2 + DAT_00e44578; // wrap around for negative angles
            }
            // Compute sin value for angle index -1
            fVar1 = (float)((int)fVar5 + -1);
            *pfVar4 = fVar2 * fVar3; // store sin value
            pfVar4[-0xff] = fVar1; // store angle index
            fVar2 = (float)(int)fVar1;
            if ((int)fVar1 < 0) {
                fVar2 = fVar2 + DAT_00e44578;
            }
            pfVar4[1] = fVar2 * fVar3; // store sin value
            // Compute sin value for angle index 0
            pfVar4[-0xfe] = fVar5; // store angle index
            fVar1 = (float)(int)fVar5;
            if ((int)fVar5 < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar2 = (float)((int)fVar5 + 1);
            pfVar4[2] = fVar1 * fVar3; // store sin value
            // Compute sin value for angle index 1
            pfVar4[-0xfd] = fVar2; // store angle index
            fVar1 = (float)(int)fVar2;
            if ((int)fVar2 < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar2 = (float)((int)fVar5 + 2);
            pfVar4[3] = fVar1 * fVar3; // store sin value
            // Compute sin value for angle index 2
            pfVar4[-0xfc] = fVar2; // store angle index
            fVar1 = (float)(int)fVar2;
            if ((int)fVar2 < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar2 = (float)((int)fVar5 + 3);
            pfVar4[4] = fVar1 * fVar3; // store sin value
            // Compute sin value for angle index 3
            pfVar4[-0xfb] = fVar2; // store angle index
            fVar1 = (float)(int)fVar2;
            if ((int)fVar2 < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar2 = (float)((int)fVar5 + 4);
            pfVar4[5] = fVar1 * fVar3; // store sin value
            // Compute sin value for angle index 4
            pfVar4[-0xfa] = fVar2; // store angle index
            fVar1 = (float)(int)fVar2;
            if ((int)fVar2 < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar2 = (float)((int)fVar5 + 5);
            pfVar4[6] = fVar1 * fVar3; // store sin value
            // Compute sin value for angle index 5
            pfVar4[-0xf9] = fVar2; // store angle index
            fVar1 = (float)(int)fVar2;
            if ((int)fVar2 < 0) {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar5 = (float)((int)fVar5 + 8); // advance by 8 angle indices
            iVar6 = iVar6 + -1;
            pfVar4[7] = fVar1 * fVar3; // store sin value
            pfVar4 = pfVar4 + 8; // advance to next table entry
        } while (iVar6 != 0);
    }
    return;
}