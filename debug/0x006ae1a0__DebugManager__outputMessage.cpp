// FUNC_NAME: DebugManager::outputMessage
bool __thiscall DebugManager::outputMessage(int thisPtr, int param2, int param3)
{
    // Stack-allocated structure for building a debug message
    // Contains a static format string, a vtable pointer, and two integer arguments
    struct DebugMessage {
        int    formatString;     // +0x00: static format string (DAT_0112a5d8)
        void** vtablePtr;        // +0x04: pointer to vtable (points to &vtable)
        char   padding;          // +0x08: unused
        void** vtable;           // +0x0C: actual vtable (PTR_LAB_00d5dbb4)
        int    instanceData;     // +0x10: from this+0x180 (e.g., debug ID or pointer)
        int    arg1;             // +0x14: param2
        int    arg2;             // +0x18: param3
        bool   returnFlag;       // +0x1C: always 0 (false)
    } msg;

    msg.formatString = DAT_0112a5d8;
    msg.vtablePtr    = &msg.vtable;
    msg.vtable       = (void**)&PTR_LAB_00d5dbb4;
    msg.instanceData = *(int*)(thisPtr + 0x180);
    msg.arg1         = param2;
    msg.arg2         = param3;
    msg.returnFlag   = false;
    msg.padding      = 0;

    // call logging function with pointer to message structure and a flag
    FUN_00408a00(&msg, 0);

    return false; // always returns false
}