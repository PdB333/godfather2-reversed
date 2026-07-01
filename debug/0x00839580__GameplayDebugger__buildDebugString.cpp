// FUNC_NAME: GameplayDebugger::buildDebugString
void __thiscall GameplayDebugger::buildDebugString(int thisPtr, undefined4 param_2)
{
    // Local string buffers and deallocation function pointers
    char* playerStr = 0;
    char* locationStr = 0;
    char* stateStr = 0;
    char* timeStr = 0;
    char* formattedOutput = 0;

    // Get format flags from member at +0xe8
    uint formatFlags = *(uint*)(thisPtr + 0xe8);

    // Convert player ID (at +0xf0) to string
    if ((formatFlags & 1) == 0) {
        getDebugValueString(*(int*)(thisPtr + 0xf0), &playerStr, 1);
    } else {
        getDebugValueStringShort(*(int*)(thisPtr + 0xf0), &playerStr, 1);
    }

    // Convert location ID (at +0x90) to string
    if ((formatFlags & 1) == 0) {
        getDebugValueString(*(int*)(thisPtr + 0x90), &locationStr, 1);
    } else {
        getDebugValueStringShort(*(int*)(thisPtr + 0x90), &locationStr, 1);
    }

    // Convert state ID (at +0xf4) using bit1
    if ((formatFlags >> 1 & 1) == 0) {
        getDebugValueString(*(int*)(thisPtr + 0xf4), &stateStr, 1);
    } else {
        getDebugValueStringShort(*(int*)(thisPtr + 0xf4), &stateStr, 1);
    }

    // Get raw time value (ms) from +0xf8 and format as mm:ss
    int rawTime = getSystemTimeMs(*(int*)(thisPtr + 0xf8));
    unsigned int seconds = (rawTime + 500) / 1000;
    formatTimeMinutesSeconds(seconds / 60, seconds % 60, &timeStr);

    // Get extra string from +0x16c (nullable, default to empty)
    char* extraStr = *(char**)(thisPtr + 0x16c);
    if (extraStr == 0) {
        extraStr = "";
    }

    // Build final formatted string
    stringFormat(&formattedOutput, "{P:%s}{L:%s}{S:%s}{E:%s}{%s}",
                 (playerStr != 0) ? playerStr : "",
                 (locationStr != 0) ? locationStr : "",
                 (stateStr != 0) ? stateStr : "",
                 (timeStr != 0) ? timeStr : "",
                 extraStr);

    // Pass to UI (param_2 likely a text label or control handle)
    setDebugText(param_2, (formattedOutput != 0) ? formattedOutput : "");

    // Free allocated strings using stored deallocate function pointers
    if (formattedOutput != 0) {
        freeString(formattedOutput);
    }
    if (timeStr != 0) {
        freeString(timeStr);
    }
    if (stateStr != 0) {
        freeString(stateStr);
    }
    if (locationStr != 0) {
        freeString(locationStr);
    }
    if (playerStr != 0) {
        freeString(playerStr);
    }
}