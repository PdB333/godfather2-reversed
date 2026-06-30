// FUNC_NAME: InputManager::getButtonState
char InputManager::getButtonState(int buttonIndex)
{
    // Access thread-local storage to get global input state array
    // FS:[0x2C] -> pointer to TLS block -> deref + offset 8 -> pointer to button state buffer
    // buffer + 0x7c + buttonIndex reads a 32-bit value containing button pressure bits
    uint state = *(uint*)(*(int*)(*(int**)(__readfsdword(0x2C)) + 8) + 0x7C + buttonIndex);
    // Mask off bits 2 and 3 (pressure/state flags)
    uint masked = state & 0x0C;
    if (masked == 0)
        return 0;                 // Not pressed
    if (masked == 4)
        return 2;                 // Light press (bit2 set)
    // Either bit3 (8) or both bits (12) – treat as full press
    return (masked == 8) ? 1 : 2; // 1 for bit3 only, 2 otherwise
}