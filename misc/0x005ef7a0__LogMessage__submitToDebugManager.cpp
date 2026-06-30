// FUNC_NAME: LogMessage::submitToDebugManager
void __fastcall LogMessage::submitToDebugManager(int this)
{
    // +0x10: pointer to format string (or 0 for default)
    const char* formatStr = *(const char**)(this + 0x10);
    if (formatStr == (const char*)0x0) {
        formatStr = &DAT_0120546e;  // default debug string
    }

    int thisCopy = this; // local copy of 'this' for logging context

    // global debug manager at DAT_0122350c, check enabled flag at +0x1744
    if (*(char*)(DAT_0122350c + 0x1744) != '\0') {
        // write log entry: format string, data field from +0x20, sentinel -1
        FUN_005e25f0(DAT_0122350c, &thisCopy, formatStr, this + 0x20, 0xffffffff);
    }

    FUN_005e1fd0(); // flush log output
}