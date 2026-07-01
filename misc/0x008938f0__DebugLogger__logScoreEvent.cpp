// FUNC_NAME: DebugLogger::logScoreEvent
void __thiscall DebugLogger::logScoreEvent(int thisPtr, uint eventId, ScorePacket* packet)
{
    byte flagsByte;
    uint resultByte;
    uint combined;
    uint tmp;
    uint uVar2;
    uint uVar4;
    int iVar8;
    bool bVar9;
    uint uVar10;
    char buffer[15];
    undefined1 terminator;

    // packet fields:
    uint scoreValue = packet->field0;        // +0x00
    uint delta = packet->field1;             // +0x04
    uint scoreType = packet->field2;         // +0x08
    uint unknown = packet->field3;           // +0x0C
    flagsByte = *(byte*)(&packet->field4);   // +0x10 (byte)

    // Extract low nibble flags from flagsByte
    uVar10 = 0;
    if ((flagsByte & 1) != 0) {
        uVar10 |= 1;
    }
    bVar9 = (flagsByte >> 1) & 1;
    if (bVar9 != 0) {
        uVar10 |= 2;
    }
    if ((flagsByte & 4) != 0) {
        uVar10 |= 4;
    }

    uVar4 = scoreType; // reuse variable
    void* tempPtr = 0;

    if (scoreType == 2) {
        if (!bVar9) {
            // Check object state
            if ((*(int*)(thisPtr + 0x38) != 0) && (*(int*)(thisPtr + 0x38) != 0x48)) {
                if (*(int*)(thisPtr + 0x38) == 0) {
                    resultByte = getRandomByte();
                    tempPtr = (void*)(resultByte & 0xFF);
                } else {
                    resultByte = getRandomByte();
                    tempPtr = (void*)(resultByte & 0xFF);
                }
            }
        } else {
            iVar8 = isDebugMode();
            if (iVar8 == 0) {
                if ((*(int*)(thisPtr + 0x38) != 0) && (*(int*)(thisPtr + 0x38) != 0x48)) {
                    if (*(int*)(thisPtr + 0x38) == 0) {
                        iVar8 = 0;
                    } else {
                        iVar8 = *(int*)(thisPtr + 0x38) - 0x48;
                    }
                    iVar8 = checkHash(iVar8, 0x369AC561);
                    if (iVar8 != 0) {
                        resultByte = getRandomByte();
                        tempPtr = (void*)(resultByte & 0xFF);
                    }
                }
            } else {
                resultByte = getRandomByte();
                tempPtr = (void*)(resultByte & 0xFF);
            }
        }
    }

    // If flags byte bit 1 is not set, use first field for logging
    if ((flagsByte & 2) == 0) {
        delta = scoreValue;
    }

    // Build log string: 8 hex digits + 2 + 2 + 2? Actually format: "%08X%02X%02X%02X"
    // Arguments: delta (uint), unknown & 0xFF, tempPtr (as uint), combined nibbles
    combined = (uVar10 << 4) | (uVar4 & 0xF);
    __snprintf(buffer, 0x10, "%08X%02X%02X%02X",
               delta, unknown & 0xFF, tempPtr, combined);
    buffer[14] = 0; // terminator

    // Log with tag "SCOR"
    debugPrintString(0x53434F52, eventId, buffer);

    // If object state is valid and flags byte bit0 or bit1 set, log position
    if ((*(int*)(thisPtr + 0x38) != 0) && (*(int*)(thisPtr + 0x38) != 0x48) &&
        ((flagsByte & 3) != 0)) {
        if (*(int*)(thisPtr + 0x38) == 0) {
            iVar8 = 0;
        } else {
            iVar8 = *(int*)(thisPtr + 0x38) - 0x48;
        }
        debugPrintInt(0x53504750, 0x504F534E, iVar8); // Tags "SPGP", "POSN"
    }
    return;
}