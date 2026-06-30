// FUN_00496c40: dispatchCommand
// Dispatch function that uses a global table of handlers.
// The handler index is extracted from the second byte of the command ID (bits 8-15, 1-based).
// ecx (this), edx, arg3, and arg6 are passed through to the handler; the high 16 bits of commandID are also passed.
// Returns the handler's result, or 0 if index is out of range.

typedef void* (*CommandHandler)(void* param1, void* param2, void* param3, uint param4);

extern CommandHandler* g_handlerTable; // DAT_01163f68
extern int g_handlerCount;            // DAT_01205460

void* __fastcall dispatchCommand(void* ecx, void* edx, void* arg3, uint commandID, void* arg5, void* arg6)
{
    uint rawIndex = (commandID >> 8) & 0xFF; // byte at bits 8-15
    int handlerIndex = (int)(rawIndex - 1);  // 1-based to 0-based

    // The check uses the unsigned version, so negative values become large positive and are rejected.
    if ((uint)handlerIndex < (uint)g_handlerCount)
    {
        // Call the handler with: (arg3, edx, arg6, high 16 bits of commandID)
        return g_handlerTable[handlerIndex](arg3, edx, arg6, commandID >> 16);
    }
    return 0;
}