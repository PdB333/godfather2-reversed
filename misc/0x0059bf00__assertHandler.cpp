// FUNC_NAME: assertHandler
// Address: 0x0059bf00
// Role: Core assertion handler for debug builds.  Checks a condition flag (stored in the passed structure)
// and triggers a debug breakpoint if the assertion fails.  Behavior is controlled by per‑thread data
// (CRT’s _tiddata or similar) and flags returned by a virtual function call.

void __fastcall assertHandler(void* thisPtr) // thisPtr passed in EAX (non‑standard)
{
    // Structure passed in EAX:
    // +0x0c: int assertionState (possibly the report type: 0=ignore, 1=debug, 4=abort)
    // +0x10: char* conditionText (if non‑null and first char is zero, assertion is skipped)
    char** condPtr = *(char***)((int)thisPtr + 0x10);
    
    // If the condition pointer is null or the first character is non‑zero, proceed with assertion handling.
    // Otherwise (condPtr non‑null and *condPtr == 0) the assertion is suppressed.
    if (condPtr == nullptr || **condPtr != '\0')
    {
        // Access per‑thread data via FS:[0x2c] → TLS array → pointer to CRT debug state
        int* pDebugData = *(int**)(*(int**)(__readfsdword(0x2c) + 0x30));
        uint flags = 1;
        if (pDebugData != nullptr)
        {
            // Call a virtual function at offset 0 of the debug data to obtain action flags
            flags = (**(uint (__stdcall**)())(*pDebugData + 8))();
        }

        // If the condition text exists and the flags request it, clear the condition flag to avoid re‑entry
        if (condPtr != nullptr && (flags & 2) != 0)
        {
            **condPtr = 0;
        }

        // Determine whether to invoke the debug breakpoint
        int state = *(int*)((int)thisPtr + 0x0c);
        if ((pDebugData != nullptr || state != 4) &&
            ((flags & 1) != 0 || state == 0 || state == 1))
        {
            // Trigger breakpoint (int 3)
            __asm int 3;
            // After the break (if the debugger continues), the function returns.
        }
    }
}