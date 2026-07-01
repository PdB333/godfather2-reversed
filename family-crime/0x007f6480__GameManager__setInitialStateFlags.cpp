// FUNC_NAME: GameManager::setInitialStateFlags
void __fastcall GameManager::setInitialStateFlags(int thisPtr)
{
    // +0x81c: uint32 flags field - clear lower 4 bits, then set bits 1 and 4 (0x12)
    *(uint32*)(thisPtr + 0x81C) = (*(uint32*)(thisPtr + 0x81C) & 0xFFFFFFF0) | 0x12;

    // +0x79C: store a global constant (likely a game state or timer reference)
    *(uint32*)(thisPtr + 0x79C) = DAT_00d5ccf8; // e.g., gGameTime or gInitialState
}