// FUNC_NAME: UIRenderElement::updateShaderParams
void __thiscall UIRenderElement::updateShaderParams(int *this, int shaderHandle)
{
    // this: pointer to UIRenderElement
    // offsets: this[0] = +0x00 (unknown flag/ID), this[1] = +0x04 (handle1), this[2] = +0x08 (handle2), this[3] = +0x0C (handle3), this[4] = +0x10 (handle4)
    float vec4[4]; // local_20, local_1c, local_18, local_14

    if ((*(int *)(DAT_012233b0 + 0x30) != 0) && (DAT_01163840 != 0)) {
        // Use alternate (highlighted/shaded) colors
        // Read a byte from complex TLS path, scale by DAT_00e44640
        char *someTLSData = *(char **)(**(int **)(__readfsdword(0x2C) + 8) + 8); // approximated
        int index = *(int *)(*(int *)(DAT_012233b0 + 0x30) + 0x18);
        vec4[3] = (float)(unsigned char)(someTLSData[0x9B + index]) * DAT_00e44640;

        // Lookup in a table of 0x38-byte entries
        if (DAT_01163830 < 0x1000) {
            char *tableEntry = &DAT_011a0f28 + DAT_01163830 * 0x38;
            vec4[0] = (float)*(unsigned short *)(tableEntry + 2);
            vec4[1] = (float)*(unsigned short *)(tableEntry + 4);
        } else {
            vec4[0] = 0.0f;
            vec4[1] = 0.0f;
        }
        vec4[2] = DAT_00e2b1a4 - vec4[3];

        // Set shader constants
        FUN_0060add0(shaderHandle, this[4], &vec4); // set vector4 for handle4

        if (this[0] != 0) {
            FUN_006063b0(); // additional setup
        }

        // Choose color source based on flag
        float *colorSource = &DAT_01163810; // primary color
        if (DAT_01163840 == 0) {
            colorSource = &DAT_00e2e760; // alternate (but condition is false here)
        }
        FUN_0060add0(shaderHandle, this[1], colorSource);

        int timeValue = FUN_0041f560(&DAT_011f6b30); // get some time/phase
        FUN_0060b020(shaderHandle, this[2], timeValue);

        float *otherColor = &DAT_011637d0;
        if (DAT_01163840 == 0) {
            otherColor = &DAT_00e2e720;
        }
        FUN_0060b020(shaderHandle, this[3], otherColor);
    } else {
        // Default: set all to constant value (likely zero/white)
        vec4[0] = DAT_00e2b1a4;
        vec4[1] = DAT_00e2b1a4;
        vec4[2] = DAT_00e2b1a4;
        vec4[3] = 0.0f;
        FUN_0060add0(shaderHandle, this[4], &vec4);
    }
}