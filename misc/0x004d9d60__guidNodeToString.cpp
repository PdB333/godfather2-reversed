//FUNC_NAME: guidNodeToString
char* __thiscall guidNodeToString(char* outBuffer, const char* inputNode)
{
    // Clear the child pointer field at offset 0x20
    outBuffer[0x20] = '\0';
    outBuffer[0x21] = '\0';
    outBuffer[0x22] = '\0';
    outBuffer[0x23] = '\0';

    char firstByte = *inputNode;
    if (firstByte == 0x01) {
        // Special case: output a single 0x01 byte and return
        *outBuffer = 0x01;
        outBuffer[0x20] = '\0';
        outBuffer[0x21] = '\0';
        outBuffer[0x22] = '\0';
        outBuffer[0x23] = '\0';
        return outBuffer;
    }

    char* dest = outBuffer;
    if (firstByte != '\0') {
        // Copy the name string from inputNode until null terminator
        do {
            *dest = firstByte;
            // Compute next character from inputNode based on distance
            firstByte = dest[(int)(inputNode + (1 - (int)outBuffer))];
            dest++;
        } while (firstByte != '\0');
    }

    // Append underscore and hex nibbles from inputNode fields
    *dest = '_';
    // InputNode offset 0x0f: low nibble
    unsigned char nibble = inputNode[0x0f] & 0xf;
    dest[1] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    // InputNode offset 0x0c: bits 20-23 (high nibble of second dword?)
    unsigned int val = *(unsigned int*)(inputNode + 0x0c);
    nibble = (val >> 0x14) & 0xf;
    dest[2] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    // InputNode offset 0x0e: low nibble
    nibble = inputNode[0x0e] & 0xf;
    dest[3] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    // InputNode offset 0x0c: bits 12-15
    nibble = (val >> 0x0c) & 0xf;
    dest[4] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    // InputNode offset 0x0c: bits 8-11
    nibble = (val >> 0x08) & 0xf;
    dest[5] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    // InputNode offset 0x0c: bits 4-7
    nibble = (val >> 0x04) & 0xf;
    dest[6] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    // InputNode offset 0x0c: bits 0-3
    nibble = val & 0xf;
    dest[7] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);

    dest[8] = '_';

    // Second group: from inputNode offsets 0x13, 0x10, 0x12, and 0x10 again
    nibble = inputNode[0x13] & 0xf;
    dest[9] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    unsigned int val2 = *(unsigned int*)(inputNode + 0x10);
    nibble = (val2 >> 0x14) & 0xf;
    dest[10] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    nibble = inputNode[0x12] & 0xf;
    dest[11] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    nibble = (val2 >> 0x0c) & 0xf;
    dest[12] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    nibble = (val2 >> 0x08) & 0xf;
    dest[13] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    nibble = (val2 >> 0x04) & 0xf;
    dest[14] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);
    nibble = val2 & 0xf;
    dest[15] = (nibble < 10) ? (nibble + '0') : (nibble + 0x37);

    dest[16] = '_';
    dest[17] = 'v';
    dest[18] = '3';
    dest[19] = '\0';

    // Check for child node pointer at inputNode+0x14
    if (*(int*)(inputNode + 0x14) != 0) {
        int allocResult = FUN_009c8e50(0x24); // Allocate 36 bytes for child output
        if (allocResult != 0) {
            // Recursively convert child node
            char* childStr = guidNodeToString((char*)allocResult, *(const char**)(inputNode + 0x14));
            *(char**)(outBuffer + 0x20) = childStr;
            return outBuffer;
        }
        // Allocation failed: clear child pointer
        outBuffer[0x20] = '\0';
        outBuffer[0x21] = '\0';
        outBuffer[0x22] = '\0';
        outBuffer[0x23] = '\0';
    }
    return outBuffer;
}