// FUNC_NAME: GUID::toString
/**
 * Function at 0x004d9d60: Convert a GUID structure to a formatted string.
 * The GUID structure contains a name string (up to 12 bytes), two 32-bit UUID components,
 * and an optional pointer to a "next" GUID (used for hierarchical GUIDs).
 * Output buffer must be at least 36 bytes (0x24).
 * Format: "<name>_<hex7>_<hex7>_v3\0", with a recursive tail appended at offset 0x20 if next != NULL.
 * Special case: if input[0] == 1, output is just a single byte 1.
 */
char* __thiscall GUID::toString(char* outputBuffer, const GUID* inputGuid)
{
    char* writePtr;
    int iVar2;
    undefined4 uVar3;
    byte bVar4;
    char cVar5;
    uint uVar6;

    // Initialize the tail part (0x20..0x23) to nulls (for recursive string)
    outputBuffer[0x20] = '\0';
    outputBuffer[0x21] = '\0';
    outputBuffer[0x22] = '\0';
    outputBuffer[0x23] = '\0';

    cVar5 = inputGuid->name[0];
    if (cVar5 == '\x01') {
        // Special empty GUID: output is just 0x01
        *outputBuffer = '\x01';
        // Clear tail again (already done, but safe)
        outputBuffer[0x20] = '\0';
        outputBuffer[0x21] = '\0';
        outputBuffer[0x22] = '\0';
        outputBuffer[0x23] = '\0';
        return outputBuffer;
    }

    // Copy the input name string until null terminator
    writePtr = outputBuffer;
    if (cVar5 != '\0') {
        do {
            *writePtr = cVar5;
            // Compute next char by offset from input (tricky pointer arithmetic)
            cVar5 = writePtr[(int)(inputGuid->name + (1 - (int)outputBuffer))];
            writePtr = writePtr + 1;
        } while (cVar5 != '\0');
    }

    // Append first underscore
    *writePtr = '_';

    // --- First UUID part (using bytes at offsets 0xf, 0xc, 0xe and dword at 0xc) ---
    // Nibble from byte at +0xf (low nibble)
    bVar4 = inputGuid->bytes[0xf] & 0xf;
    if (bVar4 < 10) {
        cVar5 = bVar4 + 0x30; // '0'
    } else {
        cVar5 = bVar4 + 0x37; // 'A' - 10
    }
    writePtr[1] = cVar5;

    // Bits 20-23 from dword at +0xc
    uVar6 = *(uint*)(inputGuid + 0xc) >> 0x14 & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[2] = cVar5;

    // Nibble from byte at +0xe (low nibble)
    bVar4 = inputGuid->bytes[0xe] & 0xf;
    if (bVar4 < 10) {
        cVar5 = bVar4 + 0x30;
    } else {
        cVar5 = bVar4 + 0x37;
    }
    writePtr[3] = cVar5;

    // Bits 12-15 from dword at +0xc
    uVar6 = *(uint*)(inputGuid + 0xc) >> 0xc & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[4] = cVar5;

    // Bits 8-11 from dword at +0xc
    uVar6 = *(uint*)(inputGuid + 0xc) >> 8 & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[5] = cVar5;

    // Bits 4-7 from dword at +0xc
    uVar6 = *(uint*)(inputGuid + 0xc) >> 4 & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[6] = cVar5;

    // Bits 0-3 from dword at +0xc
    cVar5 = (char)(*(uint*)(inputGuid + 0xc) & 0xf);
    if ((*(uint*)(inputGuid + 0xc) & 0xf) < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[7] = cVar5;

    // Second underscore
    writePtr[8] = '_';

    // --- Second UUID part (using bytes at offsets 0x13, 0x10, 0x12 and dword at 0x10) ---
    // Nibble from byte at +0x13 (low nibble)
    bVar4 = inputGuid->bytes[0x13] & 0xf;
    if (bVar4 < 10) {
        cVar5 = bVar4 + 0x30;
    } else {
        cVar5 = bVar4 + 0x37;
    }
    writePtr[9] = cVar5;

    // Bits 20-23 from dword at +0x10
    uVar6 = *(uint*)(inputGuid + 0x10) >> 0x14 & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[10] = cVar5;

    // Nibble from byte at +0x12 (low nibble)
    bVar4 = inputGuid->bytes[0x12] & 0xf;
    if (bVar4 < 10) {
        cVar5 = bVar4 + 0x30;
    } else {
        cVar5 = bVar4 + 0x37;
    }
    writePtr[0xb] = cVar5;

    // Bits 12-15 from dword at +0x10
    uVar6 = *(uint*)(inputGuid + 0x10) >> 0xc & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[0xc] = cVar5;

    // Bits 8-11 from dword at +0x10
    uVar6 = *(uint*)(inputGuid + 0x10) >> 8 & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[0xd] = cVar5;

    // Bits 4-7 from dword at +0x10
    uVar6 = *(uint*)(inputGuid + 0x10) >> 4 & 0xf;
    cVar5 = (char)uVar6;
    if (uVar6 < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[0xe] = cVar5;

    // Bits 0-3 from dword at +0x10
    cVar5 = (char)(*(uint*)(inputGuid + 0x10) & 0xf);
    if ((*(uint*)(inputGuid + 0x10) & 0xf) < 10) {
        cVar5 = cVar5 + '0';
    } else {
        cVar5 = cVar5 + '7';
    }
    writePtr[0xf] = cVar5;

    // Append "_v3" terminator
    writePtr[0x10] = '_';
    writePtr[0x11] = 'v';
    writePtr[0x12] = '3';
    writePtr[0x13] = '\0';

    // If there is a "next" GUID, allocate space and recursively format it into tail
    if (inputGuid->next != NULL) {
        iVar2 = FUN_009c8e50(0x24); // Allocate 36 bytes for next GUID string
        if (iVar2 != 0) {
            uVar3 = toString((char*)iVar2, inputGuid->next);
            // Store pointer to the recursive string at offset 0x20 in output
            *(undefined4*)(outputBuffer + 0x20) = uVar3;
            return outputBuffer;
        }
        // Allocation failed: clear tail
        outputBuffer[0x20] = '\0';
        outputBuffer[0x21] = '\0';
        outputBuffer[0x22] = '\0';
        outputBuffer[0x23] = '\0';
    }
    return outputBuffer;
}