// FUNC_NAME: DebugLogger::logMessage
void __fastcall DebugLogger::logMessage(int thisPtr) {
    // Structure for a string with three fields: pointer, length, capacity
    struct DebugString {
        const char* data;   // +0x00
        int length;         // +0x04
        int capacity;       // +0x08
    };

    DebugString msg; // local_c, local_8, local_4
    int isDebugMode = *(int*)(thisPtr + 0x04); // m_isDebugMode flag at offset +4

    if (isDebugMode == 0) {
        // Normal mode: use default string
        msg.data = (const char*)DAT_011302c0; // pointer to "DefaultMessage" or similar
    } else {
        // Debug mode: initialize debug system and use debug string
        initializeDebugSystem(); // FUN_00967450
        msg.data = (const char*)DAT_011304d8; // pointer to "DebugMessage" or similar
    }
    msg.length = 0;      // +0x04
    msg.capacity = 0;    // +0x08

    // Output the string with a flag (0 = no ownership transfer)
    debugPrintString(&msg, 0); // FUN_00408a00
}