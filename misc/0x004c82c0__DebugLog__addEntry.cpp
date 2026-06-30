// FUNC_NAME: DebugLog::addEntry
void DebugLog::addEntry(char* context, int value) {
    char buffer[12]; // stack-allocated temporary buffer
    buffer[0] = 0;
    *(short*)(buffer+4) = 0;
    *(short*)(buffer+6) = 0;
    if (context != (char*)0x0 && *context != '\0') {
        char* prefix = getTimestamp(); // FUN_004dafd0
        appendString(buffer, prefix); // FUN_00408260
    }
    struct KeyValuePair kv;
    kv.key = buffer;
    kv.value = value;
    kv.next = 0;
    addPair(&kv, 0); // FUN_00408a00
    releaseBuffer(buffer); // FUN_00408310
}