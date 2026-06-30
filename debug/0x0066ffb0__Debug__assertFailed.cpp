// FUNC_NAME: Debug::assertFailed
// Function address: 0x0066ffb0
// Role: Handles assertion failures: checks if a debug break is needed based on severity and assertion handler response.
// Context object at ECX (in_EAX) has fields:
//   +0x0c: int severity (e.g., 0=info, 1=warning, 1=error, 4=ignore)
//   +0x10: char* message (can be cleared by handler)

void __fastcall Debug::assertFailed(DebugAssertContext* ctx, int fatalFlag)
{
    // TLS: pointer to current assertion handler (function table)
    int* tlsPtr = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
    
    // Check if message string is present and non-empty (skip only if empty string)
    if ((ctx->message == nullptr) || (ctx->message[0] != '\0'))
    {
        int handlerResponse = 0;
        if (tlsPtr != nullptr)
        {
            // fatalFlag == 0 -> call report function at offset 8
            // fatalFlag != 0 -> call break function at offset 4
            if (fatalFlag == 0)
            {
                handlerResponse = ((AssertHandlerFunc)(tlsPtr[2]))(); // offset 8
            }
            else
            {
                handlerResponse = ((AssertHandlerFunc)(tlsPtr[1]))(); // offset 4
            }
        }

        // If handler says to clear the message (bit 2 set)
        if ((ctx->message != nullptr) && ((handlerResponse & 2) != 0))
        {
            ctx->message[0] = '\0';
        }

        // Determine whether to trigger a debug break:
        // Break if either:
        //   - Handler exists (may have returned a break flag)
        //   - OR severity != 4 (ignore level)
        // AND:
        //   - Handler response has bit 1 set (break requested)
        //   - OR severity is 0 or 1 (info/warning)
        bool condition1 = (tlsPtr != nullptr) || (ctx->severity != 4);
        bool condition2 = ((handlerResponse & 1) != 0) || (ctx->severity == 0) || (ctx->severity == 1);
        if (condition1 && condition2)
        {
            __debugbreak(); // int 3
        }
    }
}