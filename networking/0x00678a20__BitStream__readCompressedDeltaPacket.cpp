// FUNC_NAME: BitStream::readCompressedDeltaPacket
// 0x00678a20 - Decodes a compressed delta position packet from a byte stream.
// The packet format uses a variable-length base-6 encoding for sequence components.
// param_1: state (flags at +0x08 = highPrecision, +0x35 = shortMode)
// param_2: pointer to current byte pointer (advances as data is consumed)
// param_3: output buffer (assumed to be at least 6 ints)
// param_4: pointer to running timestamp accumulator (updated with delta)
void BitStream::readCompressedDeltaPacket(int *state, byte **dataPtr, int *outPacket, int *prevTimestamp)
{
    byte *src = *dataPtr;
    short dx = 0;
    short dy = 0;
    
    if (*(char *)(state + 8) == '\0') 
    {
        // Low precision mode (fixed 12-bit fields)
        byte firstByte = *src;
        byte *cursor = src + 1;
        
        if ((firstByte & 0x10) == 0) {
            dx = 0x1000; // No delta indicates a marker? Actually 0x1000 is 4096
        } else {
            byte hi = *cursor;
            cursor = src + 3; // skip 2 bytes for 16-bit value? Actually reads 2 bytes
            dx = (ushort)hi * 0x100 + (ushort)src[2];
        }
        
        if ((firstByte & 0x20) == 0) {
            dy = 0x1000;
        } else {
            byte hi = *cursor;
            byte lo = *(cursor + 1);
            cursor += 2;
            dy = (ushort)hi * 0x100 + (ushort)lo;
        }
        
        outPacket[2] = (int)dy << 4;
        outPacket[0] = (int)dx << 4;
        outPacket[1] = 0;
        outPacket[3] = 0;
        
        ushort timestamp;
        if ((firstByte & 0x40) == 0) {
            timestamp = (ushort)*cursor;
            cursor++;
        } else {
            timestamp = CONCAT11(*cursor, cursor[1]);
            cursor += 2;
        }
        *(ushort *)(outPacket + 5) = timestamp;
        
        if (-1 < (char)firstByte) {
            // 16-bit data identifier
            outPacket[4] = (uint)(ushort)((ushort)*cursor * 0x100 + (ushort)cursor[1]);
            *dataPtr = cursor + 2;
            return;
        } else {
            // 24-bit data identifier
            outPacket[4] = (uint)CONCAT21(CONCAT11(*cursor, cursor[1]), cursor[2]);
            *dataPtr = cursor + 3;
            return;
        }
    }
    
    // High precision mode with base-6 encoded sequence
    byte *cursor = src + 1;
    bool firstElement = false;
    uint code = (uint)*src;
    
    do {
        switch (code % 6) {
        case 0:
            dx = 0x1000; // No delta? Actually base value
            goto LAB_00678b41;
        case 1:
            dy = (short)(char)*cursor;
            dx = 0x1000;
            cursor++;
            break;
        case 2:
            {
                byte hi = *cursor;
                byte lo = *(cursor + 1);
                cursor += 2;
                dy = (ushort)hi * 0x100 + (ushort)lo;
                dx = 0x1000;
            }
            break;
        case 3:
            if (*(char *)(state + 0x35) == '\0') {
                dx = (ushort)*cursor * 0x100 + (ushort)cursor[1];
                dy = (short)(char)cursor[2];
                cursor += 3;
            } else {
                dx = (*cursor + 1) * 0x20;
                dy = (short)(char)cursor[1];
                cursor += 2;
            }
            break;
        case 4:
            if (*(char *)(state + 0x35) == '\0') {
                byte *tmp = cursor + 2;
                dx = (ushort)*cursor * 0x100 + (ushort)cursor[1];
                cursor = tmp;
            } else {
                dx = (*cursor + 1) * 0x20;
                cursor++;
            }
            dy = (ushort)*cursor * 0x100 + (ushort)cursor[1];
            cursor += 2;
            break;
        case 5:
            dx = 0;
LAB_00678b41:
            dy = 0;
            break;
        }
        
        if (firstElement) {
            // Second element: store to offsets 2 and 3
            outPacket[2] = (int)dx << 4;
            outPacket[3] = (int)dy << 16;
            
            switch (code / 6) {
            case 0:
                {
                    byte b = *cursor;
                    int newTimestamp = *prevTimestamp - (uint)b;
                    outPacket[4] = newTimestamp;
                    *prevTimestamp = newTimestamp;
                    *(ushort *)(outPacket + 5) = (ushort)b;
                    *dataPtr = cursor + 1;
                }
                return;
            case 1:
                {
                    byte b = *cursor;
                    int newTimestamp = *prevTimestamp - (uint)(ushort)(b + 0x100);
                    outPacket[4] = newTimestamp;
                    *prevTimestamp = newTimestamp;
                    *(ushort *)(outPacket + 5) = b + 0x100;
                    *dataPtr = cursor + 1;
                }
                return;
            case 2:
                {
                    ushort ts = (ushort)*cursor * 0x100 + (ushort)cursor[1];
                    int newTimestamp = *prevTimestamp - (uint)ts;
                    outPacket[4] = newTimestamp;
                    *prevTimestamp = newTimestamp;
                    *(ushort *)(outPacket + 5) = ts;
                    *dataPtr = cursor + 2;
                }
                return;
            case 3:
                {
                    byte b1 = *cursor;
                    byte b2 = cursor[1];
                    unsigned int raw = CONCAT21(CONCAT11(b1, b2), cursor[2]);
                    int newTimestamp = *prevTimestamp - (raw & 0x7fff);
                    outPacket[4] = newTimestamp;
                    *prevTimestamp = newTimestamp;
                    *(ushort *)(outPacket + 5) = CONCAT11(b1, b2) >> 7;
                    *dataPtr = cursor + 3;
                }
                return;
            case 4:
                {
                    byte b1 = *cursor;
                    byte b2 = cursor[1];
                    outPacket[4] = CONCAT21(CONCAT11(b1, b2), cursor[2]) & 0x7fff;
                    *(ushort *)(outPacket + 5) = CONCAT11(b1, b2) >> 7;
                    *dataPtr = cursor + 3;
                }
                return;
            case 5:
                {
                    byte b1 = *cursor;
                    byte b2 = cursor[1];
                    outPacket[4] = CONCAT31(CONCAT21(CONCAT11(b1, b2), cursor[2]), cursor[3]) & 0x7fffff;
                    *(ushort *)(outPacket + 5) = CONCAT11(b1, b2) >> 7;
                    *dataPtr = cursor + 4;
                }
                return;
            case 6:
                {
                    byte b1 = *cursor;
                    byte b2 = cursor[1];
                    outPacket[4] = (uint)CONCAT21(CONCAT11(cursor[2], cursor[3]), cursor[4]);
                    *(ushort *)(outPacket + 5) = (ushort)b1 * 0x100 + (ushort)b2;
                    *dataPtr = cursor + 5;
                }
                return;
            default:
                outPacket[4] = 0;
                *(short *)(outPacket + 5) = 0;
                *dataPtr = cursor;
                return;
            }
        }
        
        // First element: store to offsets 0 and 1
        outPacket[0] = (int)dx << 4;
        firstElement = true;
        outPacket[1] = (int)dy << 16;
        code = code / 6;
    } while (true);
}