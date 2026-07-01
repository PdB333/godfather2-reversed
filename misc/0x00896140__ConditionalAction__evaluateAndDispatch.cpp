//FUNC_NAME: ConditionalAction::evaluateAndDispatch

void __thiscall ConditionalAction::evaluateAndDispatch(int thisPtr, int param2)
{
    float currentValue;
    byte flags;
    int selectedValue;

    // Retrieve current value from some source (e.g., timer, distance)
    FUN_008934e0(*(int*)(thisPtr + 0x50), &currentValue);

    flags = *(byte*)(thisPtr + 0x58);

    // Check conditions based on flag bits
    if ((((flags & 1) != 0) && (currentValue < *(float*)(thisPtr + 0x54))) ||
        (((flags & 2) != 0) &&
         ((float)((uint)(currentValue - *(float*)(thisPtr + 0x54)) & DAT_00e44680) < DAT_00e44598))) ||
        (((flags & 4) != 0) &&
         (*(float*)(thisPtr + 0x54) <= currentValue && currentValue != *(float*)(thisPtr + 0x54))))
    {
        selectedValue = *(int*)(thisPtr + 0x64); // +0x64: value when condition true
    }
    else
    {
        selectedValue = *(int*)(thisPtr + 0x6c); // +0x6c: value when condition false
    }

    // Build and dispatch a message structure
    struct {
        int value;
        int param2;
        byte zero;
    } message;
    message.value = selectedValue;
    message.param2 = param2;
    message.zero = 0;

    FUN_00408a00(&message, 0);
}