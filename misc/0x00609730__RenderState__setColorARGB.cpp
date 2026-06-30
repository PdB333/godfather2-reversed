// FUNC_NAME: RenderState::setColorARGB
// Address: 0x00609730
// Packs four floats (r,g,b,a) into an ARGB 32-bit integer using global scale factor (likely 255.0f),
// stores the packed color at DAT_01205748, and stores two additional parameters to globals
// _DAT_00f15a68 and DAT_0120574c (possibly extra render state flags or alpha mod).

// Global scale factor for converting float [0,1] to byte [0,255]
extern float DAT_00e44584; // TODO: rename to g_colorScale or similar

// Globals set by this function
extern uint32_t DAT_01205748; // Packed ARGB color
extern uint32_t _DAT_00f15a68; // Extra render state parameter 1
extern uint32_t DAT_0120574c; // Extra render state parameter 2

void setColorARGB(float r, float g, float b, float a, uint32_t extraParam1, uint32_t extraParam2)
{
    // Round and convert each channel to 0-255
    uint8_t rByte = (uint8_t)(r * DAT_00e44584 + 0.5f);
    uint8_t gByte = (uint8_t)(g * DAT_00e44584 + 0.5f);
    uint8_t bByte = (uint8_t)(b * DAT_00e44584 + 0.5f);
    uint8_t aByte = (uint8_t)(a * DAT_00e44584 + 0.5f);

    // Pack as ARGB: byte0=b, byte1=g, byte2=r, byte3=a
    uint32_t packedColor = (aByte << 24) | (rByte << 16) | (gByte << 8) | bByte;

    // Store to global render state
    DAT_01205748 = packedColor;
    _DAT_00f15a68 = extraParam1;
    DAT_0120574c = extraParam2;
}