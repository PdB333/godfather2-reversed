// FUNC_NAME: EA::Assert::breakOnAssert
void __fastcall EA::Assert::breakOnAssert(AssertContext* ctx, bool isWarning)
{
    // ctx+0x10: expression string (char*)
    // ctx+0x0C: severity level (int)
    // TLS at FS:[0x2C] -> +0x30 holds a pointer to an assertion handler table
    if ((ctx->expression != nullptr) && (ctx->expression[0] != '\0'))
    {
        int* handlerTable = *(int**)(*(int*)(__readfsdword(0x2C) + 0x30));
        uint32_t handlerResult = 1; // default: continue
        if (handlerTable != nullptr)
        {
            if (isWarning)
            {
                // handlerTable->handleWarning() (vtable+4)
                handlerResult = (**(uint32_t (__fastcall**)(int*))(*handlerTable + 4))();
            }
            else
            {
                // handlerTable->handleAssert() (vtable+8)
                handlerResult = (**(uint32_t (__fastcall**)(int*))(*handlerTable + 8))();
            }
        }

        // If the expression string pointer is not null and the handler says "log it" (bit 2), then modify the string to mark it as used?
        if ((ctx->expression != nullptr) && ((handlerResult & 2) != 0))
        {
            ctx->expression[0] = '\0';
        }

        // Decide whether to trigger debug break:
        // - If there was a handler, or the severity is not 4 (possibly "ignore")
        // - And either handler says "break" (bit 1) or severity is 0 or 1 (likely "error" or "warning")
        if (((handlerTable != nullptr) || (ctx->severity != 4)) &&
            ((handlerResult & 1) || (ctx->severity == 0) || (ctx->severity == 1)))
        {
            __debugbreak();  // break into debugger
        }
    }
}