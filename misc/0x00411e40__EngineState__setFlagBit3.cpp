// FUNC_NAME: EngineState::setFlagBit3
void EngineState::setFlagBit3(void)
{
    // gEngineState is a global pointer to the engine state singleton (DAT_012233b8)
    // Offset +0x10: flags bitfield
    // Bit 3 (0x08): some enable flag, set once if not already set
    uint *flags = (uint *)(gEngineState + 0x10);
    if ((*flags & 8) == 0) {
        *flags |= 8;
    }
}