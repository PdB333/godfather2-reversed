// FUNC_NAME: getFieldAtOffset0x5c
// Simple getter that reads a 4-byte value from offset 0x5c of the object.
// Likely a member variable (e.g., an ID, state, or pointer) accessed frequently.
int __fastcall getFieldAtOffset0x5c(int thisPtr)
{
    return *(int*)(thisPtr + 0x5c);
}