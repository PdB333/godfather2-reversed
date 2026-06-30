// FUNC_NAME: debugPrintString
void debugPrintString(void* context, const char* text)
{
    size_t length = 0;
    const char* p = text;
    while (*p != '\0') {
        ++p;
        ++length;
    }
    FUN_00ab8560(context, text, length);
}