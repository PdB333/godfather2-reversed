// FUNC_NAME: packOrientationPacket
// Address: 0x00496830
// Encodes an angle (float) and a type identifier into a 32-bit packet field.
// The low 16 bits: (typeByte << 8) | 0x01 (where typeByte depends on type parameter)
// The high 16 bits: angle * g_angleScale (converted to short)
// type values: 0 -> 0x01, 1 -> 0x81, 2 -> 0x41
extern float g_angleScale; // DAT_00e2e230

int __cdecl packOrientationPacket(float angle, int type)
{
    unsigned char typeByte;
    
    if (type == 1) {
        typeByte = 0x81;
    } else if (type == 2) {
        typeByte = 0x41;
    } else {
        typeByte = 1;
    }
    
    // Build 32-bit value: high half = scaled angle, low half = (typeByte << 8) | 1
    int result = ((int)(angle * g_angleScale) << 16) | ((typeByte << 8) | 1);
    return result;
}