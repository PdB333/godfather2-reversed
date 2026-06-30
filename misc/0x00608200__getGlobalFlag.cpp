// FUNC_NAME: getGlobalFlag
// Function address: 0x00608200
// Role: Returns a global byte flag from a fixed address (likely a boolean or state indicator).
unsigned char getGlobalFlag(void)
{
    return *(unsigned char*)0x0120575b;
}