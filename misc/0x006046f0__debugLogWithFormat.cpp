// FUNC_NAME: debugLogWithFormat
// Function at 0x006046f0 - Debug log helper that formats two integer values using single-character format specifiers from globals.
// Note: Contains unreachable code paths (null function pointer calls), likely from incomplete decompilation or debug-only stubs.
void debugLogWithFormat(uint32_t* param_1) // param_1 is pointer to two uint32 values
{
    // Allocate two 2-byte buffers
    char* fmtPart1 = (char*)heapAlloc(2); // FUN_009c8e50(2)
    fmtPart1[0] = DAT_00e337cc; // first format character
    fmtPart1[1] = '\0';

    char* fmtPart2 = (char*)heapAlloc(2);
    fmtPart2[0] = DAT_00e337cd; // second format character
    fmtPart2[1] = '\0';

    // Build first part: fmtPart1, size=1, then the two param_1 values
    // FUN_004d3ca0 likely is snprintf or custom string builder
    customFormatString(fmtPart1, 1, *param_1, param_1[1]); // FUN_004d3ca0

    // The following code appears to have uninitialized locals and null function pointers.
    // It may be a debug path or a decompilation artifact.
    int uninitVar1; // local_20
    uint32_t uninitVar2; // local_1c
    // This call uses uninitVar1 and uninitVar2 as destination (potentially a bug)
    customFormatString(uninitVar1, uninitVar2, fmtPart2, 1); // FUN_004d3ca0

    int commandData[3] = {0}; // local_10
    executeCommand(commandData); // FUN_004d3e20

    if (commandData[0] != 0)
    {
        // Null function pointer dereference (would crash if reached)
        ((void (*)(int))0)(commandData[0]); // (*local_4)(local_10[0]) with local_4=0
    }

    if (uninitVar1 != 0)
    {
        // Another null function pointer call
        ((void (*)(int))0)(uninitVar1); // (*(code *)0x0)(local_20)
    }

    // Free the allocated buffers
    heapFree(fmtPart2); // thunk_FUN_009c8eb0
    heapFree(fmtPart1); // thunk_FUN_009c8eb0
}