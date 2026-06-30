// Function address: 0x0060e9e0
// Role: Returns a global flag/option (DAT_0120588c) as a 16-bit value.
// The specific meaning is unknown; possibly a debug flag or game option.

uint16_t getGameOptionFlag() {
    // DAT_0120588c is a global variable in the data section.
    return s_gameOptionFlag;  // renamed from DAT_0120588c
}