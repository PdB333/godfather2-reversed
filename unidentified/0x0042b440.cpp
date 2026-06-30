// FUN_0042b440: setGlobalGameStateFlagWord
void setGlobalGameStateFlagWord(uint16_t value)
{
    // Store value into the low 16 bits of the global state variable at 0x012053dc
    *reinterpret_cast<volatile uint16_t*>(0x012053dc) = value;
}