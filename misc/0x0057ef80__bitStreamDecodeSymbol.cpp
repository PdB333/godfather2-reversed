// FUNC_NAME: bitStreamDecodeSymbol
uint __fastcall bitStreamDecodeSymbol(void* unused, byte* state)
{
    byte* currentByte = *(byte**)bitStreamPtr; // Dereference pointer to current byte in stream
    uint temp = *state - 1; // State values: 1,3,5,7 -> index 0,2,4,6
    ushort temp16 = 0;

    switch (temp)
    {
    case 0: // State 1: examine bits 0-1 of current byte
    {
        uint bits = *currentByte & 3;
        switch (bits)
        {
        case 0: // 00
            *state = 3; // Next state
            temp = 0;
            temp16 = (ushort)(currentByte[2] >> 4) | (ushort)currentByte[1] << 4; // Combine bytes 1 and 2
            *(byte**)bitStreamPtr += 2; // Advance 2 bytes
            break;
        case 1: // 01
            *state = 7;
            byte b = currentByte[1];
            *(byte**)bitStreamPtr += 2;
            return (uint)b;
        case 2: // 10
            *state = 3;
            byte b = currentByte[1];
            *(byte**)bitStreamPtr += 1;
            return (uint)(b >> 4);
        case 3: // 11
            *state = 7;
            *(byte**)bitStreamPtr += 1;
            return 0;
        }
        break;
    }
    case 2: // State 3: examine bits 2-3 of current byte
    {
        uint bits = *currentByte & 0xc;
        switch (bits)
        {
        case 0: // 00
            *state = 5;
            byte b1 = *currentByte;
            byte b2 = currentByte[1];
            byte b3 = currentByte[2];
            *(byte**)bitStreamPtr += 2;
            return (uint)(ushort)((CONCAT11(b1, b2) & 0x3ff) * 4 | (ushort)(b3 >> 6));
        case 4: // 01
            *state = 1;
            byte b1 = *currentByte;
            byte b2 = currentByte[1];
            *(byte**)bitStreamPtr += 1;
            return (uint)(ushort)((ushort)(b1 & 3) << 6 | (ushort)(b2 >> 2));
        case 8: // 10
            *state = 5;
            byte b1 = *currentByte;
            byte b2 = currentByte[1];
            *(byte**)bitStreamPtr += 1;
            return (uint)(ushort)((ushort)(b1 & 3) << 2 | (ushort)(b2 >> 6));
        case 0xc: // 11
            *state = 1;
            return 0;
        }
        break;
    }
    case 4: // State 5: examine bits 4-5 of current byte
    {
        uint bits = *currentByte & 0x30;
        switch (bits)
        {
        case 0: // 00
            *state = 7;
            byte b1 = *currentByte;
            byte b2 = currentByte[1];
            *(byte**)bitStreamPtr += 2;
            return CONCAT11(b1, b2) & 0xffff0fff;
        case 0x10: // 01
            *state = 3;
            byte b1 = *currentByte;
            byte b2 = currentByte[1];
            *(byte**)bitStreamPtr += 1;
            return (uint)(ushort)((ushort)(b1 & 0xf) << 4 | (ushort)(b2 >> 4));
        case 0x20: // 10
            *state = 7;
            byte b = *currentByte;
            *(byte**)bitStreamPtr += 1;
            return (uint)(b & 0xf);
        case 0x30: // 11
            *state = 3;
            return 0;
        }
        break;
    }
    case 6: // State 7: examine bits 6-7 of current byte
    {
        uint bits = *currentByte & 0xc0;
        switch (bits)
        {
        case 0: // 00
            *state = 1;
            byte b1 = currentByte[1];
            byte b2 = *currentByte;
            *(byte**)bitStreamPtr += 1;
            return (uint)(ushort)((ushort)(b1 >> 2) | (ushort)b2 << 6);
        case 0x40: // 01
            *state = 5;
            byte b1 = *currentByte;
            byte b2 = currentByte[1];
            *(byte**)bitStreamPtr += 1;
            return (uint)(ushort)((ushort)(b1 & 0x3f) * 4 | (ushort)(b2 >> 6));
        case 0x80: // 10
            *state = 1;
            return (uint)(*currentByte >> 2 & 0xf);
        case 0xc0: // 11
            *state = 5;
            return 0;
        }
    }
    }
    return CONCAT22((short)(temp >> 0x10), temp16);
}