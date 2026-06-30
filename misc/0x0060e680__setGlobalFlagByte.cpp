// FUNC_NAME: setGlobalFlagByte
// Address: 0x0060e680
// Sets a global byte flag at address 0x00f15a39. Called from multiple locations,
// likely toggling a debug or gameplay mode.

void setGlobalFlagByte(uint8_t value)
{
    // Global flag (0x00f15a39) - represents some boolean or state byte
    g_someByteFlag = value;
}