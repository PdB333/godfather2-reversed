// FUNC_NAME: formatGUIDString
void __fastcall formatGUIDString(uint32_t param1, uint32_t param2, char* outBuffer, uint32_t param4, uint32_t param5)
{
    const char hexDigits[] = "0123456789ABCDEF";
    
    outBuffer[0] = '{';
    outBuffer[1] = hexDigits[param4 >> 28];
    outBuffer[2] = hexDigits[(param4 >> 24) & 0xF];
    outBuffer[3] = hexDigits[((param4 >> 16) & 0xFF) >> 4];
    outBuffer[4] = hexDigits[(param4 >> 16) & 0xF];
    outBuffer[5] = hexDigits[((param4 >> 8) & 0xFF) >> 4];
    outBuffer[6] = hexDigits[(param4 >> 8) & 0xF];
    outBuffer[7] = hexDigits[(param4 >> 4) & 0xF];
    outBuffer[8] = hexDigits[param4 & 0xF];
    outBuffer[9] = '-';
    // First 4 hex digits from low half of param5 (bits 8-15,4-7,0-3)
    outBuffer[10] = hexDigits[((param5 >> 8) & 0xFF) >> 4];
    outBuffer[11] = hexDigits[(param5 >> 8) & 0xF];
    outBuffer[12] = hexDigits[(param5 >> 4) & 0xF];
    outBuffer[13] = hexDigits[param5 & 0xF];
    // Second 4 hex digits from high half of param5 (bits 28-31,24-27,16-23)
    outBuffer[14] = '-';
    outBuffer[15] = hexDigits[param5 >> 28];
    outBuffer[16] = hexDigits[(param5 >> 24) & 0xF];
    outBuffer[17] = hexDigits[((param5 >> 16) & 0xFF) >> 4];
    outBuffer[18] = hexDigits[(param5 >> 16) & 0xF];
    // Next 4 hex digits from low half of param2 (bits 0-15), but nibble order reversed? Actually from code: bits 0-7 then 8-15
    outBuffer[19] = '-';
    outBuffer[20] = hexDigits[(param2 & 0xFF) >> 4];
    outBuffer[21] = hexDigits[param2 & 0xF];
    outBuffer[22] = hexDigits[((param2 >> 8) & 0xFF) >> 4];
    outBuffer[23] = hexDigits[(param2 >> 8) & 0xF];
    // Next 8 hex digits from high half of param2 (bits 16-31) and param1 (bits 0-31)
    outBuffer[24] = '-';
    outBuffer[25] = hexDigits[((param2 >> 16) & 0xFF) >> 4];
    outBuffer[26] = hexDigits[(param2 >> 16) & 0xF];
    outBuffer[27] = hexDigits[param2 >> 28];
    outBuffer[28] = hexDigits[(param2 >> 24) & 0xF];
    // Then from param1: low byte first (bits 0-7), then second byte (bits 8-15), then third byte (bits 16-23), then high byte (bits 24-31) but with nibble order: high nibble then low nibble per byte? Actually code: bits 0-3 low nibble, bits 4-7 high nibble? Check indices:
    // 0x1e: hex[ (param1 & 0xFF) >> 4 ] -> high nibble of low byte
    // 0x1f: hex[ param1 & 0xF ] -> low nibble
    // 0x20: hex[ (param1>>8 &0xFF)>>4 ] -> high nibble of second byte
    // 0x21: hex[ param1>>8 &0xF ] -> low nibble
    // 0x22: hex[ (param1>>16 &0xFF)>>4 ] -> high nibble of third byte
    // 0x23: hex[ param1>>16 &0xF ] -> low nibble
    // 0x24: hex[ param1>>28 ] -> high nibble of high byte? Actually >>28 gives bits 28-31 (high nibble of byte 3)
    // 0x25: hex[ param1>>24 &0xF ] -> low nibble of high byte (bits 24-27)
    // So order: high nibble then low nibble for each byte, and bytes from LSB to MSB.
    outBuffer[29] = hexDigits[(param1 & 0xFF) >> 4];
    outBuffer[30] = hexDigits[param1 & 0xF];
    outBuffer[31] = hexDigits[((param1 >> 8) & 0xFF) >> 4];
    outBuffer[32] = hexDigits[(param1 >> 8) & 0xF];
    outBuffer[33] = hexDigits[((param1 >> 16) & 0xFF) >> 4];
    outBuffer[34] = hexDigits[(param1 >> 16) & 0xF];
    outBuffer[35] = hexDigits[param1 >> 28];
    outBuffer[36] = hexDigits[(param1 >> 24) & 0xF];
    outBuffer[37] = '}';
    outBuffer[38] = '\0';
}