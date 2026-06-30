// FUNC_NAME: setGlobalByteFlag
// Function at 0x00606360: Setter for a global byte flag.
// Identified role: Simple assignment to global variable.
extern uint8_t g_globalByteFlag;

void setGlobalByteFlag(uint8_t value)
{
    g_globalByteFlag = value;
}