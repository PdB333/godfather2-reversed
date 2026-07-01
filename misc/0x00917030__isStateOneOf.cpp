//FUNC_NAME: isStateOneOf
// Checks if the value at offset +0xB8 (likely a state enum) is one of the specific values 0xD-0x11 (13-17).
// Returns 1 if it matches, 0 otherwise.
// __fastcall: param_1 is the 'this' pointer.
int __fastcall isStateOneOf(int thisPtr)
{
    int state = *(int *)(thisPtr + 0xB8); // +0xB8: state field (e.g., m_state, m_entityState)
    if (state == 0xD || state == 0xE || state == 0xF || state == 0x10 || state == 0x11)
    {
        return 1;
    }
    return 0;
}