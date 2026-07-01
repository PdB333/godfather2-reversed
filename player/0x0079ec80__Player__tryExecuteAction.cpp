// FUNC_NAME: Player::tryExecuteAction
uint __thiscall Player::tryExecuteAction(int this, uint actionParam)
{
    // Shifted permission flags from m_permissionFlags (+0x249c)
    uint shiftedFlags = *(uint *)(this + 0x249c) >> 1;

    // Check bit 1 of original flags (after shift, bit 0 = original bit 1)
    if ((shiftedFlags & 1) != 0) {
        // Additional runtime check: game active or command allowed?
        if (FUN_00481620() != 0) {
            // Execute action with mode byte from m_actionMode (+0x2498)
            return FUN_00466220(*(byte *)(this + 0x2498), actionParam);
        }
    }
    // Return shifted flags with low byte cleared (indicates failure)
    return shiftedFlags & 0xffffff00;
}