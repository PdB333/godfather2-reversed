// FUNC_NAME: GetGlobalByte
// Function at 0x0069d510: Simple getter returning a global byte variable (DAT_0112a028).
// Likely used to read a configuration flag or state byte from global data.
unsigned char GetGlobalByte(void)
{
    // DAT_0112a028 is a global byte variable holding some state/config.
    return DAT_0112a028;
}