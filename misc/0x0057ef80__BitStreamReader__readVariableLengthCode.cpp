// FUNC_NAME: BitStreamReader::readVariableLengthCode
uint __fastcall BitStreamReader::readVariableLengthCode(void* /*unused*/, byte* bitStateOut)
{
    // bitStateOut points to a byte that tracks how many bits remain in the current byte (odd values: 1,3,5,7)
    // ESI holds a pointer to the current byte pointer (global buffer pointer)
    // This function decodes a variable-length code from a bitstream.
    // The first two bits of the next byte determine the code length (00,01,10,11 -> 12,8,4,0 bits respectively)
    // Subsequent bits are read depending on the state.

    byte* currentBytePtr = (byte*)*unaff_ESI; // unaff_ESI is the bit buffer pointer (set externally)
    byte state = *bitStateOut;
    uint result;
    ushort temp;

    switch (state - 1)
    {
    case 0: // state == 1: read from first 2 bits of currentBytePtr[0]
    {
        uint codeType = *currentBytePtr & 3;
        switch (codeType)
        {
        case 0: // 00: read 12-bit value (8+4 bits from next two bytes)
            *bitStateOut = 3;
            temp = (ushort)(currentBytePtr[1] << 4) | (ushort)(currentBytePtr[2] >> 4);
            *unaff_ESI += 2; // advance buffer by 2 bytes (consumed 2 bytes? Actually consumed 3 bytes? Wait: we used currentBytePtr[0] bits, but byte advances by 2? This seems wrong. Likely the code accounts for the prefix bits already.)
            result = temp;
            break;
        case 1: // 01: read 8 bits from next byte
            *bitStateOut = 7;
            result = currentBytePtr[1];
            *unaff_ESI += 2; // advance 2 bytes? (prefix byte + data byte)
            break;
        case 2: // 10: read 4 bits from next byte (high nibble)
            *bitStateOut = 3;
            result = currentBytePtr[1] >> 4;
            *unaff_ESI += 1; // advance 1 byte (prefix byte only? Actually consumed prefix byte's bits, next byte nibble)
            break;
        case 3: // 11: no data, return 0
            *bitStateOut = 7;
            *unaff_ESI += 1;
            result = 0;
            break;
        }
        break;
    }
    case 2: // state == 3: read from bits 2-3 of currentBytePtr[0]
    {
        uint codeType = (*currentBytePtr & 0xc) >> 2; // bits 2-3
        switch (codeType)
        {
        case 0: // 00: read 12-bit (10+2 bits) from next three bytes
            *bitStateOut = 5;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                byte bVar3 = currentBytePtr[2];
                // (bVar1,bVar2) 2-byte value masked 0x3ff = 10 bits, then *4 = 12 bits? Actually shift left 2, then OR top 2 bits of bVar3
                result = (uint)(ushort)((CONCAT11(bVar1,bVar2) & 0x3ff) * 4 | (ushort)(bVar3 >> 6));
            }
            *unaff_ESI += 2; // advance 2 bytes
            break;
        case 1: // 01: read 8 bits (2+6 bits) from next two bytes
            *bitStateOut = 1;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                result = (uint)(ushort)((ushort)(bVar1 & 3) << 6 | (ushort)(bVar2 >> 2));
            }
            *unaff_ESI += 1; // advance 1 byte
            break;
        case 2: // 10: read 4 bits (2+2 bits) from next two bytes
            *bitStateOut = 5;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                result = (uint)(ushort)((ushort)(bVar1 & 3) << 2 | (ushort)(bVar2 >> 6));
            }
            *unaff_ESI += 1;
            break;
        case 3: // 11: no data
            *bitStateOut = 1;
            result = 0;
            break;
        }
        break;
    }
    case 4: // state == 5: read from bits 4-5 of currentBytePtr[0]
    {
        uint codeType = (*currentBytePtr & 0x30) >> 4; // bits 4-5
        switch (codeType)
        {
        case 0: // 00: read 12 bits (8+4? Actually mask with 0xffff0fff keeps high 4 bits? Seems odd)
            *bitStateOut = 7;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                result = CONCAT11(bVar1,bVar2) & 0xffff0fff; // Keep only bits 12-15? Actually mask out lower 12 bits? This may be a bug or special.
            }
            *unaff_ESI += 2;
            break;
        case 1: // 01: read 8 bits (4+4 bits) from next two bytes
            *bitStateOut = 3;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                result = (uint)(ushort)((ushort)(bVar1 & 0xf) << 4 | (ushort)(bVar2 >> 4));
            }
            *unaff_ESI += 1;
            break;
        case 2: // 10: read 4 bits from low nibble of first byte
            *bitStateOut = 7;
            result = *currentBytePtr & 0xf;
            *unaff_ESI += 1;
            break;
        case 3: // 11: no data
            *bitStateOut = 3;
            result = 0;
            break;
        }
        break;
    }
    case 6: // state == 7: read from bits 6-7 of currentBytePtr[0]
    {
        uint codeType = (*currentBytePtr & 0xc0) >> 6; // bits 6-7
        switch (codeType)
        {
        case 0: // 00: read 8 bits (6+2 bits) from next two bytes
            *bitStateOut = 1;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                result = (uint)(ushort)((ushort)(bVar1 << 6) | (ushort)(bVar2 >> 2));
            }
            *unaff_ESI += 1;
            break;
        case 1: // 01: read 8 bits (6+2 bits) from next two bytes (variant)
            *bitStateOut = 5;
            {
                byte bVar1 = *currentBytePtr;
                byte bVar2 = currentBytePtr[1];
                result = (uint)(ushort)((ushort)(bVar1 & 0x3f) * 4 | (ushort)(bVar2 >> 6));
            }
            *unaff_ESI += 1;
            break;
        case 2: // 10: read 4 bits from bits 2-5 of first byte
            *bitStateOut = 1;
            result = (uint)((*currentBytePtr >> 2) & 0xf);
            // No pointer advance? Actually doesn't update *unaff_ESI, meaning the same byte is reused? Possibly a bug.
            break;
        case 3: // 11: no data
            *bitStateOut = 5;
            result = 0;
            break;
        }
        break;
    }
    default:
        // Should not reach; return garbage if invalid state
        result = (uint)((ushort)(uVar5 >> 16) << 16) | (uint)uVar6;
        break;
    }
    return result;
}