// FUNC_NAME: EntityBase::resetHitCooldown
void __thiscall EntityBase::resetHitCooldown()
{
    if (this != 0) {
        // +0x64: byte field (perhaps a debug flag or subtype)
        // +0x5C: int field (maybe an ID or timer value)
        // +0x65: byte field (another flag)
        FUN_005dbc10(*(byte *)(this + 100), *(int *)(this + 0x5C), *(byte *)(this + 0x65));
        // Possibly clears or resets some shared state
        FUN_005f3640();
        // Copy current cooldown value from +0x88 to +0x8C (save previous)
        *(int *)(this + 0x8C) = *(int *)(this + 0x88);
        // Set byte at +0x67 to 0xFF (indicates ready/inactive/cooldown expired)
        *(byte *)(this + 0x67) = 0xFF;
        // Second call to the same helper (maybe for logging/update after reset)
        FUN_005dbc10(*(byte *)(this + 100), *(int *)(this + 0x5C), *(byte *)(this + 0x65));
    }
    return;
}