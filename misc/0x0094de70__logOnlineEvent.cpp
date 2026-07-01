// FUNC_NAME: logOnlineEvent
void logOnlineEvent(char** param_1, bool param_2, unsigned int param_3, char** param_4, bool param_5)
{
    char* str1 = *param_4;
    if (str1 == nullptr) {
        str1 = &DAT_0120546e; // Default empty string
    }
    char* color2 = &DAT_00e35154; // Default color code
    if (param_5) {
        color2 = &DAT_00e35114; // Alternative color code
    }
    char* str2 = *param_1;
    if (str2 == nullptr) {
        str2 = &DAT_0120546e;
    }
    char* color1 = &DAT_00e35154;
    if (param_2) {
        color1 = &DAT_00e35114;
    }
    char* formattedString;
    FUN_004d4a60(&formattedString, 1, "[c=%s]%s[c=RESET] [b=OnlineEvent%u] [c=%s]%s[c=RESET]", color1, str2, param_3, color2, str1);
    char* finalStr = formattedString;
    if (formattedString == nullptr) {
        finalStr = &DAT_0120546e;
    }
    FUN_005a04a0("InformEvent", 0, &DAT_00d8b7d4, 1, finalStr);
    if (formattedString != nullptr) {
        // Deallocate the formatted string (likely operator delete or custom free)
        // local_4 is a function pointer that was not initialized in decompilation; assume it's a deallocation function
        // For reconstruction, we call a placeholder deallocation function
        deallocateString(formattedString);
    }
}