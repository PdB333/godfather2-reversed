// FUNC_NAME: findSubstringAndCallHandler
// Address: 0x005c7640
// Role: Checks if a substring exists in a source string and if there is trailing content after the match, then calls a handler function (likely part of a command parser or debug console).
void __fastcall findSubstringAndCallHandler(int unused, char* substring, char* sourceString)
{
    char* p = substring;
    // Compute length of substring (p ends at null terminator)
    while (*p != '\0') {
        p++;
    }
    char* found = _strstr(sourceString, substring);
    // Check if substring is found and that there is at least one character after the match (pointer arithmetic may be off due to decompilation)
    if (found != nullptr && (found + (p - (substring + 1)) != nullptr)) {
        FUN_005c7270(); // handler function (likely executes the matched command)
    }
}