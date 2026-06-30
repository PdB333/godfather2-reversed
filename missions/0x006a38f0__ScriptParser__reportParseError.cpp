// FUNC_NAME: ScriptParser::reportParseError
void __thiscall ScriptParser::reportParseError(int errorCharIndex)
{
    wchar_t buffer[40]; // 80 bytes buffer for formatted error message

    if (m_pErrorHandler != nullptr) // +0x4: pointer to error handler object
    {
        formatErrorMessage(buffer, L"E01: Parse error near character %d", errorCharIndex);
        // Call error handler's output method via vtable at offset +0x4
        ((void (__thiscall *)(void *, wchar_t *))(*(int (**)(void))m_pErrorHandler)[1])(m_pErrorHandler, buffer);
    }
}