// FUNC_NAME: UnknownClass::getStateFlag

bool UnknownClass::getStateFlag()
{
    // +0x8A holds a flags byte; bit 5 (0x20) indicates if state is initialized
    if ((*(uint8_t*)(this + 0x8A) & 0x20) == 0) {
        updateState(); // Call to set up state (function at 0x006e6700)
    }
    // +0x89 holds another flags byte; return bit 3 (shift right 3, mask 1)
    return (*(uint8_t*)(this + 0x89) >> 3) & 1;
}