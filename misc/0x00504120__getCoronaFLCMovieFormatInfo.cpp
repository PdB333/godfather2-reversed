// FUNC_NAME: getCoronaFLCMovieFormatInfo
static struct /* unknown */ * getCoronaFLCMovieFormatInfo(void)
{
    // Global structure at 0x01219180, likely a static singleton for a movie format descriptor
    // Offset layout (relative to returned pointer):
    // +0x00: pointer to vtable or function table (PTR_LAB_00e37fa0)
    // +0x04: string name "Corona"
    // +0x08: four-character code (0x2e666c63 = ".flc" in little endian)
    // +0x0C: unknown (0)
    // +0x10: some integer (3) - possibly version or flags
    // +0x14: unknown (0)
    // +0x18: buffer size or limit (0x800 = 2048)
    // +0x1C: unknown (0)
    // +0x20: unknown (0)
    // +0x24: unknown (0)
    _DAT_0121918c = 0;
    _DAT_01219194 = 0;
    _DAT_0121919c = 0;
    _DAT_012191a0 = 0;
    _DAT_012191a4 = 0;
    _DAT_01219184 = "Corona";
    _DAT_01219188 = 0x2e666c63; // ".flc" as little-endian int
    _DAT_01219190 = 3;
    _DAT_01219198 = 0x800;
    _DAT_01219180 = &PTR_LAB_00e37fa0;
    return &DAT_01219180;
}