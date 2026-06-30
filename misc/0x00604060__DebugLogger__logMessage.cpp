// FUNC_NAME: DebugLogger::logMessage
void DebugLogger::logMessage(void)
{
    // Check if the initialized flag (bit 2 at +0x4c) is set
    if ((*(unsigned int*)(in_EAX + 0x4c) >> 2 & 1) == 0) {
        // If not, call sub-object initialization twice and set the flag
        FUN_00603c50(in_EAX);
        FUN_00603c50(in_EAX);
        *(unsigned int*)(in_EAX + 0x4c) |= 4;
    }

    // Get pointer to string buffer at offset 0x84
    char* strBuf = (char*)(in_EAX + 0x84);
    int strLen = 0;
    if (strBuf != (char*)0x0) {
        char* cursor = strBuf;
        while (*cursor != '\0') {
            cursor++;
        }
        // Compute length as offset from base+0x85 (skipping the first byte at 0x84)
        strLen = (int)cursor - (int)(in_EAX + 0x85);
    }

    // Call debug print function with severity=0, the string, flags=0, length
    FUN_004d41f0(0, strBuf, 0, strLen);

    // Release or destruct resource at offset 0x94
    FUN_004d4300(in_EAX + 0x94);
    return;
}