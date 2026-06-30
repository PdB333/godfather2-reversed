// FUNC_NAME: SetSliderValueState
// Address: 0x0053d470
// Role: Updates global slider state based on a float input (likely a slider value range).
// Global constants: DAT_00e2b1a4 (unknown offset), DAT_01219908 (pointer/constant), DAT_01125e84 (array of 8-byte entries)

void SetSliderValueState(int param_1, float inputValue)
{
    uint quantized;

    g_rawSliderValue = inputValue;               // +0x0112602c
    quantized = (uint)(inputValue + OFFSET_CONSTANT) & 0xfe;  // Clamp to even step
    if (quantized < 2) {
        quantized = 2;
    }
    g_stepIndex = ((quantized - 2) >> 1) + 4;    // +0x01126028  (converted to array index)
    g_somePointer = DAT_01219908;                 // +0x01125d90
    // Array of 8-byte entries, use stepIndex*8 to pick element, take first 4 bytes as float
    g_arrayEntry = *(float*)((char*)&DAT_01125e84 + g_stepIndex * 8); // +0x01125d94
    g_extraParam = param_1;                       // +0x01125e24
    g_quantizedFloat = (float)quantized;          // +0x01126030
}