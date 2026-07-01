// FUNC_NAME: GameStateManager::updateState
void __fastcall GameStateManager::updateState(int *this)
{
    char isActive;

    this->prepareStateCheck();
    isActive = isGameActive();
    if ((((isActive == '\0') && (this[0x65] != 0)) && ((this[0xa4] & 0x20U) != 0)) &&
       ((this[0xa4] & 0x100U) == 0)) {
        // +0x194: pointer or flag for special state
        // +0x290: bit flags (bit5=0x20, bit8=0x100)
        this->handleSpecialState();
    }
    else if ((this[0xa4] & 0x100U) != 0) {
        // vtable+0x54: setFlashColor(1) – e.g., trigger a flash effect
        (*(void (__thiscall **)(int))(this[0] + 0x54))(1);
        resetActionTimer(0);
        // vtable+0x5c: setFadeColor(0x80, 0xc0) – e.g., set fade to a specific color
        (*(void (__thiscall **)(int, int))(this[0] + 0x5c))(0x80, 0xc0);
    }
    if ((*(byte *)(this + 0xa4) & 0x20) != 0) {
        // vtable+0x5c: setFadeColor(0x3f, 0x3f)
        (*(void (__thiscall **)(int, int))(this[0] + 0x5c))(0x3f, 0x3f);
    }
    return;
}