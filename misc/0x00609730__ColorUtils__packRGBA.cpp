// FUNC_NAME: ColorUtils::packRGBA
void packRGBA(float r, float g, float b, float a, uint32_t colorOut, uint32_t alphaOut)
{
    uint32_t rByte;
    uint32_t gByte;
    uint32_t bByte;
    uint32_t aByte;
    uint32_t packedColor;

    // Store alpha output pointer
    _DAT_00f15a68 = colorOut;

    // Convert float components to bytes using scale factor at 0x00e44584
    rByte = (uint32_t)(uint8_t)(int32_t)(r * _DAT_00e44584);
    aByte = (uint32_t)(uint8_t)(int32_t)(a * _DAT_00e44584);
    gByte = (uint32_t)(uint8_t)(int32_t)(g * _DAT_00e44584);
    bByte = (uint32_t)(uint8_t)(int32_t)(b * _DAT_00e44584);

    // Pack into RGBA format: (A << 24) | (B << 16) | (G << 8) | R
    packedColor = ((rByte | (aByte << 8)) << 8 | gByte) << 8 | bByte;

    // Store packed color and alpha output
    _DAT_01205748 = packedColor;
    _DAT_0120574c = alphaOut;
}