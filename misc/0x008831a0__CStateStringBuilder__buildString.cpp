// FUNC_NAME: CStateStringBuilder::buildString
// 0x008831a0 - Constructs a formatted string based on an internal state index.
// The state (uint from this+0x70) selects a global data pointer (likely a format string or object).
// Formats the input `param_3` using that data into a temporary buffer, then copies to `param_2`.

void __thiscall CStateStringBuilder::buildString(
    CStateStringBuilder* this,
    char* outString,          // param_2: output buffer
    const char* inString      // param_3: input string (e.g., format or source)
)
{
    int stateIndex;           // iVar1
    char* stateData;          // uVar2
    char buffer[76];          // local_50

    stateIndex = *(int*)((uintptr_t)this + 0x70);  // +0x70 state index (0,1,2)

    // Select global data based on state index
    if (stateIndex == 0)
    {
        stateData = (char*)DAT_00e446a0;   // Global data for state 0
    }
    else if (stateIndex == 1)
    {
        stateData = (char*)DAT_00d5f00c;   // Global data for state 1 and 2
    }
    else if (stateIndex == 2)
    {
        stateData = (char*)DAT_00d5f00c;   // Same as state 1
    }
    else
    {
        stateData = nullptr;
    }

    // Build formatted string into buffer using state data and input string
    FUN_0056c040(stateData, inString, buffer);   // Likely copies formatted text into buffer
    // Copy result to output string
    FUN_0056d530(buffer, outString);             // Likely string copy or concatenation
}