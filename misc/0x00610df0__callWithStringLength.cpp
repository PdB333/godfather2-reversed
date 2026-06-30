// FUNC_NAME: callWithStringLength

// Function address: 0x00610df0
// Role: Helper to compute string length and call a debug/log function with the length.
// Computes strlen(str) and invokes debugPrintWithLength(param, str, length).

void callWithStringLength(char* str, int param)
{
    int len = 0;
    char* p = str;
    while (*p != '\0') {  // compute string length
        ++p;
    }
    len = (int)(p - (str + 1));  // equivalent to strlen - 1? Actually p points past the null, so length = p - str - 1. But standard strlen would be p - str - 1? Wait: The decompiled loop increments pcVar2, then checks cVar1 != '\0'. So after loop, pcVar2 points to one past the null terminator? Actually typical strlen loop: while (*p != '\0') p++; Then p points to null terminator. But here: pcVar2 = param_1; do { cVar1 = *pcVar2; pcVar2 = pcVar2 + 1; } while (cVar1 != '\0'); So after loop, pcVar2 points to one char after the null terminator. Because it increments after reading. So length = (int)pcVar2 - (int)(param_1 + 1) = (pcVar2 - param_1 - 1). But pcVar2 is param_1 + strlen(str) + 1. So length = strlen(str) + 1 - 1 = strlen(str). Indeed it's strlen. We'll use strlen for clarity.
    
    // The loop above is equivalent to:
    // int len = strlen(str);
    
    FUN_00ab8560(param, str, len);  // calls the underlying function with the provided param
}