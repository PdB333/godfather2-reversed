// FUNC_NAME: setGlobalVector4
void setGlobalVector4(uint* param_1)
{
    // Copy 4 dwords from input to global variables (likely a 128-bit vector/color)
    gGlobalVectorX = param_1[0];  // DAT_011f4220
    gGlobalVectorY = param_1[1];  // DAT_011f4224
    gGlobalVectorZ = param_1[2];  // DAT_011f4228
    gGlobalVectorW = param_1[3];  // DAT_011f422c
    return;
}