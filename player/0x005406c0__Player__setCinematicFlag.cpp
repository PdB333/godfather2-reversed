// FUNC_NAME: Player::setCinematicFlag
void __thiscall Player::setCinematicFlag(char enable) {
    // Offset 0x86c: bool flag (isCinematicActive)
    // Offset 0x868: pointer to a ressource/stream handle (cinematicStream)
    // Offset 0x68: base pointer for an associated object (e.g., SoundManager)
    if (*(char *)(this + 0x86c) != '\0' && enable == '\0' && *(int *)(this + 0x868) != 0) {
        FUN_009ea940(this + 0x68, *(int *)(this + 0x868)); // Release stream
        *(int *)(this + 0x868) = 0;
    }
    *(char *)(this + 0x86c) = enable;
}