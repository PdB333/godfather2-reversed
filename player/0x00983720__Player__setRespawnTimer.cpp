// FUNC_NAME: Player::setRespawnTimer
void __thiscall Player::setRespawnTimer(uint newTimer, uint maxTimer) {
    // Only update if timer is within valid range and player can respawn (flag at this+0x48 is non-zero)
    if ((newTimer < maxTimer) && (*(char *)(this + 0x48) != '\0')) {
        // Store the new respawn timer value at offset +0xd4
        *(uint *)(this + 0xd4) = newTimer;
        // Log the event for debugging (engine utility)
        LogEvent("UpdateRespawnTimer", 0, &DAT_00d77dc0, 0);
    }
}