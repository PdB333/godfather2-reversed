// FUNC_NAME: CrashHandler::CaptureStackContext
// Address: 0x007a92a0
// Role: Saves up to 0xB0 dwords from caller's stack into local buffer, then calls a handler function with a pointer to a structure containing this pointer. Used for debug/crash context capture.

void __fastcall CrashHandler::CaptureStackContext(CrashHandler* this)
{
    // Check if handler is not already active (byte at +0x311c) and a critical pointer is non-null (int at +0x130)
    if (this->field_0x311c == 0 && this->somePointer != 0)
    {
        // Copy 0xB0 dwords from the caller's stack frame into a local buffer
        undefined4 stackContext[178]; // large enough to hold 0xB0 (176) dwords
        // The source is the stack area starting at the return address (just above the current frame)
        undefined4* stackSource = (undefined4*)&stack0x00000004;
        undefined4* stackDest = stackContext;
        for (int i = 0; i < 0xB0; i++)
        {
            *stackDest = *stackSource;
            stackSource++;
            stackDest++;
        }

        // Build a temporary structure: pointer to this object
        CrashHandler* contextBlock[1]; // effectively a pointer to this
        contextBlock[0] = this;

        // Call the actual handler (possibly a virtual or static function)
        FUN_007a6f10(contextBlock);
    }
}